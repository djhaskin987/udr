/*
   Copyright 2016 Daniel Jay Haskin

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
#define BOOST_TEST_MODULE VersionComparison
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <memory>

#define UDR_UNIT_TEST
#include "VersionComparison.hpp"
#include "StringName.hpp"
#include "IntegerVersion.hpp"

struct VersionComparisonFixture
{
    UDR::ConstVersionPtr u = UDR::IntegerVersion::Create(48);
    UDR::ConstVersionPtr v = UDR::IntegerVersion::Create(47);
    UDR::ConstVersionPtr s = UDR::IntegerVersion::Create(46);
    UDR::ConstVersionPtr t = UDR::IntegerVersion::Create(47);

    VersionComparisonFixture() = default;
    ~VersionComparisonFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE( VersionComparison , VersionComparisonFixture )

BOOST_AUTO_TEST_CASE( GreaterThan )
{
    UDR::ConstVersionComparisonPtr a =
        UDR::VersionComparison::Create(
                UDR::VersionRelation::GREATER_THAN,
                v.clone());
    BOOST_CHECK(!a->satisfiedBy(u));
    BOOST_CHECK(!a->satisfiedBy(s));
    BOOST_CHECK(a->satisfiedBy(t));
}

BOOST_AUTO_TEST_SUITE_END()
