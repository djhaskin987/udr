#define BOOST_TEST_MODULE make sure everything can work test
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#define UDR_UNIT_TEST
#include "IntegerVersion.hpp"

BOOST_AUTO_TEST_SUITE( IntegerVersion )

BOOST_AUTO_TEST_CASE( compare )
{
    UDR::ConstVersionPtr a = UDR::IntegerVersion::Create(12);
    UDR::ConstVersionPtr b = UDR::IntegerVersion::Create(42);
    UDR::ConstVersionPtr c = UDR::IntegerVersion::Create(42);

    int lt = a->compare(b);

    BOOST_CHECK_LT(lt, 0);

    int gt = b->compare(a);

    BOOST_CHECK_GT(gt, 0);

    int eq = b->compare(b);

    BOOST_CHECK_EQUAL(eq, 0);

    int eq2 = b->compare(c);

    BOOST_CHECK_EQUAL(eq2, 0);
}


BOOST_AUTO_TEST_CASE( match )
{
    UDR::ConstVersionPtr a = UDR::IntegerVersion::Create(12);
    UDR::ConstVersionPtr b = UDR::IntegerVersion::Create(42);
    UDR::ConstVersionPtr c = UDR::IntegerVersion::Create(41);
    UDR::ConstVersionPtr d = UDR::IntegerVersion::Create(49);
    BOOST_CHECK( ! a->matches(b) );
    BOOST_CHECK( b->matches(c) );
    BOOST_CHECK( c->matches(d) );
    BOOST_CHECK( d->matches(c) );
    BOOST_CHECK( b->matches(d) );
}

BOOST_AUTO_TEST_SUITE_END()
