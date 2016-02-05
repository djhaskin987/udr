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
#ifndef UDR_PACKAGE_SPEC_HPP
#define UDR_PACKAGE_SPEC_HPP 1

#include <string>
namespace UDR
{
    template <typename P>
    struct PackageSpec
    {
        typedef typename P::NameType NameType;
        NameType name;
    };
}

#endif // UDR_PACKAGE_SPEC_HPP
