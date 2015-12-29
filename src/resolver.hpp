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
#include "types.hpp"
#include <boost/expected.hpp>

/* TODO:
 *   - Expected value use for repository
 *   - Start implementing stuff
 */
namespace udr {
    class repository {
        public:
            virtual std::forward_list<std::pair<version_type, URL> > query_available(
                    const name_type & name) = 0;
            virtual std::unordered_map<name_type, std::unordered_set<constraint_type> >
                query_dependencies(
                        const name_type & name,
                        const version_type & version) = 0;
    };

    class resolver {
        private:
            const repository *repo;
        public:
            boost::expected< std::forward_list<URL>,
                std::forward_list<std::pair<name_type, std::unordered_set<constraint_type> > >
                resolve(const order_type & order) const {
                std::forward_list<URL> result;
                for (auto package : order) {
                    auto name = package.first;
                    auto constraints = package.second;

                    // a list for a REASON
                    // Lets the package system determine
                    // what version of package to try first
                    // This allows pooling vs priority repositories.
                    std::forward_list<std::pair<version_type, URL> > candidates =
                        repo->query_available(name);
                    for (auto constraint : constraints) {
                        std::remove_if(candidates.begin(), candidates.end(),
                                [constraint&](auto x){return constraint(x.first);});
                    }

                    if (candidates.empty() ) {
                        std::forward_list<std::pair<name_type, std::unordered_set<constraint_type> > > lst;
                        lst.push_front(package);
                        return make_unexpected(lst);
                    }

                    for (auto candidate : candidates) {
                        auto candidate_version = candidate.first;
                        auto candidate_url = candidate.second;
                        auto candidate_deps =
                            repo->query_dependencies(name, candidate_version);
                        auto candidate_dep_urls = this->resolve(candidate_deps);
                        if (candidate_dep_urls) {
                            if (!(*candidate_dep_urls).empty()) {
                                result.splice(result.cend(), *candidate_dep_urls);
                            }
                        }
                        else
                        {
                            // return error case
                            std::forwared_list<std::pair<name_type, unordered_set<constraint_type> > >
                                lst;
                            lst.splice(lst.cend(),candidate_dep_urls.error().value());
                            return lst;
                        }
                        result.push_back(candidate_url);
                    }
                }
                return result;
            }
    };
}

#endif // UDR_REPOSITORY_HPP
