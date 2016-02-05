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
#ifndef UDR_TESTING_PACKAGE_HPP
#define UDR_TESTING_PACKAGE_HPP 1

#include <string>
namespace UDRTest
{
    struct TestingPackage
    {
        typedef std::string NameType;
        typedef int VersionType;
        typedef std::string LocationType;
        NameType name;
        VersionType version;
        LocationType location;
    };
}

#endif // UDR_TESTING_PACKAGE_HPP
