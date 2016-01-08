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
#ifndef UDR_TYPES_HPP
#define UDR_TYPES_HPP 1


namespace udr {
    typedef std::string url_type;
    /*
     * 
     */
    typedef std::unordered_set<std::pair<udr::constraint<version_type>,
                                    version_type> > constraints_type;
    typedef std::pair<name_type, constraints_type> possibility_type;
    typedef std::vector<possibility_type> requirement_type;
    typedef std::vector<requirement_type> requirements_type;
    typedef std::unordered_map<name_type, constraints_type> conflicts_type;
    typedef std::unordered_map<name_type, name_type> obsoleted_by_type;
    typedef std::tuple<version_type, url_type, obsoletes_type, conflicts_type>
    found_package_type;
    typedef std::unordered_map<name_type,
                                > satisfied_results_type;
    // feels functional-y, not right.
    typedef enum class {
        UNSATISFIABLE,
            SATISFIED,
            UNNEEDED
            } result_tag_type;
    // magic happens here
    typedef std::tuple<result_tag_type, std::vector<std::pair<name_type, constraints_type> > -or- std::unordered_map<name_type, std::tuple<version_type, url_type, obsoletes_type, conflicts_type> > -or- std::tuple<name_type, resolve_results_type;
}

#endif
