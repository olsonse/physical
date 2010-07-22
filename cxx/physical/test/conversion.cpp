#include <physical/physical.h>
#include <physical/runtime.h>

#define BOOST_TEST_MODULE  unit_systems

#include <boost/test/unit_test.hpp>

#include <iostream>

BOOST_AUTO_TEST_SUITE( unit_systems );

  BOOST_AUTO_TEST_CASE( DimQuantity_cast_double ) {
    using namespace physical;
    namespace system = physical::system;
    using system::si;
    using system::atomic;
    using system::cgs;
    using system::esu;
    using system::emu;
    namespace dim = dimension;

    DimQuantity<si,dim::velocity> dsivel(1.0);
    double & ref = dsivel;
    const double & cref = static_cast<const DimQuantity<si,dim::velocity>& >(dsivel);
    BOOST_CHECK_EQUAL( &ref, &(dsivel.value) );
    BOOST_CHECK_EQUAL( &cref, &(dsivel.value) );
    BOOST_CHECK_EQUAL( &ref, &cref );
    BOOST_CHECK_EQUAL( dsivel, 1.0 );
    BOOST_CHECK_EQUAL( 10.0*dsivel, 10.0 );
  }

  BOOST_AUTO_TEST_CASE( DimQuantity_cast_runtime ) {
    using namespace runtime::physical;
    namespace system = runtime::physical::system;
    using system::si;
    using system::atomic;
    using system::cgs;
    using system::esu;
    using system::emu;
    namespace dim = dimension;

    DimQuantity<si,dim::velocity> dsivel(Quantity(1.0));
    Quantity & ref = dsivel;
    const Quantity & cref = static_cast<const DimQuantity<si,dim::velocity>& >(dsivel);
    BOOST_CHECK_EQUAL( &ref, &(dsivel.value) );
    BOOST_CHECK_EQUAL( &cref, &(dsivel.value) );
    BOOST_CHECK_EQUAL( &ref, &cref );

    /* testing the cast operator again.  For non-native types (e.g. double) the
     * casting is necessary in many cases. */
    BOOST_CHECK_EQUAL( static_cast<Quantity&>(dsivel), Quantity(1.0) );
    BOOST_CHECK_EQUAL( 10.0*static_cast<const Quantity&>(dsivel), Quantity(10.0) );
  }

  BOOST_AUTO_TEST_CASE( conversion ) {
    using namespace physical;
    namespace system = physical::system;
    using system::si;
    using system::atomic;
    using system::cgs;
    using system::esu;
    using system::emu;
    namespace dim = dimension;
  
    /* these should all equal '1' because the dimensions are supposed to be
     * explicitly in SI units, even for each unit system.  By having all
     * dimensions defined in terms of a single system (SI as is done here), it is
     * possible to easily convert from one to another. */
    BOOST_CHECK_EQUAL( dim::length<si>::value(),                1 );
    BOOST_CHECK_EQUAL( dim::mass<si>::value(),                  1 );
    BOOST_CHECK_EQUAL( dim::time<si>::value(),                  1 );
    BOOST_CHECK_EQUAL( dim::charge<si>::value(),                1 );
    BOOST_CHECK_EQUAL( dim::frequency<si>::value(),             1 );
    BOOST_CHECK_EQUAL( dim::charge_to_mass<si>::value(),        1 );
    BOOST_CHECK_EQUAL( dim::inverse_length<si>::value(),        1 );
    BOOST_CHECK_EQUAL( dim::area<si>::value(),                  1 );
    BOOST_CHECK_EQUAL( dim::volume<si>::value(),                1 );
    BOOST_CHECK_EQUAL( dim::number_density<si>::value(),        1 );
    BOOST_CHECK_EQUAL( dim::density<si>::value(),               1 );
    BOOST_CHECK_EQUAL( dim::velocity<si>::value(),              1 );
    BOOST_CHECK_EQUAL( dim::acceleration<si>::value(),          1 );
    BOOST_CHECK_EQUAL( dim::force<si>::value(),                 1 );
    BOOST_CHECK_EQUAL( dim::energy<si>::value(),                1 );
    BOOST_CHECK_EQUAL( dim::power<si>::value(),                 1 );
    // except for this one since it is a little ambiguous
    BOOST_CHECK_EQUAL( dim::temperature<si>::value(), 1./constant::si::K_B );
    BOOST_CHECK_EQUAL( dim::pressure<si>::value(),              1 );
    BOOST_CHECK_EQUAL( dim::momentum<si>::value(),              1 );
    BOOST_CHECK_EQUAL( dim::angular_momentum<si>::value(),      1 );
    BOOST_CHECK_EQUAL( dim::viscosity<si>::value(),             1 );
    BOOST_CHECK_EQUAL( dim::kinematic_viscosity<si>::value(),   1 );

    BOOST_CHECK_EQUAL( dim::electric::potential<si>::value(),   1 );
    BOOST_CHECK_EQUAL( dim::electric::field<si>::value(),       1 );
    BOOST_CHECK_EQUAL( dim::electric::current<si>::value(),     1 );
    BOOST_CHECK_EQUAL( dim::electric::resistance<si>::value(),  1 );
    BOOST_CHECK_EQUAL( dim::electric::conductance<si>::value(), 1 );
    BOOST_CHECK_EQUAL( dim::electric::resistivity<si>::value(), 1 );
    BOOST_CHECK_EQUAL( dim::electric::conductivity<si>::value(),1 );
    BOOST_CHECK_EQUAL( dim::electric::capacitance<si>::value(), 1 );

    BOOST_CHECK_EQUAL( dim::magnetic::flux<si>::value(),        1 );
    BOOST_CHECK_EQUAL( dim::magnetic::flux_density<si>::value(),1 );
    BOOST_CHECK_EQUAL( dim::magnetic::field<si>::value(),       1 );
    BOOST_CHECK_EQUAL( dim::magnetic::inductance<si>::value(),  1 );
    BOOST_CHECK_EQUAL( dim::magnetic::permeability<si>::value(),1 );
    BOOST_CHECK_EQUAL( dim::magnetic::moment<si>::value(),      1 );


    /* now check various derived dimensions in various systems. */
    BOOST_CHECK_EQUAL( dim::charge<esu>::value(),               unit::statCoulomb );
    BOOST_CHECK_CLOSE( dim::energy<atomic>::value(),            
                       constant::si::m_e *
                       SQR(constant::si::a_0) / 
                       SQR(constant::si::h_bar * unit::radian /
                           constant::si::Hartree),
                       1e-7 );
    BOOST_CHECK_EQUAL( dim::electric::current<esu>::value(),    unit::statAmpere );
    BOOST_CHECK_EQUAL( dim::electric::current<atomic>::value(),
                       constant::si::e * constant::si::Hartree /
                       constant::si::h_bar );
    BOOST_CHECK_EQUAL( dim::electric::potential<esu>::value(),unit::statVolt );
    BOOST_CHECK_CLOSE( dim::electric::potential<atomic>::value(),
                       constant::si::Hartree / constant::si::e, 1e-7 );
    BOOST_CHECK_CLOSE( dim::magnetic::flux<atomic>::value(),
                       (constant::si::h_bar / constant::si::e), 1e-7 );
    BOOST_CHECK_CLOSE( dim::magnetic::field<atomic>::value(),
                       (constant::si::h_bar / constant::si::e) /
                       SQR(constant::si::a_0), 1e-7 );
    BOOST_CHECK_EQUAL( dim::magnetic::flux<esu>::value(),     unit::statMaxwell );
    BOOST_CHECK_EQUAL( dim::magnetic::field<esu>::value(),
                       unit::statMaxwell / SQR(unit::cm) );
    BOOST_CHECK_EQUAL( dim::magnetic::flux<emu>::value(),     unit::Maxwell );
    BOOST_CHECK_EQUAL( dim::magnetic::field<emu>::value(),    unit::Gauss );
  
    /* These test the compile time conversion selection function. */
    BOOST_CHECK_EQUAL( (make_convert_ratio<si,si,dim::energy>::value()), 1. );
    BOOST_CHECK_EQUAL( (make_convert_ratio<atomic,si,dim::energy>::value()),
                       1. / dim::energy<atomic>::value() );
    BOOST_CHECK_EQUAL( (make_convert_ratio<si,si,dim::force>::value()), 1. );
    BOOST_CHECK_EQUAL( (make_convert_ratio<si,esu,dim::force>::value()), 1e-5 );
    BOOST_CHECK_EQUAL( (convert<si>(DimQuantity<esu,dim::force>(1.0))), 1e-5 );
    BOOST_CHECK_EQUAL( (convert<cgs>(DimQuantity<si,dim::velocity>(1.0))), 100. );


    /* this is what the aggregate dimension conversion should do. */
    BOOST_CHECK_CLOSE(
      ( make_convert_ratio<esu,si,dim::electric::capacitance>::value() /
        make_convert_ratio<esu,si,dim::length>::value() ),
      1. / ((unit::statCoul / unit::statVolt ) / unit::cm),
      1e-13
    );

    BOOST_CHECK_CLOSE(
      (make_convert_ratio<esu,si,constant::detail::capacitance_per_length>::value()),
      1. / ((unit::statCoul / unit::statVolt ) / unit::cm),
      1e-13
    );
  
    /* This tests the runtime conversion selection function. */
    BOOST_CHECK_EQUAL( (convert(DimQuantity<esu,dim::force>(1.0),si::Id)), 1e-5 );


    /* These test the per-unit-system constants which are automatically
     * converted from constant::si::* to constant::item<tag>::value() at
     * instantiation time. */
    BOOST_CHECK_EQUAL( constant::c<si>::value(),        constant::si::c);
    BOOST_CHECK_EQUAL( constant::c<cgs>::value(),       100*constant::si::c);
    BOOST_CHECK_EQUAL( constant::c<atomic>::value(),    1./constant::si::alpha);
    BOOST_CHECK_EQUAL( constant::eV<si>::value(),       constant::si::eV);
    BOOST_CHECK_CLOSE( constant::eV<atomic>::value(),   constant::si::eV/constant::si::Hartree, 1e-7);
    BOOST_CHECK_EQUAL( constant::alpha<si>::value(),    constant::si::alpha);
    BOOST_CHECK_EQUAL( constant::alpha<atomic>::value(),constant::si::alpha);
    BOOST_CHECK_CLOSE( constant::e<atomic>::value(),    1.0, 1e-13);
    BOOST_CHECK_EQUAL( constant::e<esu>::value(),       constant::si::e / unit::statCoulomb);
    BOOST_CHECK_EQUAL( constant::epsilon0<si>::value(), constant::si::epsilon0);
    BOOST_CHECK_EQUAL( constant::epsilon0<esu>::value(),constant::si::epsilon0 /
                                                        (unit::statCoul /
                                                         (unit::statVolt *
                                                          unit::cm)));
    BOOST_CHECK_EQUAL( constant::k_E<si>::value(),      constant::si::k_E);
    BOOST_CHECK_CLOSE( constant::k_E<atomic>::value(),  1., 1e-7);
    BOOST_CHECK_CLOSE( constant::k_E<esu>::value(),     1., 1e-5);

    BOOST_CHECK_CLOSE( constant::z0<si>::value(),       constant::si::c *
                                                        constant::si::mu0, 1e-5 );
    BOOST_CHECK_CLOSE( constant::z0<esu>::value(),      4.191690164586e-10, 1e-5);

    /* check the default implementation of the constants (SHOULD be SI). */
    BOOST_CHECK_EQUAL( constant::c<>::value(),         constant::si::c);
    BOOST_CHECK_EQUAL( constant::eV<>::value(),        constant::si::eV);
  }



