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
#ifndef UDR_RESOLVER_HPP
#define UDR_RESOLVER_HPP 1
#include <list>
#include <algorithm>
#include <string>
#include "types.hpp"
#include <boost/expected.hpp>



/// HAVING A CONSTRAINT IS NOT GOOD.
// I NEED A VECTOR OF CONSTRAINTS
// SO THAT I CAN ALSO EASILY HAVE NO
// CONSTRAINTS AT ALL
// EITHER THAT OR GET IT TO WHERE
// CONSTRAINTS DEFAULT TO "true"
//
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

    typedef std::string url_type;
    template <typename V>
        using std::function<bool(const V &, const V &)> = constraint_type;

    template <typename N, typename V>
    struct package_specifier
    {
        typedef N name_type;
        typedef V version_type;
        name_type name;
        std::vector< constraint_type<version_type> > constraints;
    }

    template <typename N, typename V>
    struct package
    {
        typedef N name_type;
        typedef V version_type;
        version_type version;
        url_type URL;
        order_type<N, V> requires;
        boost::optional<N> obsoletes;
        order_type<N, V> suggests;
        package() = default;
    };

    template <typename N, typename V>
        using std::vector<package_specifier<N, V> > = possibilities_type;

    template <typename N, typename V>
        using std::vector<possibilities_type<N, V> > = order_type;


    template <typename N, typename V>
    class repository {
        public:
            typedef N name_type;
            typedef V version_type;
            virtual std::vector<package> query(const N & name) const = 0;
    };

    template <typename N, typename V>
    class resolver {
        public:
            enum class suggests_policy {
                REQUIRED,
                BEST_EFFORT,
                IGNORE
            };

        private:
            suggests_policy policy;
        // herein lies a lot of typedefs and the use of boost::variant.
        // Please excuse my heavy LISP accent.
        // Or should I just say, pleathe excuthe my lithp? :P
        typedef std::vector<package<N,V> > resolver_success_type;
        typedef order_type<N, V> resolver_failure_type;
        // not useful, given possibilities. Even candidates for one possibility
        /*
        template <typename N, typename V>
        struct resolver_failed_type
        {
            typedef N name_type;
            typedef V version_type;

            std::vector<package_specifier<N, V> > ancestor_line;
            N name;
            resolver_failed_type() = default;
        };
        typedef boost::variant<resolver_success_type,
                               resolver_failed_type> resolver_result_type;
        */
        typedef boost::optional<resolver_success_type>
            resolver_result_type;


        const repository *repo;
        const bool reorder;

        resolver_result_type resolve_requirement(
                const possibilities_type & requirement,
                order_type<N, V> & suggests,
                std::map<N, V> & already_installed,
                std::map<N, N> & obsoleted_by,
                std::map<N, std::vector< constraint_type > > & conflicts) {
            for (auto possibility : requirement) {
                auto search_installed = already_installed.find(possibility.name);
                if (search_installed != already_installed.end()) {
                    if (all_of(possibility.constraints.cbegin(),
                                possibility.constraints.cend(),
                                [&search_installed](auto constraint) {
                                    constraint((*search_installed).second)
                                })) {
                        return resolver_success_type{};
                    }
                    else {
                        return boost::none;
                    }
                }
                else {
                    auto search_conflicts = conflicts.find(possibility.name);
                    // check for blank-check conflict with _name_
                    if (search_conflicts != conflicts.cend() &&
                            (*search_conflicts).second.empty()) {
                        return boost::none;
                    }
                    else {
                        auto candidates = repo->query(possibility.name);
                        for (auto candidate : candidates) {
                            if (!all_of(possibility.constraints.cbegin(),
                                        possibility.constraints.cend(),
                                        [&candidate](auto constraint) {
                                            return constraint(candidate.version)
                                        }))
                            {
                                continue;
                            }
                            // check again for granular conflict this time
                            if (search_conflicts != conflicts.cend() &&
                                    all_of((*search_conflicts).second.cbegin(),
                                        (*search_conflicts).second.cend(),
                                        [&candidate](auto conflict) {
                                            return conflict(candidate.version)
                                        })) {
                                continue;
                            }
                            // OOOOOOKay.
                            // We'll take this mutation one at a time.
                            // newsuggests. suppose we add stuff. if it fails,
                            // we just remove it again.
                            // newalreadyinstalled. Suppose we add stuff.
                            suggests.insert(suggests.end(),
                                    candidate.suggests.begin(),
                                    candidate.suggests.end());
                            already_installed.insert(possibility.name,
                                    candidate.version);
                            // Can we do this safely yet? NO.
                            // We cannot prove yet with current code that
                            // obsoleted_by doesn't already have the
                            // given name in it already.
                            //
                            // We need to provide this guarantee by implementing
                            // code that uses this feature.
                            if (candidate.obsoletes) {
                                obsoleted_by.insert(*(candidate.obsoletes),
                                        possibility.name);
                            }
                            conflicts.insert(suggests.end(),
                                    candidate.conflicts.begin(),
                                    candidate.conflicts.end());

                            auto results = resolve(
                                    candidate.requires,
                                    suggests,
                                    already_installed,
                                    obsoleted_by,
                                    conflicts);
                            if (results) {
                                // In this case, we want the mutations above to
                                // persist, so we are clear to simply return
                                // success and leave the sets mutated for future
                                // use by the calling resolve() function.
                                return *results;
                            }
                            else {
                                // Put everything back.
                                suggests.erase(
                                        suggests.end() -
                                            candidate.suggests.size(),
                                        suggests.end());
                                already_installed.erase(possibility.name);
                                if (candidate.obsoletes) {
                                    obsoleted_by.erase(*(candidate.obsoletes));
                                }
                                conflicts.erase(
                                        conflicts.end() - candidate.conflicts.size(),
                                        conflicts.end());
                            }
                        }
                    }
                }
            }
            return boost::none;
        }

        // This is the private version
        // because in order to do stuff like
        // pass sets and maps down recursively,
        // (most) everything passed in must be mutable.
        resolver_result_type resolve(
                // A constant reference to an ordered collection.
                // Aaah, determinism.
                const order_type<N, V> & requires,
                order_type<N, V> & suggests,
                std::map<N, V> & already_installed,
                std::map<N, N> & obsoleted_by,
                std::map<N, std::vector< constraint_type> > & conflicts) {

            resolver_success_type cumulative;

            for (auto requirement : requires) {
                auto results = resolve_requirement(requirement,
                        suggests,
                        already_installed,
                        obsoleted_by,
                        conflicts
                        );
                if (results) {
                    cumulative.insert(cumulative.cend(), (*results).first(),
                            (*results).last());
                }
                else
                {
                    return boost::none;
                }
            }
            if (this->policy != suggests_policy::IGNORE) {
                for (auto suggestion : suggests) {
                    auto results = resolve_requirement(requirement,
                            suggests,
                            already_installed,
                            obsoleted_by,
                            conflicts
                            );
                    if (results) {
                        cumulative.insert(cumulative.cend(), (*results).first(),
                                (*results).last());
                    }
                    else
                    {
                        return boost::none;
                    }
                }
            }
            return cumulative;
        }

    public:
        resolver_success_type resolve(const order_type & order) const {
        }
    };
}

#endif // UDR_REPOSITORY_HPP
