#define BOOST_TEST_MODULE  quantity

#include <physical/runtime.h>
#include <physical/math.h>

#include <boost/test/unit_test.hpp>

#include <complex>
#include <iostream>


BOOST_AUTO_TEST_SUITE( quantity );//{

  BOOST_AUTO_TEST_CASE( getCoeff ) {
    using runtime::physical::quantity;
    quantity< std::complex<double> > a = std::complex<double>(1.0);
    quantity<double> b = 1.0;
    //std::cout << "a<complex>:  " << a << std::endl;
    /* default (GNU/Units like) printing */
    BOOST_CHECK_EQUAL( a.toString(), "<1>");
    BOOST_CHECK_EQUAL( a.getCoeff<double>(), b.getCoeff<double>() );
    BOOST_CHECK_EQUAL( b.getCoeff(), b.getCoeff<double>() );
    BOOST_CHECK_EQUAL( &b.getCoeff(), &b.coeff );
  }

  BOOST_AUTO_TEST_CASE( ugly_print ) {
    typedef runtime::physical::quantity< std::complex<double> > Quantity;
    using runtime::physical::units_pair;
    Quantity::setPrintMode(Quantity::UGLY_PRINT);

    Quantity a = Quantity(std::complex<double>(1.0,1.0), units_pair("kg",1));

    BOOST_CHECK_EQUAL( a.toString(), "(1,1) * {(kg : 1), }");
    BOOST_CHECK_EQUAL( (-1*a).toString(), "(-1,-1) * {(kg : 1), }");

    a *= Quantity(1.0, units_pair("s",-1));

    a *= 10.0;
    BOOST_CHECK_EQUAL( a.toString(), "(10,10) * {(kg : 1), (s : -1), }");
    BOOST_CHECK_EQUAL( (-1*a).toString(), "(-10,-10) * {(kg : 1), (s : -1), }");

    a /= 100.0;
    BOOST_CHECK_EQUAL( a.toString(), "(0.1,0.1) * {(kg : 1), (s : -1), }");
    BOOST_CHECK_EQUAL( (-1*a).toString(), "(-0.1,-0.1) * {(kg : 1), (s : -1), }");
  }

  BOOST_AUTO_TEST_CASE( math_print ) {
    typedef runtime::physical::quantity< std::complex<double> > Quantity;
    using runtime::physical::units_pair;
    Quantity::setPrintMode(Quantity::MATH_PRINT);

    Quantity a = Quantity(std::complex<double>(1.0,1.0), units_pair("kg",1));

    BOOST_CHECK_EQUAL( a.toString(), "((1 + i*1) * kg)" );
    BOOST_CHECK_EQUAL( (-1*a).toString(), "((-1 - i*1) * kg)" );

    a *= Quantity(1.0, units_pair("s",-1));

    a *= 10.0;
    BOOST_CHECK_EQUAL( a.toString(), "((10 + i*10) * kg / s)" );
    BOOST_CHECK_EQUAL( (-1*a).toString(), "((-10 - i*10) * kg / s)" );

    a /= 100.0;
    BOOST_CHECK_EQUAL( a.toString(), "((0.1 + i*0.1) * kg / s)" );
    BOOST_CHECK_EQUAL( (-1*a).toString(), "((-0.1 - i*0.1) * kg / s)" );

    a *= Quantity(1.0, units_pair("m",-1));

    a *= 100.0;
    BOOST_CHECK_EQUAL( a.toString(), "((10 + i*10) * kg / (m * s))" );
    BOOST_CHECK_EQUAL( (-1*a).toString(), "((-10 - i*10) * kg / (m * s))" );

    a /= 100.0;
    BOOST_CHECK_EQUAL( a.toString(), "((0.1 + i*0.1) * kg / (m * s))" );
    BOOST_CHECK_EQUAL( (-1*a).toString(), "((-0.1 - i*0.1) * kg / (m * s))" );
  }

  BOOST_AUTO_TEST_CASE( latex_print ) {
    typedef runtime::physical::quantity< std::complex<double> > Quantity;
    using runtime::physical::units_pair;
    Quantity::setPrintMode(Quantity::LATEX_PRINT);

    Quantity a = Quantity(std::complex<double>(1.0,1.0), units_pair("kg",1));

    BOOST_CHECK_EQUAL( a.toString(), "(1 + i1)~\\mathrm{kg}");
    BOOST_CHECK_EQUAL( (-1*a).toString(), "(-1 - i1)~\\mathrm{kg}");

    a *= 10.0;
    BOOST_CHECK_EQUAL( a.toString(), "(10 + i10)~\\mathrm{kg}");
    BOOST_CHECK_EQUAL( (-1*a).toString(), "(-10 - i10)~\\mathrm{kg}");

    a *= 10.0;
    BOOST_CHECK_EQUAL( a.toString(), "(100 + i100)~\\mathrm{kg}");
    BOOST_CHECK_EQUAL( (-1*a).toString(), "(-100 - i100)~\\mathrm{kg}");

    a *= 10.0;
    BOOST_CHECK_EQUAL( a.toString(), "(1 \\times 10^{3} + i1 \\times 10^{3})~\\mathrm{kg}");
    BOOST_CHECK_EQUAL( (-1*a).toString(), "(-1 \\times 10^{3} - i1 \\times 10^{3})~\\mathrm{kg}");

    a *= 10.0;
    BOOST_CHECK_EQUAL( a.toString(), "(1 \\times 10^{4} + i1 \\times 10^{4})~\\mathrm{kg}");
    BOOST_CHECK_EQUAL( (-1*a).toString(), "(-1 \\times 10^{4} - i1 \\times 10^{4})~\\mathrm{kg}");


    a = Quantity(std::complex<double>(1.0,1.0), units_pair("kg",-1));

    Quantity::setPrintMode(Quantity::LATEX_ONELINE_PRINT);
    BOOST_CHECK_EQUAL( a.toString(), "(1 + i1)~1/\\mathrm{kg}");
    BOOST_CHECK_EQUAL( (-1*a).toString(), "(-1 - i1)~1/\\mathrm{kg}");
    Quantity::setPrintMode(Quantity::LATEX_PRINT);
    BOOST_CHECK_EQUAL( a.toString(), "(1 + i1)~\\frac{1}{\\mathrm{kg}}");
    BOOST_CHECK_EQUAL( (-1*a).toString(), "(-1 - i1)~\\frac{1}{\\mathrm{kg}}");

    a *= Quantity(1.0, units_pair("kg",-1));

    a /= 10.0;
    Quantity::setPrintMode(Quantity::LATEX_ONELINE_PRINT);
    BOOST_CHECK_EQUAL( a.toString(), "(0.1 + i0.1)~1/\\mathrm{kg}^{2}");
    BOOST_CHECK_EQUAL( (-1*a).toString(), "(-0.1 - i0.1)~1/\\mathrm{kg}^{2}");
    Quantity::setPrintMode(Quantity::LATEX_PRINT);
    BOOST_CHECK_EQUAL( a.toString(), "(0.1 + i0.1)~\\frac{1}{\\mathrm{kg}^{2}}");
    BOOST_CHECK_EQUAL( (-1*a).toString(), "(-0.1 - i0.1)~\\frac{1}{\\mathrm{kg}^{2}}");

    a /= 10.0;
    Quantity::setPrintMode(Quantity::LATEX_ONELINE_PRINT);
    BOOST_CHECK_EQUAL( a.toString(), "(0.01 + i0.01)~1/\\mathrm{kg}^{2}");
    BOOST_CHECK_EQUAL( (-1*a).toString(), "(-0.01 - i0.01)~1/\\mathrm{kg}^{2}");
    Quantity::setPrintMode(Quantity::LATEX_PRINT);
    BOOST_CHECK_EQUAL( a.toString(), "(0.01 + i0.01)~\\frac{1}{\\mathrm{kg}^{2}}");
    BOOST_CHECK_EQUAL( (-1*a).toString(), "(-0.01 - i0.01)~\\frac{1}{\\mathrm{kg}^{2}}");

    a /= 10.0;
    Quantity::setPrintMode(Quantity::LATEX_ONELINE_PRINT);
    BOOST_CHECK_EQUAL(
      a.toString(),
      "(1 \\times 10^{-3} + i1 \\times 10^{-3})~1/\\mathrm{kg}^{2}");
    BOOST_CHECK_EQUAL(
      (-1*a).toString(),
      "(-1 \\times 10^{-3} - i1 \\times 10^{-3})~1/\\mathrm{kg}^{2}");
    Quantity::setPrintMode(Quantity::LATEX_PRINT);
    BOOST_CHECK_EQUAL(
      a.toString(),
      "(1 \\times 10^{-3} + i1 \\times 10^{-3})~\\frac{1}{\\mathrm{kg}^{2}}");
    BOOST_CHECK_EQUAL(
      (-1*a).toString(),
      "(-1 \\times 10^{-3} - i1 \\times 10^{-3})~\\frac{1}{\\mathrm{kg}^{2}}");

    a /= 10.0;
    Quantity::setPrintMode(Quantity::LATEX_ONELINE_PRINT);
    BOOST_CHECK_EQUAL(
      a.toString(),
      "(1 \\times 10^{-4} + i1 \\times 10^{-4})~1/\\mathrm{kg}^{2}");
    BOOST_CHECK_EQUAL(
      (-1*a).toString(),
      "(-1 \\times 10^{-4} - i1 \\times 10^{-4})~1/\\mathrm{kg}^{2}");
    Quantity::setPrintMode(Quantity::LATEX_PRINT);
    BOOST_CHECK_EQUAL(
      a.toString(),
      "(1 \\times 10^{-4} + i1 \\times 10^{-4})~\\frac{1}{\\mathrm{kg}^{2}}");
    BOOST_CHECK_EQUAL(
      (-1*a).toString(),
      "(-1 \\times 10^{-4} - i1 \\times 10^{-4})~\\frac{1}{\\mathrm{kg}^{2}}");
  }

  
  BOOST_AUTO_TEST_CASE( complex_test ) {
    typedef runtime::physical::quantity< std::complex<double> > Quantity;
    using runtime::physical::units_pair;

    Quantity a = std::complex<double>(1.0,1.0);
    a *= Quantity(1.0, units_pair("kg",1));

    Quantity::setPrintMode(Quantity::UGLY_PRINT);
    BOOST_CHECK_EQUAL( a.toString(), "(1,1) * {(kg : 1), }");
  }

  BOOST_AUTO_TEST_CASE( quantity_pow ) {
    typedef runtime::physical::quantity< std::complex<double> > Quantity;
    using runtime::physical::units_pair;

    Quantity a = Quantity(std::complex<double>(2.,2.), units_pair("kg",1));

    a = pow(a, 3.0);

    Quantity::setPrintMode(Quantity::UGLY_PRINT);
    //std::cout << "a<complex>:  " << a << std::endl;
    BOOST_CHECK_EQUAL( a.toString(), "(-16,16) * {(kg : 3), }");
  }

  BOOST_AUTO_TEST_CASE( assertMatch ) {
    typedef runtime::physical::quantity< std::complex<double> > Quantity;
    using runtime::physical::units_pair;

    Quantity a = Quantity(std::complex<double>(2.,2.), units_pair("kg",1));
    Quantity b = Quantity(std::complex<double>(2.,2.), units_pair());

    a = pow(a, 5.0);
    b = pow(b, 5.0);

    Quantity::setPrintMode(Quantity::UGLY_PRINT);
    BOOST_CHECK_EQUAL( a.toString(), "(-128,-128) * {(kg : 5), }");
    BOOST_CHECK_EQUAL( b.toString(), "(-128,-128) * {}");

    BOOST_CHECK_NO_THROW(
      a.assertMatch(Quantity(std::complex<double>(1.,1.), units_pair("kg",5)))
    );
    BOOST_CHECK_NO_THROW(
      b.assertMatch(Quantity(std::complex<double>(1.,1.), units_pair()))
    );
    BOOST_CHECK_NO_THROW( b.assertUnitless() );

    BOOST_CHECK_THROW(
      a.assertMatch(Quantity(std::complex<double>(1.,1.), units_pair("kg",1))),
      std::runtime_error
    );
    BOOST_CHECK_THROW(
      b.assertMatch(Quantity(std::complex<double>(1.,1.), units_pair("kg",1))),
      std::runtime_error
    );
    BOOST_CHECK_THROW( a.assertUnitless(), std::runtime_error );
  }

BOOST_AUTO_TEST_SUITE_END();//}

