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
 *   - circular dependencies
 *   - conjunctive normal form orders
 *   - DNF is easier to process, but CNF is more natural to specify.
 *   - (a>1&a<2|b>1&b<2)&(b>3&b<4|c>3&c<8)
 *   - (b>1&b<2&b>3&b<4)|(a>1&a<2&c>3&c<8)
     *   cnf terms: {name -> (relation -> version)}
     *   dnf terms: {name -> (relation -> version)}
     *   convert from cnf to dnf, or at least specify in dnf to start with
 *   - memoize what candidates have already been found a&b|(a&c);(in the case of (a|b@1)&(b@|c)&d&b@3 -> b@1,2,3|a&c, previously memoize that we've already found b (or so? i don't like first found).
 *       - Get list of which names are in multiple terms and how many terms they are in. Resolve their terms first, preferring the names which are listed frequently.
 *       - If I can use b to satisfy both, that is better. Therefore, 
 *   - template by name type so that they can validate, set it by default to udr::name_type
 *   - version type is a thing, with comparison and match() -- template or virtualize?
 */
namespace udr {
    template <typename name_type, typename version_type>
    class repository {
        public:
        virtual std::vector<std::tuple<version_type,
                                       url_type,
                                       requirement_type,
                                       conflicts_type,
                                       suggests_type,
                                       obsoleted_by_type> >
        query(const name_type & name) = 0;
    };


    template <typename name_type, typename version_type>
    class resolver {
        private:
            const repository *repo;
        public:
        
            boost::expected< std::vector<URL>,
                std::vector<std::pair<name_type, std::unordered_set<version_constraint_type> > >
                resolve(const order_type & order) const {
                std::vector<URL> result;
                for (auto package : order) {
                    auto name = package.first;
                    auto constraints = package.second;

                    // a list for a REASON
                    // Lets the package system determine
                    // what version of package to try first
                    // This allows pooling vs priority repositories.
                    std::vector<std::pair<version_type, URL> > candidates =
                        repo->query_available(name);
                    for (auto constraint : constraints) {
                        std::remove_if(candidates.begin(), candidates.end(),
                                [constraint&](auto x){return constraint(x.first);});
                    }

                    if (candidates.empty() ) {
                        std::vector<std::pair<name_type, std::unordered_set<constraint_type> > > lst;
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
