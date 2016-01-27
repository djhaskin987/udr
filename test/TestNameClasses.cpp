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
#define BOOST_TEST_MODULE make sure everything can work test
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <memory>

#define UDR_UNIT_TEST
#include "Name.hpp"
#include "StringName.hpp"

class TestName : public UDR::Name
{
    public:
        TestName() = default;
        virtual ~TestName() {}

        virtual bool equals(const UDR::ConstNamePtr & other) const override
        {
            return false;
        }
};

BOOST_AUTO_TEST_SUITE( StringName )

BOOST_AUTO_TEST_CASE( name )
{
    UDR::ConstStringNamePtr a = std::unique_ptr<const UDR::StringName>(
            static_cast<const UDR::StringName*>(
                UDR::StringName::Create("I AM MORDAC").release()));
    BOOST_CHECK_EQUAL(a->getName(), std::string("I AM MORDAC"));
}

struct NameEqualsFixture
{
    UDR::ConstNamePtr a = UDR::StringName::Create("I AM MORDAC");
    UDR::ConstNamePtr b = UDR::StringName::Create("I AM MORDAC");
    UDR::ConstNamePtr c = UDR::StringName::Create("I AM WEB MISTRESS MIN");
    NameEqualsFixture() = default;
    ~NameEqualsFixture() = default;
};

BOOST_FIXTURE_TEST_CASE( EqualsReflection , NameEqualsFixture )
{
    BOOST_CHECK(a->equals(a));
}

BOOST_FIXTURE_TEST_CASE( EqualsOther , NameEqualsFixture )
{
    BOOST_CHECK(a->equals(b));
}

BOOST_FIXTURE_TEST_CASE( EqualsNotEqual , NameEqualsFixture )
{
    BOOST_CHECK(! b->equals(c));
}

struct NameTypesFixture
{
    UDR::ConstNamePtr badTyped = std::unique_ptr<const UDR::Name>(
            static_cast<const UDR::Name*>(new TestName()));
    UDR::ConstNamePtr goodTyped = UDR::StringName::Create("Hilbert");
    NameTypesFixture() = default;
    ~NameTypesFixture() = default;
};

BOOST_FIXTURE_TEST_CASE( equalsTypes, NameTypesFixture )
{
    BOOST_CHECK_THROW(goodTyped->equals(badTyped), UDR::NameMismatchException);
}

BOOST_AUTO_TEST_SUITE_END()
