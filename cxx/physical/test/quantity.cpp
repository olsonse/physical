#define BOOST_TEST_MODULE  quantity

#include <physical/quantity.h>

#include <boost/test/unit_test.hpp>

#include <complex>
#include <iostream>


BOOST_AUTO_TEST_SUITE( quantity );//{

  BOOST_AUTO_TEST_CASE( getCoeff ) {
    runtime::physical::Quantity a = std::complex<double>(1.0);
    runtime::physical::quantity<double> b = 1.0;
    std::cout << "a<complex>:  " << a << std::endl;
    BOOST_CHECK_EQUAL( a.getCoeff<double>(), b.getCoeff<double>() );
    BOOST_CHECK_EQUAL( b.getCoeff(), b.getCoeff<double>() );
    BOOST_CHECK_EQUAL( &b.getCoeff(), &b.coeff );
  }
  
  BOOST_AUTO_TEST_CASE( complex_test ) {
    typedef runtime::physical::quantity< std::complex<double> > Quantity;
    using runtime::physical::units_pair;

    Quantity a = std::complex<double>(1.0,1.0);
    a *= Quantity(1.0, units_pair("kg",1));

    Quantity::setPrintMode(Quantity::PRETTY_PRINT);
    std::cout << "a<complex>:  " << a << std::endl;
    Quantity::setPrintMode(Quantity::MATH_PRINT);
    std::cout << "a<complex>:  " << a << std::endl;
    Quantity::setPrintMode(Quantity::LATEX_PRINT);
    std::cout << "a<complex>:  " << a << std::endl;
    Quantity::setPrintMode(Quantity::LATEX_ONELINE_PRINT);
    std::cout << "a<complex>:  " << a << std::endl;
    Quantity::setPrintMode(Quantity::UGLY_PRINT);
    std::cout << "a<complex>:  " << a << std::endl;

    std::complex<double> b = std::log10(std::complex<double>(1.0,1.0));
    BOOST_CHECK_EQUAL( 0, 0 );
  }

BOOST_AUTO_TEST_SUITE_END();//}

