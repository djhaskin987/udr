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

namespace test_vr
{
    struct hello_repo
    {
        udr::mock_repository mr = {
            {
                {
                    "hello", {
                        {"hello", 54, nullptr},
                        {"hello", 45, nullptr},
                        {"hello", 44, nullptr}
                    }
                }
            }
        };
    };

    template <template <typename T> typename R = std::greater_equal>
    void resolve_for_success(const std::string& name, int version,
            const udr::mock_repository& mr,
            const package<std::string, int>& expected)
    {
        auto tested = make_vr_spec<udr::package<std::string, int>, R>(name,version);
        auto results = tested->resolve(&mr);
        BOOST_REQUIRE(results);
        BOOST_CHECK(results->size() == 1);
        BOOST_CHECK(results->begin()->name == expected.name);
        BOOST_CHECK(results->begin()->version == expected.version);
    }
}

BOOST_AUTO_TEST_SUITE(name_spec)


BOOST_FIXTURE_TEST_CASE(successful_retrieval, test_vr::hello_repo)
{
    test_vr::resolve_for_success<std::less>("hello", 45, mr,
        { "hello", 44, nullptr });
}

BOOST_FIXTURE_TEST_CASE(order_is_correct, test_vr::hello_repo)
{
    test_vr::resolve_for_success<std::greater_equal>("hello", 0, mr,
                        {"hello", 54, nullptr});
}

BOOST_FIXTURE_TEST_CASE(bad_name, test_vr::hello_repo)
{
    auto tested = make_vr_spec<udr::package<std::string, int>, std::equal_to>("goodbye", 45);
    auto results = tested->resolve(&mr);
    std::vector<package<std::string,int>>* packages =
            boost::get<std::vector<package<std::string, int>>>(&results);
    BOOST_CHECK(packages == nullptr);
}

BOOST_FIXTURE_TEST_CASE(bad_version, test_vr::hello_repo)
{
    auto tested = make_vr_spec<udr::package<std::string, int>>("hello", 81);
    auto results = tested->resolve(&mr);
    BOOST_CHECK(!results);
}

BOOST_AUTO_TEST_SUITE_END()
