#define BOOST_TEST_MODULE  infix

#include <physical/calc/infix.h>

#include <boost/test/unit_test.hpp>

#include <complex>
#include <iostream>

namespace {
  using runtime::physical::Quantity;
  using runtime::physical::calc::InfixCalc;

  void prepareCalculator() {
    /* prepare infix units calculator. */
    using runtime::physical::calc::symbol;
    InfixCalc::base_calc & calc = InfixCalc::instance();
  
    /* clear the old symbols out */
    calc.symbols.clear();
    calc.addMathLib();
    calc.addPhysicalUnits();

    calc.exec("from physical::constant import *");
    calc.exec("from physical::unit import *");
    calc.exec("from physical import 'unit::pi'");
    calc.exec("from physical import 'element::.*'");
  }

}


BOOST_AUTO_TEST_SUITE( InFixCalc );//{

  BOOST_AUTO_TEST_CASE( simple_parse ) {
    prepareCalculator();

    BOOST_CHECK_CLOSE(
      InfixCalc::instance().parse( "pi*(0.417*nm)^2").getCoeff<double>(),
      5.4628840494007563e-19,
      1e-10
    );
  }

BOOST_AUTO_TEST_SUITE_END();//}

