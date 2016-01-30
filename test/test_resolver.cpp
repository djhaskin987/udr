/*
   Copyright 2015-2016 Daniel Jay Haskin

   Licensed under the Apache License, Name 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#define BOOST_TEST_MODULE resolverClasses
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#define UDR_UNIT_TEST
#include "resolver.hpp"
#include "memory_repository.h"

BOOST_AUTO_TEST_SUITE( resolver )

struct resolve_fixture
{
    typedef udr::memory_repository r;
    std::map<std::string,
        std::vector<r::package_type> obsoleted_by = ...;
    std::map<std::string,
        std::vector<r::package_type> literal = ...;
    std::map<std::string,
        std::vector<r::package_type> provides = ...;
    r repo(obsoleted_by, literal, provides);
    udr::resolver<mem_repo> resolver(repo);
};

BOOST_FIXUTRE_TEST_CASE( resolve_create , resolve_fixture )
{

}

BOOST_AUTO_TEST_SUITE_END()
