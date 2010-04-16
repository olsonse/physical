/** \file
 * Various constants, most of which have been pulled in May 2009 from
 * http://physics.nist.gov/cuu/Constants/index.html.
 */

#if ( defined(PHYSICAL_DATA_FOR_RUNTIME) && \
     !defined(runtime_physical_constant_si_h) ) || \
    (!defined(PHYSICAL_DATA_FOR_RUNTIME) && \
     !defined(physical_constant_si_h) )

#  if defined(PHYSICAL_DATA_FOR_RUNTIME)
#    define runtime_physical_constant_si_h
#  else
#    define physical_constant_si_h
#  endif

#  if defined (PHYSICAL_DATA_FOR_RUNTIME)
namespace runtime {
#  endif

    // #### BEGIN OF CONSTANT CREATION #### #
_OPEN_NAMESPACE(constant_si,physical) {
    _OPEN_NAMESPACE(constant_si,constant) {
      _BEGIN_NAMESPACE(si) {
        _QUANTITYn(pi,                unit::pi / unit::rad,        "unitless pi");
        _QUANTITYn(c,                 2.99792458e8*unit::m/unit::s,"speed of light");
        _QUANTITYn(Mach,              331.46 * unit::m / unit::s,  "speed of sound");
        _QUANTITYn(h,                 6.62606896e-34
                                      * unit::J * unit::s,         "Planck constant");
        _QUANTITYn(h_bar,             h/(2.0*pi*unit::rad),        "Planck constant");
        _QUANTITY(g,                  unit::gravity);
        _QUANTITYn(e,                 1.602176487e-19 * unit::C,   "electron charge");
        _QUANTITYn(eV,                e * unit::V,                 "electron Volt");
        _QUANTITYn(keV,               1000.0*eV,                   "kilo-electron Volt");
        _QUANTITYn(MeV,               1000000.0*eV,                "Mega-electron Volt");
        _QUANTITYn(GeV,               1000000000.0*eV,             "Giga-electron Volt");
        _QUANTITYn(Rinfinity,         10973731.568527/unit::m,     "Rydberg constant (R_inf)");
        _QUANTITYn(Rydberg,           h * c * Rinfinity,           "Rydberg energy");
        _QUANTITY(Rydbergs,           Rydberg);
        _QUANTITYn(Hartree,           2*Rydberg,                   "Atomic energy unit");
        _QUANTITY(Hartrees,           Hartree);
        _QUANTITYn(m_e,               9.10938215e-31*unit::kg,     "electron mass");
        _QUANTITYn(m_p,               1.672621637e-27*unit::kg,    "proton mass");
        _QUANTITYn(m_d,               1875.612793*MeV/(c*c),       "deuteron mass");
        _QUANTITYn(atomic_mass_unit,  1.660538782e-27*unit::kg,    "unified atomic mass unit");
        _QUANTITY(atomic_mass_units,  atomic_mass_unit);
        _QUANTITY(amu,                atomic_mass_unit);
        _QUANTITY(Dalton,             atomic_mass_unit);
        _QUANTITY(Daltons,            Dalton);
        _QUANTITYn(epsilon0,          8.854187817e-12
                                      * unit::F / unit::m,         "permittivity of free space");
        _QUANTITYn(k_E,               1./(4*pi*epsilon0),          "Coulomb constant");
        _QUANTITYn(mu0,               4*pi*1e-7
                                      * unit::N
                                      / ( unit::A * unit::A ),     "permeability of free space");
        _QUANTITYun(alpha,            7.2973525376e-3, units_map(),"fine-structure constant");
        _QUANTITYun(g_e,              -2.0023193043622, units_map(),"electron g-factor");
        _QUANTITYun(g_d,              0.8574382308, units_map(),   "deuteron g-factor");
        _QUANTITYn(r_e,               2.81794092e-15 * unit::m,    "classical electron radius");
        _QUANTITYn(lambda_C,          h / (m_e * c),               "Compton wavelength");
        _QUANTITYn(lambda_C_bar,      lambda_C/(2*pi*unit::rad),   "Compton wavelength (over 2pi)");
        _QUANTITYn(a_0,               alpha/(4*pi * Rinfinity),    "Bohr radius");
        _QUANTITYn(lambda_1eV,        h / (eV/c),                  "wavelength of 1 eV/c particle");
        _QUANTITYn(sigma_0,           0.6652458558*unit::barns,    "Thomson cross section");
        _QUANTITYn(mu_B,              5.7883818e-11*MeV / unit::T, "Bohr magneton");
        _QUANTITYn(mu_N,              3.1524513e-14*MeV / unit::T, "nuclear magneton");
        _QUANTITYn(e_m_e,             e / m_e,                     "electron cyclotron frequency/field");
        _QUANTITYn(e_m_p,             e / m_p,                     "proton cyclotron frequency/field");
        _QUANTITYn(G,                 6.67428e-11
                                      * unit::m * unit::m * unit::m
                                      / (  unit::kg
                                         * unit::s * unit::s ),    "gravitational constant");
        _QUANTITYun(N_A,              6.02214179e23, units_map(),  "Avogadro's constant");
        _QUANTITYn(K_B,               1.3806504e-23
                                      * unit::J / unit::K,         "Boltzmann constant");
        _QUANTITYn(stdtemp,           273.15 * unit::K,            "standard temperature");
        _QUANTITYn(R,                 K_B * N_A,                   "universal gas constant");
        _QUANTITYn(V_molar,           unit::mol * R * stdtemp
                                      / unit::atm,                 "molar volume, ideal gas at standard temperature and pressure");
        _QUANTITYn(sigma_SB,          5.670400e-8
                                      * unit::W
                                      / (  unit::m * unit::m
                                         * unit::K * unit::K
                                         * unit::K * unit::K ),    "Stefan-Boltzmann constant");
        _QUANTITYn(z0,                c*mu0,                       "impedance of free space");
      _END_NAMESPACE}
    _CLOSE_NAMESPACE(constant_si)}
_CLOSE_NAMESPACE(constant_si)}

#  if defined (PHYSICAL_DATA_FOR_RUNTIME)
}/* namespace runtime. */
#  endif

#endif // physical_constant_si_h
