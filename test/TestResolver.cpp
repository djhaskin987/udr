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

class ShouldNotResolveVisitor : public boost::static_visitor<bool> {
private:
    std::vector<NameType> expected;

public:
    ShouldNotResolveVisitor(const std::vector<NameType>& e)
        : expected(e)
        , boost::static_visitor<bool>()
    {
    }
    ShouldNotResolveVisitor(std::vector<NameType>&& e, bool g)
        : expected(std::move(e))
        , boost::static_visitor<bool>()
    {
    }

    bool operator()(const std::vector<PackageType>& packages) const
    {
        BOOST_TEST_MESSAGE("Visited failed resolution");
        return false;
    }
    bool operator()(const std::vector<NameType>& names) const
    {
        if (names == expected) {
            BOOST_TEST_MESSAGE("Visited correct unsatisfiable names");
            return true;
        }
        else {
            BOOST_TEST_MESSAGE("Visited incorrect unsatisfiable names "
                    << names[0]);
            return false;
        }
    }
};
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

class MapQuery
{
private:
    std::map<NameType, QueryResultsType> availablePackages;
public:
    MapQuery() = default;
    MapQuery(const MapQuery& other) = default;
    MapQuery(MapQuery&& other) = default;
    MapQuery& operator= (const MapQuery& other) {
        return *this = std::move(MapQuery(other));
    };
    MapQuery& operator= (MapQuery&& other) {
        this->availablePackages = std::move(other.availablePackages);
    }
    ~MapQuery() {}

    MapQuery(const std::map<NameType, QueryResultsType> & packages) :
        availablePackages(packages)
    {}

    MapQuery(std::map<NameType, QueryResultsType>&& packages) :
        availablePackages(std::move(packages))
    {}

    boost::optional<const std::vector<PackageType> &>
        operator ()(const NameType& n) {
            auto itr = availablePackages.find(n);
            if (itr == availablePackages.end()) {
                return boost::none;
            }
            else {
                return itr->second;
            }
    }
};

struct NoDependenciesFixture
{
    std::map<NameType, QueryResultsType> queryMap{
        { "a",
            { { "a", 25, "a_loc25" },
                { "a", 13, "a_loc13" } } },
        { "c",
            { { "c", 16, "c_loc16" } } }
    };
    MapQuery query{queryMap};
};

BOOST_FIXTURE_TEST_CASE(TestSimpleRetrieval, NoDependenciesFixture)
{
    std::vector<UDR::PackageSpec<PackageType> > request{ { "a" } };
    std::vector<PackageType> expected{ { "a", 25, "a_loc25" } };

    auto result = UDR::resolve(
        request,
        query);
    BOOST_CHECK(boost::apply_visitor(ShouldResolveVisitor(expected), result));
    request = { { "c" } };
    expected = { { "c", 16, "c_loc16" } };

    result = UDR::resolve(
        request,
        query);
    BOOST_CHECK(boost::apply_visitor(ShouldResolveVisitor(expected), result));

}

BOOST_FIXTURE_TEST_CASE(TestSimpleUnsatisfiable, NoDependenciesFixture)
{
    std::vector<UDR::PackageSpec<PackageType> > request{ { "b" } };
    std::vector<NameType> expected{ "b" };

    auto result = UDR::resolve(request, query);
    BOOST_CHECK(boost::apply_visitor(ShouldNotResolveVisitor(expected),
                result));
}

BOOST_AUTO_TEST_SUITE_END()
