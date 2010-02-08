#include <physical/physical.h>
#include <physical/runtime.h>

#define BOOST_TEST_MODULE  include_guards

#include <boost/test/unit_test.hpp>

#include <iostream>

/* THIS TEST SHOULD NOT COMPILE.
 * With non-native types (i.e. a class type instead of double for example),
 * the automatic casting does not work. */
BOOST_AUTO_TEST_CASE( runtime_second ) {
  {
    using runtime::physical::Quantity;
    namespace constant = runtime::physical::constant;
    Quantity m_e = constant::si::m_e;
  }

  {
    namespace constant = physical::constant;
    double m_e = constant::si::m_e;
    if (m_e == 0)
      BOOST_FAIL("m_e not supposed to be zero!");
  }
}

