#include <physical/physical.h>
#include <physical/quantity.h>

#define BOOST_TEST_MODULE  unit_systems

#include <boost/test/unit_test.hpp>

#include <iostream>

BOOST_AUTO_TEST_SUITE( unit_systems );

  BOOST_AUTO_TEST_CASE( conversion ) {
    using namespace physical;
    using system::si;
    using system::atomic;
    using system::cgs;
    using system::esu;
    using system::emu;
    namespace dim = dimension;
  
    /* These test the per-unit-system constants which are automatically converted
     * from constant::si::* to constant::item<tag>::value at instantiation time.
     * */
    BOOST_CHECK_EQUAL( constant::c<si>::value,         constant::si::c);
    BOOST_CHECK_EQUAL( constant::c<cgs>::value,        100*constant::si::c);
    BOOST_CHECK_EQUAL( constant::c<atomic>::value,     1./constant::si::alpha);
    BOOST_CHECK_EQUAL( constant::eV<atomic>::value,    constant::si::eV/constant::si::Hartree);
    BOOST_CHECK_EQUAL( constant::alpha<si>::value,     constant::si::alpha);
    BOOST_CHECK_EQUAL( constant::alpha<atomic>::value, constant::si::alpha);
    BOOST_CHECK_EQUAL( constant::e<atomic>::value,     1.0);
    BOOST_CHECK_EQUAL( constant::e<esu>::value,        constant::si::e / unit::statCoulomb);
    BOOST_CHECK_EQUAL( constant::epsilon0<si>::value,  constant::si::epsilon0);
    BOOST_CHECK_EQUAL( constant::epsilon0<esu>::value, constant::si::epsilon0 /
                                                       (unit::statCoul /
                                                        (unit::statVolt *
                                                         unit::cm)));
    BOOST_CHECK_EQUAL( constant::k_E<si>::value,       constant::si::k_E);
    BOOST_CHECK_EQUAL( constant::k_E<atomic>::value,   1);
    BOOST_CHECK_EQUAL( constant::k_E<esu>::value,      1);
  
    /* these should all equal '1' because the dimensions are supposed to be
     * explicitly in SI units, even for each unit system.  By having all
     * dimensions defined in terms of a single system (SI as is done here), it is
     * possible to easily convert from one to another. */
    BOOST_CHECK_EQUAL( dim::force<si>::value,                   1 );
    BOOST_CHECK_EQUAL( dim::velocity<si>::value,                1 );
    BOOST_CHECK_EQUAL( dim::pressure<si>::value,                1 );
    BOOST_CHECK_EQUAL( dim::mass<si>::value,                    1 );
    BOOST_CHECK_EQUAL( dim::momentum<si>::value,                1 );
    BOOST_CHECK_EQUAL( dim::angular_momentum<si>::value,        1 );
    BOOST_CHECK_EQUAL( dim::power<si>::value,                   1 );
    BOOST_CHECK_EQUAL( dim::energy<si>::value,                  1 );
    BOOST_CHECK_EQUAL( dim::electric::resistance<si>::value,    1 );
    BOOST_CHECK_EQUAL( dim::electric::potential<si>::value,     1 );
    BOOST_CHECK_EQUAL( dim::electric::capacitance<si>::value,   1 );
    BOOST_CHECK_EQUAL( dim::magnetic::flux<si>::value,          1 );
    BOOST_CHECK_EQUAL( dim::magnetic::flux_density<si>::value,  1 );
    BOOST_CHECK_EQUAL( dim::magnetic::field<si>::value,         1 );
    BOOST_CHECK_EQUAL( dim::magnetic::inductance<si>::value,    1 );

    /* now check various derived dimensions in various systems. */
    BOOST_CHECK_EQUAL( dim::charge<esu>::value,     unit::statCoulomb );
    BOOST_CHECK_EQUAL( dim::electric::current<esu>::value,    unit::statAmpere );
    BOOST_CHECK_EQUAL( dim::electric::current<atomic>::value,
                       constant::si::e * constant::si::Hartree /
                       constant::si::h_bar );
    BOOST_CHECK_EQUAL( dim::electric::potential<esu>::value,  unit::statVolt );
    BOOST_CHECK_EQUAL( dim::electric::potential<atomic>::value,
                       constant::si::Hartree / constant::si::e );
    BOOST_CHECK_EQUAL( dim::magnetic::flux<atomic>::value, 
                       (constant::si::h_bar / constant::si::e) );
    BOOST_CHECK_EQUAL( dim::magnetic::field<atomic>::value, 
                       (constant::si::h_bar / constant::si::e) /
                       SQR(constant::si::a_0) );
    BOOST_CHECK_EQUAL( dim::magnetic::flux<esu>::value,       unit::statMaxwell );
    BOOST_CHECK_EQUAL( dim::magnetic::field<esu>::value,
                       unit::statMaxwell / SQR(unit::cm) );
    BOOST_CHECK_EQUAL( dim::magnetic::flux<emu>::value,       unit::Maxwell );
    BOOST_CHECK_EQUAL( dim::magnetic::field<emu>::value,      unit::Gauss );
  
    /* These two test the compile time conversion selection function. */
    BOOST_CHECK_EQUAL( (make_convert_ratio<esu,dim::force,si>::value), 1e-5 );
    BOOST_CHECK_EQUAL( (convert<esu,dim::force,si>(1.0)), 1e-5 );
    BOOST_CHECK_EQUAL( (convert<si,dim::velocity,cgs>(1.0)), 100. );


    /* this is what the aggregate dimension conversion should do. */
    BOOST_CHECK_EQUAL( ( make_convert_ratio<si,dim::electric::capacitance,esu>::value /
                         make_convert_ratio<si,dim::length,esu>::value
                       ),
                       1. / ((unit::statCoul / unit::statVolt ) / unit::cm)
                     );

    BOOST_CHECK_EQUAL(
      ( make_convert_ratio<si,dim::electric::capacitance_per_length,esu>::value ),
      1. / ((unit::statCoul / unit::statVolt ) / unit::cm)
    );
  
    /* This tests the runtime conversion selection function. */
    BOOST_CHECK_EQUAL( (convert<esu,dim::force>(1.0,si::Id)), 1e-5 );
  }

  BOOST_AUTO_TEST_CASE( conversion_test ) {
    using namespace runtime::physical;
    using system::si;
    using system::atomic;
    using system::cgs;
    using system::esu;
    using system::emu;
    namespace dim = dimension;
  
    std::cout << "e<atomic>:  " <<  constant::e<atomic>::value << std::endl;
    std::cout << "k_E<atomic>:  " <<  constant::k_E<atomic>::value << std::endl;
  }

  BOOST_AUTO_TEST_CASE( conversion_w_runtime ) {
    using namespace runtime::physical;
    using system::si;
    using system::atomic;
    using system::cgs;
    using system::esu;
    using system::emu;
    namespace dim = dimension;
  
    /* These test the per-unit-system constants which are automatically converted
     * from constant::si::* to constant::item<tag>::value at instantiation time.
     * */
    BOOST_CHECK_EQUAL( constant::c<si>::value,         constant::si::c);
    BOOST_CHECK_EQUAL( constant::c<cgs>::value,        100*constant::si::c);
    BOOST_CHECK_EQUAL( constant::c<atomic>::value,     1./constant::si::alpha);
    BOOST_CHECK_EQUAL( constant::eV<atomic>::value,    constant::si::eV/constant::si::Hartree);
    BOOST_CHECK_EQUAL( constant::alpha<si>::value,     constant::si::alpha);
    BOOST_CHECK_EQUAL( constant::alpha<atomic>::value, constant::si::alpha);
    BOOST_CHECK_EQUAL( constant::e<atomic>::value,     unit::A * unit::s);
    BOOST_CHECK_EQUAL( constant::e<esu>::value,        constant::si::e / unit::statCoulomb);
    BOOST_CHECK_EQUAL( constant::epsilon0<si>::value,  constant::si::epsilon0);
    BOOST_CHECK_EQUAL( constant::epsilon0<esu>::value, constant::si::epsilon0 /
                                                       (unit::statCoul /
                                                        (unit::statVolt *
                                                         unit::cm)));
    BOOST_CHECK_EQUAL( constant::k_E<si>::value,       constant::si::k_E);
    BOOST_CHECK_EQUAL( constant::k_E<atomic>::value,   Quantity(1));
    BOOST_CHECK_EQUAL( constant::k_E<esu>::value,      Quantity(1));
  
    /* these should all equal '1' because the dimensions are supposed to be
     * explicitly in SI units, even for each unit system.  By having all
     * dimensions defined in terms of a single system (SI as is done here), it is
     * possible to easily convert from one to another. */
    BOOST_CHECK_EQUAL( dim::force<si>::value,                   Quantity(1) );
    BOOST_CHECK_EQUAL( dim::velocity<si>::value,                Quantity(1) );
    BOOST_CHECK_EQUAL( dim::pressure<si>::value,                Quantity(1) );
    BOOST_CHECK_EQUAL( dim::mass<si>::value,                    Quantity(1) );
    BOOST_CHECK_EQUAL( dim::momentum<si>::value,                Quantity(1) );
    BOOST_CHECK_EQUAL( dim::angular_momentum<si>::value,        Quantity(1) );
    BOOST_CHECK_EQUAL( dim::power<si>::value,                   Quantity(1) );
    BOOST_CHECK_EQUAL( dim::energy<si>::value,                  Quantity(1) );
    BOOST_CHECK_EQUAL( dim::electric::resistance<si>::value,    Quantity(1) );
    BOOST_CHECK_EQUAL( dim::electric::potential<si>::value,     Quantity(1) );
    BOOST_CHECK_EQUAL( dim::electric::capacitance<si>::value,   Quantity(1) );
    BOOST_CHECK_EQUAL( dim::magnetic::flux<si>::value,          Quantity(1) );
    BOOST_CHECK_EQUAL( dim::magnetic::flux_density<si>::value,  Quantity(1) );
    BOOST_CHECK_EQUAL( dim::magnetic::field<si>::value,         Quantity(1) );
    BOOST_CHECK_EQUAL( dim::magnetic::inductance<si>::value,    Quantity(1) );

    /* now check various derived dimensions in various systems. */
    BOOST_CHECK_EQUAL( dim::charge<esu>::value,     unit::statCoulomb );
    BOOST_CHECK_EQUAL( dim::electric::current<esu>::value,    unit::statAmpere );
    BOOST_CHECK_EQUAL( dim::electric::current<atomic>::value,
                       constant::si::e * constant::si::Hartree /
                       constant::si::h_bar );
    BOOST_CHECK_EQUAL( dim::electric::potential<esu>::value,  unit::statVolt );
    BOOST_CHECK_EQUAL( dim::electric::potential<atomic>::value,
                       constant::si::Hartree / constant::si::e );
    BOOST_CHECK_EQUAL( dim::magnetic::flux<atomic>::value, 
                       (constant::si::h_bar / constant::si::e) );
    BOOST_CHECK_EQUAL( dim::magnetic::field<atomic>::value, 
                       (constant::si::h_bar / constant::si::e) /
                       SQR(constant::si::a_0) );
    BOOST_CHECK_EQUAL( dim::magnetic::flux<esu>::value,       unit::statMaxwell );
    BOOST_CHECK_EQUAL( dim::magnetic::field<esu>::value,
                       unit::statMaxwell / SQR(unit::cm) );
    BOOST_CHECK_EQUAL( dim::magnetic::flux<emu>::value,       unit::Maxwell );
    BOOST_CHECK_EQUAL( dim::magnetic::field<emu>::value,      unit::Gauss );
  
    /* These two test the compile time conversion selection function. */
    BOOST_CHECK_EQUAL( (make_convert_ratio<esu,dim::force,si>::value), Quantity(1e-5) );
    BOOST_CHECK_EQUAL( (convert<esu,dim::force,si>(Quantity(1.0))),    Quantity(1e-5) );
    BOOST_CHECK_EQUAL( (convert<si,dim::velocity,cgs>(Quantity(1.0))), Quantity(100.) );


    /* this is what the aggregate dimension conversion should do. */
    BOOST_CHECK_EQUAL( ( make_convert_ratio<si,dim::electric::capacitance,esu>::value /
                         make_convert_ratio<si,dim::length,esu>::value
                       ),
                       1. / ((unit::statCoul / unit::statVolt ) / unit::cm)
                     );

    BOOST_CHECK_EQUAL(
      ( make_convert_ratio<si,dim::electric::capacitance_per_length,esu>::value ),
      1. / ((unit::statCoul / unit::statVolt ) / unit::cm)
    );
  
    /* This tests the runtime conversion selection function. */
    BOOST_CHECK_EQUAL( (convert<esu,dim::force>(Quantity(1.0),si::Id)), Quantity(1e-5) );
  }

BOOST_AUTO_TEST_SUITE_END();

