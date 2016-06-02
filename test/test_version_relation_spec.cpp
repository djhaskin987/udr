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
                        {"hello", 54, "col_olleh" },
                        {"hello", 45, "hello_loc2"},
                        {"hello", 44, "hello_loc"}
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
        auto tested = make_vr_spec<std::string, int, R>(name,version);
        auto results = tested->resolve(&mr);
        emessages_type* errors = boost::get<emessages_type>(&results);
        BOOST_CHECK(errors == nullptr);
        std::vector<package<std::string, int>>* packages =
                boost::get<std::vector<package<std::string, int>>>(&results);
        BOOST_REQUIRE(packages != nullptr);
        BOOST_CHECK(packages->size() == 1);
        BOOST_CHECK(packages->begin()->name == expected.name);
        BOOST_CHECK(packages->begin()->version == expected.version);
        BOOST_CHECK(packages->begin()->location == expected.location);

    }
}

BOOST_AUTO_TEST_SUITE(name_spec)


BOOST_FIXTURE_TEST_CASE(successful_retrieval, test_vr::hello_repo)
{
    test_vr::resolve_for_success<std::less>("hello", 45, mr,
        { "hello", 44, "hello_loc" });
}

BOOST_FIXTURE_TEST_CASE(order_is_correct, test_vr::hello_repo)
{
    test_vr::resolve_for_success<std::greater_equal>("hello", 0, mr,
                        {"hello", 54, "col_olleh" });
}

BOOST_FIXTURE_TEST_CASE(bad_name, test_vr::hello_repo)
{
    auto tested = make_vr_spec<std::string, int, std::equal_to>("goodbye", 45);
    auto results = tested->resolve(&mr);
    std::vector<package<std::string,int>>* packages =
            boost::get<std::vector<package<std::string, int>>>(&results);
    BOOST_CHECK(packages == nullptr);
}

BOOST_FIXTURE_TEST_CASE(bad_version, test_vr::hello_repo)
{
    auto tested = make_vr_spec<std::string, int>("hello", 81);
    auto results = tested->resolve(&mr);
    std::vector<package<std::string,int>>* packages =
            boost::get<std::vector<package<std::string, int>>>(&results);
    BOOST_CHECK(packages == nullptr);
}

BOOST_AUTO_TEST_SUITE_END()
