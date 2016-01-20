#define BOOST_TEST_MODULE make sure everything can work test
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#define UDR_UNIT_TEST
#include "gripe.hpp"

BOOST_AUTO_TEST_SUITE( gripe )

BOOST_AUTO_TEST_CASE( gripe_age )
{
    udr::Gripe g;
    BOOST_CHECK ( g.is(1) );
}

BOOST_AUTO_TEST_CASE( gripe_fail )
{
    BOOST_FAIL(true);
}

BOOST_AUTO_TEST_SUITE_END()

