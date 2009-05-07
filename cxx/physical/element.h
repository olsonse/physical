/** \file
 * A set of data for elements from the periodic table.
 */

#if ( defined(PHYSICAL_DATA_FOR_RUNTIME) && \
     !defined(runtime_physical_element_h) ) || \
    (!defined(PHYSICAL_DATA_FOR_RUNTIME) && \
     !defined(physical_element_h) )

#  if defined(PHYSICAL_DATA_FOR_RUNTIME)
#    define runtime_physical_element_h
#  else
#    define physical_element_h
#  endif

#  if defined (PHYSICAL_DATA_FOR_RUNTIME)
namespace runtime {
#  endif

_OPEN_NAMESPACE(physical_element,physical) {
    // #### BEGIN OF ELEMENT CREATION #### #
    // FIXME:  finish filling out this periodic table data
    /* This data is taken from physics.nist.gov. */
#define _ELEMENT(name,sym,n,m,i) \
    _BEGIN_NAMESPACE(name) { \
        _QUANTITYn(number,    PHYSICAL_QUANTITY_COEFF_TYPE(n),"atomic number of "     #name); \
        _QUANTITYn(mass,        m * constant::si::amu, "atomic mass of "       #name); \
        _QUANTITYn(ionization,  i * constant::si::eV,  "ionization energy of " #name); \
    _END_NAMESPACE} \
    _ALIAS_NAMESPACE(sym, name);

    /** Periodic table information.
     * @see http://physics.nist.gov/PhysRefData/Elements/index.html
     */
    _BEGIN_NAMESPACE(element) {
        //       long-name    abrv.   n        mass(amu)  outer-electron ionization (eV)
        _ELEMENT(hydrogen,      H,    1,      1.00794,      13.5984 );
        _ELEMENT(helium,        He,   2,      4.002602,     24.5874 );
        _ELEMENT(lithium,       Li,   3,      6.941,         5.3917 );
        _ELEMENT(beryllium,     Be,   4,      9.012182,      9.3227 );
        _ELEMENT(boron,          B,   5,     10.812,         8.2980 );
        _ELEMENT(carbon,         C,   6,      12.0107,      11.2603 );
        _ELEMENT(nitrogen,       N,   7,      14.0067,      14.5341 );
        _ELEMENT(oxygen,         O,   8,      15.9994,      13.6181 );
        _ELEMENT(fluorine,       F,   9,      18.9984032,   17.4228 );
        _ELEMENT(neon,          Ne,  10,      20.1797,      21.5645 );
        _ELEMENT(sodium,        Na,  11,      22.989770,     5.1391 );
        _ELEMENT(magnesium,     Mg,  12,      24.3051,       7.6462 );
        _ELEMENT(aluminium,     Al,  13,      26.981538,     5.9858 );
        _ELEMENT(silicon,       Si,  14,      28.0855,       8.1517 );
        _ELEMENT(phosphorus,     P,  15,      30.973761,    10.4867 );
        _ELEMENT(sulfur,         S,  16,      32.065,       10.3600 );
        _ELEMENT(chlorine,      Cl,  17,      35.453,       12.9676 );
        _ELEMENT(argon,         Ar,  18,      39.948,       15.7596 );
        _ELEMENT(potassium,      K,  19,      39.0983,       4.3407 );
        _ELEMENT(calcium,       Ca,  20,      40.078,        6.1132 );
        _ELEMENT(scandium,      Sc,  21,      44.955911,     6.5615 );
        _ELEMENT(titanium,      Ti,  22,      47.867,        6.8281 );
        _ELEMENT(vanadium,       V,  23,      50.9415,       6.7462 );
        _ELEMENT(chromium,      Cr,  24,      51.9961,       6.7665 );
        _ELEMENT(manganese,     Mn,  25,      54.9380499,    7.4340 );
        _ELEMENT(iron,          Fe,  26,      55.845,        7.9024 );
        _ELEMENT(cobalt,        Co,  27,      58.9332009,    7.8810 );
        _ELEMENT(nickel,        Ni,  28,      58.6934,       7.6398 );
        _ELEMENT(copper,        Cu,  29,      63.546,        7.7264 );
        _ELEMENT(zinc,          Zn,  30,      65.409,        9.3942 );
        _ELEMENT(krypton,       Kr,  36,      83.798,       13.9996 );
        _ELEMENT(rubidium,      Rb,  37,      85.4678,       4.1771 );
        _ELEMENT(xenon,         Xe,  54,     131.293,       12.1298 );
        _ELEMENT(cesium,        Cs,  55,     132.90545,      3.8939 );
        _ELEMENT(mercury,       Hg,  80,     200.59,        10.4375 );
        _ELEMENT(francium,      Fr,  87,     223,            4.0727 );
    _END_NAMESPACE}
    _ALIAS_NAMESPACE(elements, element);
    // ####   END OF ELEMENT CREATION #### #
_CLOSE_NAMESPACE(physical_element)}
#undef _ELEMENT

#  if defined (PHYSICAL_DATA_FOR_RUNTIME)
}/* namespace runtime. */
#  endif

#endif // physical_element_h
