/** \file
 * Expression of units in an arbitrary unit system.
 *
 * */

#if ( defined(PHYSICAL_DATA_FOR_RUNTIME) && \
     !defined(runtime_physical_constant_conversion_h) ) || \
    (!defined(PHYSICAL_DATA_FOR_RUNTIME) && \
     !defined(physical_constant_conversion_h) )

#  if defined(PHYSICAL_DATA_FOR_RUNTIME)
#    define runtime_physical_constant_conversion_h
#  else
#    define physical_constant_conversion_h
#  endif


#  include <physical/dimension/define.h>
#  include <physical/dimension/convert.h>
#  include <physical/constant/si.h>



#  if defined (PHYSICAL_DATA_FOR_RUNTIME)
namespace runtime {
#  endif

namespace physical {
  namespace constant {
#   define _TQUANTITYn(v,dims) \
    /* convert_v_from_si class exists because I can't pass commas to macros.*/ \
    template < typename T >  \
    struct convert_##v##_from_si : make_convert_ratio<system::si,dims,T> {}; \
    /* definition of where the value is stored. */ \
    template< typename T > \
    struct v { \
      static const Quantity value; \
    }; \
    /* Here is where the generic conversion happens... */ \
    template <typename T> \
    const Quantity v<T>::value = \
      PHYSICAL_QUANTITY_INITn( \
        T::name + "::" + #v, \
        constant::si::v * convert_##v##_from_si<T>::value, \
        constant::si::v.name + '(' + T::name + " units)" )

    _TQUANTITYn(pi,                 dimension::unity);
    _TQUANTITYn(c,                  dimension::velocity);
    _TQUANTITYn(Mach,               dimension::velocity);
    _TQUANTITYn(h,                  dimension::angular_momentum);
    _TQUANTITYn(h_bar,              dimension::angular_momentum);
    _TQUANTITYn(g,                  dimension::acceleration);
    _TQUANTITYn(e,                  dimension::charge);
    _TQUANTITYn(eV,                 dimension::energy);
    _TQUANTITYn(keV,                dimension::energy);
    _TQUANTITYn(MeV,                dimension::energy);
    _TQUANTITYn(GeV,                dimension::energy);
    _TQUANTITYn(Rinfinity,          dimension::inverse_length);
    _TQUANTITYn(Rydberg,            dimension::energy);
    _TQUANTITYn(Rydbergs,           dimension::energy);
    _TQUANTITYn(Hartree,            dimension::energy);
    _TQUANTITYn(Hartrees,           dimension::energy);
    _TQUANTITYn(m_e,                dimension::mass);
    _TQUANTITYn(m_p,                dimension::mass);
    _TQUANTITYn(m_d,                dimension::mass);
    _TQUANTITYn(atomic_mass_unit,   dimension::mass);
    _TQUANTITYn(atomic_mass_units,  dimension::mass);
    _TQUANTITYn(amu,                dimension::mass);
    _TQUANTITYn(Dalton,             dimension::mass);
    _TQUANTITYn(Daltons,            dimension::mass);
    // typedef make_dim< dimension::capacitance,
    //                   dimension::exp_dim<dimension::length,-1>::type
    //                 >::type capacitance_per_length;
    _TQUANTITYn(epsilon0,           dimension::electric::capacitance_per_length);
    _TQUANTITYn(k_E,                dimension::electric::length_per_capacitance);
    _TQUANTITYn(mu0,                dimension::magnetic::permeability);
    _TQUANTITYn(alpha,              dimension::unity);
    _TQUANTITYn(g_e,                dimension::unity);
    _TQUANTITYn(g_d,                dimension::unity);
    _TQUANTITYn(r_e,                dimension::length);
    _TQUANTITYn(lambda_C,           dimension::length);
    _TQUANTITYn(lambda_C_bar,       dimension::length);
    _TQUANTITYn(a_0,                dimension::length);
    _TQUANTITYn(lambda_1eV,         dimension::length);
    _TQUANTITYn(sigma_0,            dimension::area);
//  _TQUANTITYn(mu_B,               5.78838263e-11*MeV/T);
//  _TQUANTITYn(mu_N,               3.15245166e-14*MeV/T);
//  _TQUANTITYn(e_m_e,              1.75881962e11*C/kg*(rad/(s*T)));
//  _TQUANTITYn(e_m_p,              9.5788309e7*C/kg*(rad/(s*T)));
//  _TQUANTITYn(G,                  6.67259e-11*m*m*m/(kg*s*s));
    _TQUANTITYn(N_A,                dimension::unity);
//  _TQUANTITYn(K_B,                1.380658e-23*J/K);
    _TQUANTITYn(stdtemp,            dimension::temperature);
    _TQUANTITYn(R,                  dimension::unity);
    _TQUANTITYn(V_molar,            dimension::volume);
//  _TQUANTITYn(sigma_SB,           5.67051e-8*W/(m*m*K*K*K*K));
  }/* ****   END UNIT SYSTEM CONSTANTS **** */

#undef _TQUANTITYn
}

#  if defined (PHYSICAL_DATA_FOR_RUNTIME)
}/* namespace runtime. */
#  endif


#endif // physical_constant_conversion_h
