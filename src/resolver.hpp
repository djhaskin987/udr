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

<<<<<<< Updated upstream
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
using std::function<bool(const V&, const V&)> = constraint_type;
template <typename N, typename V>
using std::pair<N, constraint_type<V> > = specifier_type;
template <typename N, typename V>
using std::vector<specifier_type<N, V> > = possibilities_type;
template <typename N, typename V>
using std::vector<possibilities_type<N, V> > = order_type;
template <typename N, typename V>
using std::tuple<V, // version
    url_type, // URL
    order_type<N, V>, // requires
    boost::optional<N>, // *obsoletes* (not obsoleted_by), maybe
    order_type<N, V> > // suggests
    = package_type;
template <typename N, typename V>
using

    template <typename N, typename V>
    class repository {
public:
    typedef N name_type;
    typedef V version_type;
    virtual std::vector<package_type> query(const N& name) const = 0;
};

template <typename N, typename V>
class resolver {
private:
    typedef std::vector<std::pair<N, std::set<constraint<V> > > >
        resolver_failed_type;
    typedef std::pair<name_type, resolver_success_type> resolver_unneeded_type;
    typedef boost::variant<resolver_success_type,
        resolver_failed_type,
        resolver_unneeded_type> resolver_result_type;
    typedef std::vector<std::vector<std::pair<N, std::set<constraint<V> > > > >
        order_type;
=======
#include <package.hpp>

namespace udr
{

    enum class suggests_policy {
        REQUIRED,
        BEST_EFFORT,
        IGNORE
    };
    template <typename N, typename V>
    class resolver {
    public:
    private:
        //suggests_policy policy;
        // herein lies a lot of typedefs and the use of boost::variant.
        // Please excuse my heavy LISP accent.
        // Or should I just say, pleathe excuthe my lithp? :P
        //typedef std::vector<package<N,V> > resolver_success_type;
        //typedef order_type<N, V> resolver_failure_type;
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
        /* typedef boost::optional<resolver_success_type>
            resolver_result_type;

>>>>>>> Stashed changes

        const repository *repo;


        void find_candidate(requirement) {
            for (auto possibility : requirement)
            {
                auto name = possibility.first;
                auto possibility_constraints = possibility.second;

                auto obs_itr = obsoleted_by.find(name);
                boost::optional<name_type> obs_name = boost::none;
                if (obs_itr != obsoleted_by.end()) {
                    obs_name = obs_itr->second;
                }
                if (already_installed.find(name) != already_installed.end()) {
                    return boost::none;
                }
                else if (conflicts.find(name) != conflicts.end() &&
                         conflicts[name].size() == 0)
                {
                    // clearly no candidate will win, so don't query, just
                    // go.
                    continue;
                }

                auto candidates repo->query(name);
                auto candidate_itr =
                    find_if(candidates.cbegin(), candidates.cend(),
                            [&](auto candidate) {
                                version_type c_ver;
                                url_type _;
                                std::vector<std::vector<std::pair<name_type, std::set<constraint> > > >
                                c_reqs, c_suggests;
                                std::map<name_type, std::set<constraint> > c_conflicts;
                                boost::optional<name_type> c_ob_by;
                                std::tie(c_ver, _, c_reqs, c_conflicts, c_ob_by, c_suggests) =
                                candidate;
                                if (conflicts.find(name) != conflicts.end() &&
                                    std::all_of(possibility_constraints,
                                                [&cver](auto constraint) {
                                                    constraint(c_ver)
                                                        })) {
                                    return false;
                                }
                                else
                                {
                                    // clause where I'm not in conflict.
                                    // here comes the ugly recursive call.
                                }
                            });
                if (candidate_itr != candidates.end()) {
                    return *candidate_itr;
                }
            }
        }
        
        resolver_result_type resolve(
            const std::vector<std::vector<std::pair<name_type, std::set<constraint> > > > & order,
            std::map<name_type, version_type> & already_installed,
            std::map<name_type, name_type> & obsoleted_by,
            std::map<name_type, std::set<constraint> > & conflicts,
            std::map<name_type, std::set<constraint> > & already_considered) {
            // possibly reorder here before something happens
            // Here, if there are any possibilities common among the
            // requirements, we move them to the front of the vector
            // of possibilities in which they reside, in order of
            // which ones are most common.
            // After reordering, we continue as usual
            for (auto requirement : order)
            {
                auto candidate = find_candidate(requirement);
                if (candidate) {
                    version_type c_ver;
                    url_type c_url;
                    std::vector<std::vector<std::pair<name_type, std::set<constraint> > > >
                                c_reqs, c_suggests;
                    std::map<name_type, std::set<constraint> > c_conflicts;
                    boost::optional<name_type> c_ob_by;
                    std::tie(c_ver, c_url, c_reqs, c_conflicts, c_ob_by, c_suggests) =
                        *candidate;
                    
                }
                else
                {
                    return resolver_success_type{};
                }

                if (no possibilities were resolved)
                {
                    return unsatisfiable;
                }
            }
        }
    public:
        resolver_success_type resolve(const order_type & order) const {
<<<<<<< Updated upstream
            // call *actual* resolver here
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
                        std::vector<std::pair<name_type, std::set<constraint_type> > > lst;
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
                            std::forwared_list<std::pair<name_type, set<constraint_type> > >
                                lst;
                            lst.splice(lst.cend(),candidate_dep_urls.error().value());
                            return lst;
                        }
                        result.push_back(candidate_url);
                    }
                }
                return result;
            }
=======
        }
    */
>>>>>>> Stashed changes
};
}

#endif // UDR_REPOSITORY_HPP
