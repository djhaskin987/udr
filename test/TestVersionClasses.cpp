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
#define BOOST_TEST_MODULE VersionClasses
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#define UDR_UNIT_TEST
#include "IntegerVersion.hpp"

class TestVersion : public UDR::Version
{
    public:
        TestVersion() = default;
        virtual ~TestVersion() {}

        virtual int compare(const UDR::ConstVersionPtr & other) const override
        {
            return -1;
        }

        virtual bool matches(const UDR::ConstVersionPtr & other) const override
        {
            return false;
        }
};

BOOST_AUTO_TEST_SUITE( IntegerVersion )

struct VersionTypesFixture
{
    UDR::ConstVersionPtr badTyped = std::unique_ptr<const UDR::Version>(
            static_cast<const UDR::Version*>(new TestVersion()));
    UDR::ConstVersionPtr goodTyped = UDR::IntegerVersion::Create(12);
    VersionTypesFixture() = default;
    ~VersionTypesFixture() = default;
};

BOOST_FIXTURE_TEST_CASE( compareTypes, VersionTypesFixture )
{
    BOOST_CHECK_THROW(goodTyped->compare(badTyped), UDR::VersionMismatchException);
}

BOOST_FIXTURE_TEST_CASE( matchesTypes, VersionTypesFixture )
{
    BOOST_CHECK_THROW(goodTyped->matches(badTyped), UDR::VersionMismatchException);
}

BOOST_AUTO_TEST_CASE( compare )
{
    UDR::ConstVersionPtr a = UDR::IntegerVersion::Create(12);
    UDR::ConstVersionPtr b = UDR::IntegerVersion::Create(42);
    UDR::ConstVersionPtr c = UDR::IntegerVersion::Create(42);

    int lt = a->compare(b);

    BOOST_CHECK_LT(lt, 0);

    int gt = b->compare(a);

    BOOST_CHECK_GT(gt, 0);

    int eq = b->compare(b);

    BOOST_CHECK_EQUAL(eq, 0);

    int eq2 = b->compare(c);

    BOOST_CHECK_EQUAL(eq2, 0);
}


BOOST_AUTO_TEST_CASE( match )
{
    UDR::ConstVersionPtr a = UDR::IntegerVersion::Create(12);
    UDR::ConstVersionPtr b = UDR::IntegerVersion::Create(42);
    UDR::ConstVersionPtr c = UDR::IntegerVersion::Create(41);
    UDR::ConstVersionPtr d = UDR::IntegerVersion::Create(49);
    BOOST_CHECK( ! a->matches(b) );
    BOOST_CHECK( b->matches(c) );
    BOOST_CHECK( c->matches(d) );
    BOOST_CHECK( d->matches(c) );
    BOOST_CHECK( b->matches(d) );
}

BOOST_AUTO_TEST_SUITE_END()
