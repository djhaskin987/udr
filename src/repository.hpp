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
    typedef std::function<int(version_type,version_type)> compare_type;
    typedef std::function<std::map<versioN_type, URL>(name_type) > query_type;
    typedef std::function<std::map<name_type, std::set<constraint_type> >(
            name_type, version_type)> query_dependencies_type;

    std::list<URL> resolve(
            const std::map<name, std::set<constraint_type> > & order,
            const compare_type & compare_versions,
            query_type query,
            query_dependencies_type dependencies) {

        std::list<URL> result;
        for (auto package : order) {
            auto name = package.first;
            auto constraints = package.second;

            std::map<version_type, URL> candidates = query(name);
            for (auto constraint : constraints) {
                std::remove_if(candidates.begin(), candidates.end(),
                        [constraint&](auto x){return constraint(x.first);});
            }

            if (candidates.empty() ) {
                return result;
            }

            std::stable_sort(candidates,
                    [](a, b) {
                    return compare_versions(a,b) * -1;
                    });

            for (auto candidate : candidates) {
                auto candidate_version = candidate.first;
                auto candidate_url = candidate.second;
                auto candidate_deps =
                    dependencies(name, candidate_version);
                auto candidate_dep_urls = resolve(candidate_deps,
                        compare,
                        query,
                        dependencies);
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
}
#endif // UDR_REPOSITORY_HPP
