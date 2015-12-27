/*
   Copyright 2015 Daniel Jay Haskin

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#ifndef UDR_REPOSITORY_HPP
#define UDR_REPOSITORY_HPP 1
#include <list>
#include <algorithm>
#include <string>

namespace udr {
    typedef std::string URL;
    typedef std::string name_type;
    typedef std::string version_type;
    typedef std::function<bool(version_type)> constraint_type;


    class package_system {
        public:
            virtual std::unordered_map<name_type, std::unordered_set<constraint_type> >
                query_dependencies(
                        const name_type & name,
                        const version_type & version) = 0;
            virtual std::unordered_map<version_type, URL> query_candidates(
                    const name_type & name) = 0;
            virtual int compare_versions(const version_type & a,
                    const version_type & b) = 0;
            virtual std::unordered_map<name_type, std::unordered_set<constraint_type> >
                constraints_from_string(
                        const std::string & constraints) = 0;
    };

    class repository {
        private:
            const package_system *system;
            std::forward_list<URL> resolve(const std::unordered_map<name_type, std::unordered_set<constraint_type> &
                    order) const {
                std::forward_list<URL> result;
                for (auto package : order) {
                    auto name = package.first;
                    auto constraints = package.second;

                    std::unordered_map<version_type, URL> candidates =
                        system->query_candidates(name);
                    for (auto constraint : constraints) {
                        std::remove_if(candidates.begin(), candidates.end(),
                                [constraint&](auto x){return constraint(x.first);});
                    }

                    if (candidates.empty() ) {
                        return result;
                    }

                    // sort in descending order, latest versions first
                    std::stable_sort(candidates,
                            [](a, b) {
                            return system->compare_versions(a,b) * -1;
                            });

                    for (auto candidate : candidates) {
                        auto candidate_version = candidate.first;
                        auto candidate_url = candidate.second;
                        auto candidate_deps =
                            system->query_dependencies(name, candidate_version);
                        auto candidate_dep_urls = this->resolve(candidate_deps);
                        if (!candidate_dep_urls.empty()) {
                            // concatenate lists, use move semantics if possible
                            result.splice(result.cend(), candidate_dep_files);
                            break;
                        }
                        result.push_back(candidate_url);
                    }
                }
                return result;
            }
        public:
            std::forward_list<URL> resolve(const std::string & constraints) const {
                return resolve(system->constraints_from_string(constraints));
            }
    };
}

#endif // UDR_REPOSITORY_HPP
