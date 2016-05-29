#define BOOST_TEST_MODULE Resolver
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define UDR_UNIT_TEST

#include <boost/test/unit_test.hpp>

#include <map>
#include "pkg_spec.hpp"

using namespace udr;

class mock_repository : public repository<std::string, int>
{
public:
    virtual ~mock_repository() {}

    virtual result_type<std::string, int> query(const std::string name)
    {
        return std::vector<std::string>();
    }
private:
    std::map<std::string, std::vector<package<std::string, int> > >
        packages = {};
};


BOOST_AUTO_TEST_SUITE(spec)

BOOST_AUTO_TEST_CASE(Dummy)
{
}

BOOST_AUTO_TEST_SUITE_END()
