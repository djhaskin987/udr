/*
   Copyright 2016 Daniel Jay Haskin

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
#include <boost/variant.hpp>
#include <algorithm>

namespace UDR {
template <typename PackageType, typename QueryType>

boost::variant<std::vector<PackageType>,
               std::vector<typename PackageType::NameType>> resolve(
                       const std::vector<PackageSpec<PackageType>> &requirements,
        QueryType query) {
  std::vector<PackageType> result;

  for (auto requirement = requirements.cbegin();
       requirement != requirements.cend(); requirement++) {
    auto answer = query(requirement->name);
    if (!answer) {
      return std::vector<typename PackageType::NameType>{requirement->name};
    } else {
      result.push_back(*(answer->begin()));
    }
  }
  /*
   * for each requirement, try to find it.
   */
  return result;
}
}

#endif // UDR_RESOLVER_HPP
