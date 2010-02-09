#define BOOST_TEST_MODULE  physical_detail_ConvertCoeff

#include <physical/detail/ConvertCoeff.h>

#include <boost/test/unit_test.hpp>

#include <complex>
#include <iostream>

namespace {
  using runtime::physical::detail::ConvertCoeff;
  typedef std::complex<double> Dc;
  typedef std::complex<float> Fc;
}

BOOST_AUTO_TEST_SUITE( Conversion );//{

  BOOST_AUTO_TEST_CASE( to_double_from_double ) {
    BOOST_CHECK_EQUAL( ConvertCoeff<double>( 1. ), 1. );
    BOOST_CHECK_EQUAL( ConvertCoeff<double>( -1. ), -1. );
  }

  BOOST_AUTO_TEST_CASE( to_float_from_double ) {
    BOOST_CHECK_EQUAL( ConvertCoeff<float>( 1. ), 1.f );
    BOOST_CHECK_EQUAL( ConvertCoeff<float>( -1. ), -1.f );
  }

  BOOST_AUTO_TEST_CASE( to_double_from_float ) {
    BOOST_CHECK_EQUAL( ConvertCoeff<double>( 1.f ), 1. );
    BOOST_CHECK_EQUAL( ConvertCoeff<double>( -1.f ), -1. );
  }

  BOOST_AUTO_TEST_CASE( to_int_from_int) {
    BOOST_CHECK_EQUAL( ConvertCoeff<int>( 1 ), 1 );
    BOOST_CHECK_EQUAL( ConvertCoeff<int>( -1 ), -1 );
  }

  BOOST_AUTO_TEST_CASE( to_double_from_cdouble ) {
    BOOST_CHECK_EQUAL( ConvertCoeff<double>( Dc(1.,0.) ), 1. );
    BOOST_CHECK_EQUAL( ConvertCoeff<double>( Dc(-1.,0.) ), -1. );
    BOOST_CHECK_THROW( ConvertCoeff<double>( Dc(-1.,1.) ), runtime::physical::exception );
    BOOST_CHECK_THROW( ConvertCoeff<double>( Dc(0.,1.) ), runtime::physical::exception );
  }

  BOOST_AUTO_TEST_CASE( to_float_from_cdouble ) {
    BOOST_CHECK_EQUAL( ConvertCoeff<float>( Dc(1.,0.) ), 1.f );
    BOOST_CHECK_EQUAL( ConvertCoeff<float>( Dc(-1.,0.) ), -1.f );
    BOOST_CHECK_THROW( ConvertCoeff<float>( Dc(-1.,1.) ), runtime::physical::exception );
    BOOST_CHECK_THROW( ConvertCoeff<float>( Dc(0.,1.) ), runtime::physical::exception );
  }

  BOOST_AUTO_TEST_CASE( to_double_from_cfloat ) {
    BOOST_CHECK_EQUAL( ConvertCoeff<double>( Fc(1.f,0.f) ), 1. );
    BOOST_CHECK_EQUAL( ConvertCoeff<double>( Fc(-1.f,0.f) ), -1. );
    BOOST_CHECK_THROW( ConvertCoeff<double>( Fc(-1.f,1.f) ), runtime::physical::exception );
    BOOST_CHECK_THROW( ConvertCoeff<double>( Fc(0.f,1.f) ), runtime::physical::exception );
  }

  BOOST_AUTO_TEST_CASE( to_float_from_cfloat ) {
    BOOST_CHECK_EQUAL( ConvertCoeff<float>( Fc(1.f,0.f) ), 1.f );
    BOOST_CHECK_EQUAL( ConvertCoeff<float>( Fc(-1.f,0.f) ), -1.f );
    BOOST_CHECK_THROW( ConvertCoeff<float>( Fc(-1.f,1.f) ), runtime::physical::exception );
    BOOST_CHECK_THROW( ConvertCoeff<float>( Fc(0.f,1.f) ), runtime::physical::exception );
  }

  BOOST_AUTO_TEST_CASE( to_cdouble_from_cdouble ) {
    BOOST_CHECK_EQUAL( ConvertCoeff<Dc>( Dc(1.,0.) ), 1. );
    BOOST_CHECK_EQUAL( ConvertCoeff<Dc>( Dc(-1.,0.) ), -1. );
    BOOST_CHECK_EQUAL( ConvertCoeff<Dc>( Dc(1.,1.) ), Dc(1.,1.) );
    BOOST_CHECK_EQUAL( ConvertCoeff<Dc>( Dc(-1.,1.) ), Dc(-1.,1.) );
  }

  BOOST_AUTO_TEST_CASE( to_cfloat_from_cdouble ) {
    BOOST_CHECK_EQUAL( ConvertCoeff<Fc>( Dc(1.,0.) ), 1.f );
    BOOST_CHECK_EQUAL( ConvertCoeff<Fc>( Dc(-1.,0.) ), -1.f );
    BOOST_CHECK_EQUAL( ConvertCoeff<Fc>( Dc(1.,1.) ), Fc(1.f,1.f) );
    BOOST_CHECK_EQUAL( ConvertCoeff<Fc>( Dc(-1.,1.) ), Fc(-1.f,1.f) );
  }

  BOOST_AUTO_TEST_CASE( to_cdouble_from_cfloat ) {
    BOOST_CHECK_EQUAL( ConvertCoeff<Dc>( Fc(1.f,0.f) ), 1. );
    BOOST_CHECK_EQUAL( ConvertCoeff<Dc>( Fc(-1.f,0.f) ), -1. );
    BOOST_CHECK_EQUAL( ConvertCoeff<Dc>( Fc(1.f,1.f) ), Dc(1.,1.) );
    BOOST_CHECK_EQUAL( ConvertCoeff<Dc>( Fc(-1.f,1.f) ), Dc(-1.,1.) );
  }

  BOOST_AUTO_TEST_CASE( to_cfloat_from_cfloat ) {
    BOOST_CHECK_EQUAL( ConvertCoeff<Fc>( Fc(1.f,0.f) ), 1.f );
    BOOST_CHECK_EQUAL( ConvertCoeff<Fc>( Fc(-1.f,0.f) ), -1.f );
    BOOST_CHECK_EQUAL( ConvertCoeff<Fc>( Fc(1.f,1.f) ), Fc(1.f,1.f) );
    BOOST_CHECK_EQUAL( ConvertCoeff<Fc>( Fc(-1.f,1.f) ), Fc(-1.f,1.f) );
  }

BOOST_AUTO_TEST_SUITE_END();//}

