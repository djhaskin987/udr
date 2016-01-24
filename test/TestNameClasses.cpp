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

#define UDR_UNIT_TEST
#include "Name.hpp"
#include "StringName.hpp"

class TestName : public Name
{
    public:
        TestName() = default;
        virtual ~TestName() {}

        virtual bool equals(const ConstNamePtr & other) const override
        {
            return false;
        }
};

BOOST_AUTO_TEST_SUITE( StringName )

class TestName : public Name
{
    public:
        TestVersion() = default;
        virtual ~TestVersion() {}

        virtual int compare(const ConstVersionPtr & other) const override
        {
            return -1;
        }

        virtual bool matches(const ConstVersionPtr & other) const override
        {
            return false;
        }
}

BOOST_AUTO_TEST_CASE( name )
{
    UDR::ConstStringNamePtr a = UDR::StringName::Create("I AM MORDAC");
    BOOST_CHECK_EQUAL(a->name(), std::string("I AM MORDAC"));
}

BOOST_AUTO_TEST_CASE( equals )
{
    UDR::ConstNamePtr a = UDR::StringName::Create("I AM MORDAC");
    UDR::ConstNamePtr b = UDR::StringName::Create("I AM MORDAC");
    UDR::ConstNamePtr c = UDR::StringName::Create("I AM WEB MISTRESS MIN");
    BOOST_CHECK(a->equals(a));
    BOOST_CHECK(a->equals(b));
    BOOST_CHECK(! b->equals(c));
}

BOOST_AUTO_TEST_CASE( equals_exception )
{
}

BOOST_AUTO_TEST_SUITE_END()