#if 0
  THis is commented out right now because it is unclear how this actually helps,
  although, as indicated in the comment below, I have used this in debugging.  I
  think there could have been better tests written.  

  /* Although I don't think that the conversion stuff is very useful for the
   * runtime component of this library, the following tests have been helpful in
   * debugging things. */

  BOOST_AUTO_TEST_CASE( conversion_test ) {
    using namespace runtime::physical;
    namespace system = runtime::physical::system;
    using system::si;
    using system::atomic;
    using system::cgs;
    using system::esu;
    using system::emu;
    namespace dim = dimension;

    BOOST_CHECK_CLOSE( constant::e<atomic>::value().getCoeff().real(),
                       (constant::e<si>::value() / ::physical::constant::si::e).getCoeff().real(),
                       1e-13 );
    //BOOST_CHECK_EQUAL( constant::k_E<atomic>::value(), unit::A * unit::s );
  
    std::cout << "e<atomic>:  " <<  constant::e<atomic>::value() << std::endl;
    std::cout << "e<si>:  " <<  constant::e<si>::value() << std::endl;
    std::cout << "dim::electric::capacitance<si>::value():  " << dim::electric::capacitance<si>::value() << std::endl;
    std::cout << "constant::detail::capacitance_per_length<si>::value():  " << constant::detail::capacitance_per_length<si>::value() << std::endl;
    std::cout << "constant::detail::capacitance_per_length<atomic>::value():  " << constant::detail::capacitance_per_length<atomic>::value() << std::endl;
    std::cout << "dim::electric::capacitance<atomic>::value():  " << dim::electric::capacitance<atomic>::value() << std::endl;
    std::cout << "dim::length<si>::value():  " << dim::length<si>::value() << std::endl;
    std::cout << "dim::length<atomic>::value():  " << dim::length<atomic>::value() << std::endl;
    std::cout << "constant::si::epsilon0:  " <<  constant::si::epsilon0 << std::endl;
    std::cout << "epsilon0<si>:  " <<  constant::epsilon0<si>::value() << std::endl;
    std::cout << "k_E<si>:  " <<  constant::k_E<si>::value() << std::endl;
    std::cout << "epsilon0<atomic>:  " <<  constant::epsilon0<atomic>::value() << std::endl;
    std::cout << "k_E<atomic>:  " <<  constant::k_E<atomic>::value() << std::endl;
  }

  BOOST_AUTO_TEST_CASE( conversion_w_runtime ) {
    using namespace runtime::physical;
    namespace system = runtime::physical::system;
    using system::si;
    using system::atomic;
    using system::cgs;
    using system::esu;
    using system::emu;
    namespace dim = dimension;
  
    /* These test the per-unit-system constants which are automatically converted
     * from constant::si::* to constant::item<tag>::value() at instantiation time.
     * */
    BOOST_CHECK_EQUAL( constant::c<si>::value(),         constant::si::c);
    BOOST_CHECK_EQUAL( constant::c<cgs>::value(),        100*constant::si::c);
    BOOST_CHECK_EQUAL( constant::c<atomic>::value(),     
                       unit::m/unit::s/constant::si::alpha);
    BOOST_CHECK_EQUAL( constant::eV<atomic>::value(),    
                       constant::si::eV / ::physical::constant::si::Hartree);
    BOOST_CHECK_EQUAL( constant::alpha<si>::value(),     constant::si::alpha);
    BOOST_CHECK_EQUAL( constant::alpha<atomic>::value(), constant::si::alpha);
    BOOST_CHECK_EQUAL( constant::e<atomic>::value(),     unit::A * unit::s);
    BOOST_CHECK_EQUAL( constant::e<esu>::value(),        
                       constant::si::e / ::physical::unit::statCoulomb );
    BOOST_CHECK_EQUAL( constant::epsilon0<si>::value(),  constant::si::epsilon0);
    BOOST_CHECK_EQUAL( constant::epsilon0<esu>::value(),
                       constant::si::epsilon0 /
                       (::physical::unit::statCoul /
                        (::physical::unit::statVolt *
                         ::physical::unit::cm)) );
    BOOST_CHECK_EQUAL( constant::k_E<si>::value(),       constant::si::k_E);
    BOOST_CHECK_EQUAL( constant::k_E<atomic>::value(),   
                       constant::si::k_E / ::physical::constant::si::k_E );
    BOOST_CHECK_EQUAL( constant::k_E<esu>::value(),      
                       constant::si::k_E / ::physical::constant::si::k_E );
  
    /* these should all equal '1' because the dimensions are supposed to be
     * explicitly in SI units, even for each unit system.  By having all
     * dimensions defined in terms of a single system (SI as is done here), it is
     * possible to easily convert from one to another. */
    BOOST_CHECK_EQUAL( dim::force<si>::value().coeff,                  1. );
    BOOST_CHECK_EQUAL( dim::velocity<si>::value().coeff,               1. );
    BOOST_CHECK_EQUAL( dim::pressure<si>::value().coeff,               1. );
    BOOST_CHECK_EQUAL( dim::mass<si>::value().coeff,                   1. );
    BOOST_CHECK_EQUAL( dim::momentum<si>::value().coeff,               1. );
    BOOST_CHECK_EQUAL( dim::angular_momentum<si>::value().coeff,       1. );
    BOOST_CHECK_EQUAL( dim::power<si>::value().coeff,                  1. );
    BOOST_CHECK_EQUAL( dim::energy<si>::value().coeff,                 1. );
    BOOST_CHECK_EQUAL( dim::electric::resistance<si>::value().coeff,   1. );
    BOOST_CHECK_EQUAL( dim::electric::potential<si>::value().coeff,    1. );
    BOOST_CHECK_EQUAL( dim::electric::capacitance<si>::value().coeff,  1. );
    BOOST_CHECK_EQUAL( dim::magnetic::flux<si>::value().coeff,         1. );
    BOOST_CHECK_EQUAL( dim::magnetic::flux_density<si>::value().coeff, 1. );
    BOOST_CHECK_EQUAL( dim::magnetic::field<si>::value().coeff,        1. );
    BOOST_CHECK_EQUAL( dim::magnetic::inductance<si>::value().coeff,   1. );

    /* now check various derived dimensions in various systems. */
    BOOST_CHECK_EQUAL( dim::charge<esu>::value(),     unit::statCoulomb );
    BOOST_CHECK_EQUAL( dim::electric::current<esu>::value(),    unit::statAmpere );
    BOOST_CHECK_EQUAL( dim::electric::current<atomic>::value(),
                       constant::si::e * constant::si::Hartree /
                       constant::si::h_bar/unit::radian );
    BOOST_CHECK_EQUAL( dim::electric::potential<esu>::value(),  unit::statVolt );
    BOOST_CHECK_EQUAL( dim::electric::potential<atomic>::value(),
                       constant::si::Hartree / constant::si::e );
    BOOST_CHECK_EQUAL( dim::magnetic::flux<atomic>::value(), 
                       (constant::si::h_bar*unit::radian / constant::si::e) );
    BOOST_CHECK_EQUAL( dim::magnetic::field<atomic>::value(), 
                       (constant::si::h_bar*unit::radian / constant::si::e) /
                       SQR(constant::si::a_0) );
    BOOST_CHECK_EQUAL( dim::magnetic::flux<esu>::value(),       unit::statMaxwell );
    BOOST_CHECK_EQUAL( dim::magnetic::field<esu>::value(),
                       unit::statMaxwell / SQR(unit::cm) );
    BOOST_CHECK_EQUAL( dim::magnetic::flux<emu>::value(),       unit::Maxwell );
    BOOST_CHECK_EQUAL( dim::magnetic::field<emu>::value(),      unit::Gauss );
  
    /* These two test the compile time conversion selection function. */
    BOOST_CHECK_EQUAL( (make_convert_ratio<si,esu,dim::force>::value()), Quantity(1e-5) );
    BOOST_CHECK_EQUAL( (convert<esu>(DimQuantity<si,dim::force>(Quantity(1.0))).value), Quantity(1e-5) );
    BOOST_CHECK_EQUAL( (convert<si>(DimQuantity<cgs,dim::velocity>(Quantity(1.0))).value), Quantity(100.) );


    /* this is what the aggregate dimension conversion should do. */
    BOOST_CHECK_EQUAL( ( make_convert_ratio<esu,si,dim::electric::capacitance>::value() /
                         make_convert_ratio<esu,si,dim::length>::value
                       ),
                       1. / ((unit::statCoul / unit::statVolt ) / unit::cm).coeff
                     );

    BOOST_CHECK_EQUAL(
      ( make_convert_ratio<esu,si,constant::detail::capacitance_per_length>::value() ),
      1. / ((unit::statCoul / unit::statVolt ) / unit::cm).coeff
    );
  
    /* This tests the runtime conversion selection function. */
    BOOST_CHECK_EQUAL(
      (convert( DimQuantity<esu,dim::force>(dim::force<esu>::value()),si::Id ).value),
      1e-5*dim::force<si>::value
    );
  }
#endif

BOOST_AUTO_TEST_SUITE_END();

