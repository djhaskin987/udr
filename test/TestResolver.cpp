#define BOOST_TEST_MODULE Resolver
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

class ShouldResolveVisitor : public boost::static_visitor<bool> {
private:
    std::vector<PackageType> expected;

public:
    ShouldResolveVisitor(const std::vector<PackageType>& e)
        : expected(e)
        , boost::static_visitor<bool>()
    {
    }
    ShouldResolveVisitor(std::vector<PackageType>&& e, bool g)
        : expected(std::move(e))
        , boost::static_visitor<bool>()
    {
    }

    bool operator()(const std::vector<PackageType>& packages) const
    {
        if (packages == expected) {
            BOOST_TEST_MESSAGE("Visited correct packages");
            return true;
        }
        else {
            BOOST_TEST_MESSAGE("Visited incorrect packages " << packages[0].name);
            return false;
        }
    }
    bool operator()(const std::vector<NameType>& names) const
    {
        BOOST_TEST_MESSAGE("Visited failed resolution");
        return false;
    }
};

BOOST_AUTO_TEST_SUITE(NoDependencies)

BOOST_AUTO_TEST_CASE(TestSimpleRetrieval)
{
    std::map<NameType, QueryResultsType> queryMap{
        { std::string("a"),
            { { "a", 25, "a_loc25" },
                { "a", 13, "a_loc13" },
                { "c", 17, "c_loc16" } } }
    };

    std::vector<UDR::PackageSpec<PackageType> > requestA{ { "a" } };

    auto result = UDR::resolve(
        requestA,
        [&](const NameType& n) -> boost::optional<const std::vector<PackageType>&> {
            auto itr = queryMap.find(n);
            if (itr == queryMap.end()) {
                return boost::none;
            }
            else {
                return itr->second;
            }
        });
    std::vector<PackageType> expected{ { "a", 25, "a_loc25" } };

    BOOST_CHECK(boost::apply_visitor(ShouldResolveVisitor(expected), result));
}

BOOST_AUTO_TEST_SUITE_END()
