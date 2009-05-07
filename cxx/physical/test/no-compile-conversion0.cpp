#include <physical/physical.h>
#include <physical/quantity.h>

#define BOOST_TEST_MODULE  unit_systems

#include <boost/test/unit_test.hpp>

#include <iostream>

BOOST_AUTO_TEST_SUITE( unit_systems );

  /* THIS TEST SHOULD NOT COMPILE.
   * With non-native types (i.e. a class type instead of double for example),
   * the automatic casting does not work. */
  BOOST_AUTO_TEST_CASE( DimQuantity_cast_runtime ) {
    using namespace runtime::physical;
    using system::si;
    namespace dim = dimension;

    DimQuantity<si,dim::velocity> dsivel(Quantity(1.0));
    /* THIS LINE SHOULD NOT COMPILE: */
    BOOST_CHECK_EQUAL( Quantity(10.0)*(dsivel), Quantity(10.0) );

    /* THIS LINE SHOULD INDEED COMPILE: */
    BOOST_CHECK_EQUAL( Quantity(10.0)*static_cast<const Quantity&>(dsivel), Quantity(10.0) );
  }

BOOST_AUTO_TEST_SUITE_END();

