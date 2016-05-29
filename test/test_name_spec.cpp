#define BOOST_TEST_MODULE name_spec
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define UDR_UNIT_TEST

#include <boost/test/unit_test.hpp>

#include <boost/variant/get.hpp>
#include <map>
#include <algorithm>
#include "name_spec.hpp"

using namespace udr;

class mock_repository : public repository<std::string, int>
{
public:
    mock_repository(const std::map<std::string, std::vector<package<std::string, int>>>& pkgs) : packages(pkgs) {}
    virtual ~mock_repository() {}

    virtual result_type<std::string, int> query(const std::string& name) const
    {
        _queries.push_back(name);
        auto item_itr = (this->packages).find(name);
        if (item_itr == (this->packages).end())
        {
            return std::vector<std::string> { std::string() + "`" + name +
                "` is not in the mock map."};
        }
        else
        {
            return item_itr->second;
        }
    }
    const std::vector<std::string> & queries() {
        return _queries;
    }

private:
    std::map<std::string, std::vector<package<std::string, int> > >
        packages = {};
    mutable std::vector<std::string> _queries = {};
};


BOOST_AUTO_TEST_SUITE(name_spec)

struct hello_repo
{
    mock_repository mr = {
        {
            {"hello", { {"hello", 45, "hello_loc"}, {"hello", 54, "col_olleh" } } }
        }
    };
};

BOOST_FIXTURE_TEST_CASE(successful_retrieval, hello_repo)
{
    auto tested = make_name_spec<std::string, int>("hello");
    auto results = tested->resolve(&mr);
    if (emessages_type* errors = boost::get<emessages_type>(&results))
    {
        BOOST_ERROR(std::string("Errors."));
    }
    else if (std::vector<package<std::string, int>>* packages =
            boost::get<std::vector<package<std::string, int>>>(&results))
    {
        BOOST_CHECK(packages->size() == 1);
        package<std::string, int> expected = { "hello", 45, "hello_loc" };
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
