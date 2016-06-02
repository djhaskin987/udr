#define BOOST_TEST_MODULE name_spec
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define UDR_UNIT_TEST

#include <boost/test/unit_test.hpp>

#include <boost/variant/get.hpp>
#include <algorithm>
#include "version_relation_spec.hpp"
#include "mock_repository.hpp"

using namespace udr;

BOOST_AUTO_TEST_SUITE(name_spec)

struct hello_repo
{
    udr::mock_repository mr = {
        {
            {
                "hello", {
                    {"hello", 44, "hello_loc"},
                    {"hello", 45, "hello_loc2"},
                    {"hello", 54, "col_olleh" }
                }
            }
        }
    };
};

BOOST_FIXTURE_TEST_CASE(successful_retrieval, hello_repo)
{
    auto tested = make_vr_spec<std::string, int, std::less>("hello", 45);
    auto results = tested->resolve(&mr);
    if (emessages_type* errors = boost::get<emessages_type>(&results))
    {
        BOOST_ERROR(std::string("Errors."));
    }
    else if (std::vector<package<std::string, int>>* packages =
            boost::get<std::vector<package<std::string, int>>>(&results))
    {
        BOOST_CHECK(packages->size() == 1);
        package<std::string, int> expected = { "hello", 44, "hello_loc" };
        BOOST_CHECK(packages->begin()->name == expected.name);
        BOOST_CHECK(packages->begin()->version == expected.version);
        BOOST_CHECK(packages->begin()->location == expected.location);
    }
}

BOOST_FIXTURE_TEST_CASE(nothing_found, hello_repo)
{
    auto tested = make_name_spec<std::string, int>("goodbye");
    auto results = tested->resolve(&mr);
    if (std::vector<package<std::string,int>>* packages =
            boost::get<std::vector<package<std::string, int>>>(&results))
    {
        BOOST_ERROR(std::string() +
                "An error should have been reported when querying for " +
                "a non existent package.");
    }
}

BOOST_AUTO_TEST_SUITE_END()
