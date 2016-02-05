#define BOOST_TEST_MODULE make sure everything can work test
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define UDR_UNIT_TEST

#include <map>
#include <vector>
#include <utility>

#include <boost/test/unit_test.hpp>
#include <boost/optional.hpp>
#include <boost/variant/static_visitor.hpp>

#include "PackageSpec.hpp"
#include "Resolver.hpp"
#include "TestingPackage.hpp"

typedef UDRTest::TestingPackage PackageType;
typedef PackageType::NameType NameType;
typedef PackageType::VersionType VersionType;
typedef std::vector<PackageType> QueryResultsType;
typedef std::vector<PackageType> ResolveResultsType;

class TestingResolveVisitor : public boost::static_visitor<bool>
{
    private:
        std::vector<PackageType> expected;
        bool isGood;

    public:
        TestingResolveVisitor(const std::vector<PackageType>& e, bool g) :
            expected(e), isGood(g), boost::static_visitor<bool>() {}
        TestingResolveVisitor(std::vector<PackageType>&& e, bool g) :
            expected(std::move(e)), isGood(g), boost::static_visitor<bool>() {}

        bool operator ()(const std::vector<PackageType>& packages) const
        {
            if (packages == expected)
            {
                return isGood;
            }
            else
            {
                return !isGood;
            }
        }
        bool operator ()(const std::vector<NameType>& names) const
        {
            return !isGood;
        }
};


BOOST_AUTO_TEST_CASE( TestSimpleRetrieval )
{
    std::map<NameType, QueryResultsType> queryMap {
        { std::string("a"), {{"a", 25, "a_loc25"},
                             {"a", 13, "a_loc13"},
                             {"c", 17, "c_loc16"} } }
    };

    std::vector<UDR::PackageSpec<PackageType> > requestA {
        { "a" }
    };


    auto result = UDR::resolve(requestA,
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
    std::vector<PackageType> expected{
        {"a", 25, "a_loc25"}
    };

    BOOST_CHECK ( boost::apply_visitor(
                TestingResolveVisitor(expected, true), result) );
}
