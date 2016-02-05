#define BOOST_TEST_MODULE make sure everything can work test
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/optional.hpp>

#define UDR_UNIT_TEST
#include <map>
#include <vector>
#include "PackageSpec.hpp"
#include "Resolver.hpp"
#include "TestingPackage.hpp"

typedef UDRTest::TestingPackage PackageType;
typedef PackageType::NameType NameType;
typedef PackageType::VersionType VersionType;
typedef std::vector<PackageType> QueryResultsType;

BOOST_AUTO_TEST_CASE( TestSimpleRetrieval )
{
    std::map<NameType, QueryResultsType> queryMap {
        { std::string("a"), {{"a", 13, "a_loc13"},
                             {"a", 25, "a_loc25"},
                             {"c", 17, "c_loc16"} } }
    };

    std::vector<UDR::PackageSpec<PackageType> > requestA = {
        { "a" }
    };

    std::vector<PackageType> result = UDR::resolve(requestA,
            [&](const NameType& n) ->
                boost::optional<const std::vector<PackageType> &> {
                auto itr = queryMap.find(n);
                if (itr == queryMap.end()) {
                    return boost::none;
                }
                else
                {
                    return itr->second;
                }
            });

    BOOST_CHECK ( true );
}
