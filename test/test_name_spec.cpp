#define BOOST_TEST_MODULE name_spec
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define UDR_UNIT_TEST

#include <boost/test/unit_test.hpp>
#include <boost/variant/get.hpp>
#include "mock_repository.hpp"
#include "name_spec.hpp"

using namespace udr;


BOOST_AUTO_TEST_SUITE(name_spec)

struct hello_repo
{
    mock_repository mr = {
        {
            {"hello", { {"hello", 45, nullptr}, {"hello", 54, nullptr} } }
        }
    };
};

BOOST_FIXTURE_TEST_CASE(successful_retrieval, hello_repo)
{
    auto tested = make_name_spec<udr::package<std::string, int>>("hello");
    auto results = tested->resolve(&mr);
    BOOST_REQUIRE(results);
    BOOST_CHECK(results->size() == 1);
    package<std::string, int> expected = { "hello", 45, nullptr };
    BOOST_CHECK(results->begin()->name == expected.name);
    BOOST_CHECK(results->begin()->version == expected.version);
}

BOOST_FIXTURE_TEST_CASE(nothing_found, hello_repo)
{
    auto tested = make_name_spec<udr::package<std::string, int>>("goodbye");
    auto results = tested->resolve(&mr);
    BOOST_CHECK(!results);
}

BOOST_AUTO_TEST_SUITE_END()
