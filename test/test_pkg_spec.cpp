#define BOOST_TEST_MODULE pkg_spec
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define UDR_UNIT_TEST

#include <boost/test/unit_test.hpp>

#include <map>
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


BOOST_AUTO_TEST_SUITE(pkg_spec)

BOOST_AUTO_TEST_CASE(basic)
{
    std::map<std::string, std::vector<package<std::string, int>>> packages = {
        {"hello", { {"hello", 45, "hello_loc"} } }
    };
    mock_repository mr = {packages};
    std::unique_ptr<spec<std::string, int>> tested(udr::name_spec<std::string, int>());
}

BOOST_AUTO_TEST_SUITE_END()
