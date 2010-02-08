#define BOOST_TEST_MODULE  physical_calc_Driver

#include <physical/calc/Driver.h>
#include <physical/calc/symbol.h>

#include <boost/test/unit_test.hpp>

#include <complex>
#include <iostream>

namespace {
  using runtime::physical::Quantity;
  using runtime::physical::calc::Driver;
  using runtime::physical::calc::symbol;

  void prepareCalculator() {
    /* prepare infix units calculator. */
    Driver & calc = Driver::instance();
  
    /* clear the old symbols out */
    calc.symbols.clear();
    calc.addMathLib();
    calc.addPhysicalUnits();

    calc.exec("from physical::constant import *");
    calc.exec("from physical::unit import *");
    calc.exec("from physical import 'unit::pi'");
    calc.exec("from physical import 'element::.*'");
  }

  void cleanCalculator() {
    /* prepare infix units calculator. */
    Driver & calc = Driver::instance();
  
    /* clear the old symbols out */
    calc.symbols.clear();
  }

}


BOOST_AUTO_TEST_SUITE( CalculatorDriver );//{

  BOOST_AUTO_TEST_CASE( simple_parse ) {
    prepareCalculator();

    BOOST_CHECK_CLOSE(
      Driver::instance().eval( "pi*(0.417*nm)^2").getCoeff<double>(),
      5.4628840494007563e-19,
      1e-10
    );

    cleanCalculator();
  }

  BOOST_AUTO_TEST_CASE( assignment ) {
    Driver & calc = Driver::instance();
    calc.symbols.clear();

    double v0 = calc.eval( "v0 = v1 = 10" ).getCoeff<double>();
    symbol::table::const_iterator it = calc.symbols.find("v0");
    if ( it == calc.symbols.end() )
      BOOST_FAIL("symbol 'v0' was not assigned!");
    else
      BOOST_CHECK_EQUAL( it->second.evaluate().getCoeff<double>(), v0);

    it = calc.symbols.find("v1");
    if ( it == calc.symbols.end() )
      BOOST_FAIL("symbol 'v1' was not assigned!");
    else
      BOOST_CHECK_EQUAL( it->second.evaluate().getCoeff<double>(), v0);

    calc.symbols.clear();
  }

  BOOST_AUTO_TEST_CASE( expressions ) {
    Driver & calc = Driver::instance();
    calc.symbols.clear();

    BOOST_CHECK_CLOSE( calc.eval( "1 + 1" ).getCoeff<double>(), 2., 1e-10 );
    BOOST_CHECK_CLOSE( calc.eval( "1 - 1" ).getCoeff<double>(), 0., 1e-10 );
    BOOST_CHECK_CLOSE( calc.eval( "1 + 1 - 1" ).getCoeff<double>(), 1., 1e-10 );
    BOOST_CHECK_CLOSE( calc.eval( "1 - 1 + 1" ).getCoeff<double>(), 1., 1e-10 );
    BOOST_CHECK_CLOSE( calc.eval( "1 - 2 + 1 + 1" ).getCoeff<double>(), 1., 1e-10 );
    BOOST_CHECK_CLOSE( calc.eval( "2*3 + 2^3" ).getCoeff<double>(), 14., 1e-10 );
    BOOST_CHECK_CLOSE( calc.eval( "9/3 + 5 % 2" ).getCoeff<double>(), 4., 1e-10 );
    BOOST_CHECK_CLOSE( calc.eval( "-3 + 2^-1 + 2*3" ).getCoeff<double>(), 3.5, 1e-10 );
    BOOST_CHECK_CLOSE( calc.eval( "2^3^2" ).getCoeff<double>(), 512., 1e-10 );
    BOOST_CHECK_CLOSE( calc.eval( "+3 + 2^-1 + 2*3" ).getCoeff<double>(), 9.5, 1e-10);
    BOOST_CHECK_CLOSE( calc.eval( "1 - (1 + 1)" ).getCoeff<double>(), -1., 1e-10 );
    BOOST_CHECK_CLOSE( calc.eval( "(1 - 3)*2 + 1" ).getCoeff<double>(), -3., 1e-10 );

  }


BOOST_AUTO_TEST_SUITE_END();//}

