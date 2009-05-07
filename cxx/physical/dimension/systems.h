/** \file
 * A registry for physical::quantity types that have been initialized
 * properly.
 *
 * */

#if ( defined(PHYSICAL_DATA_FOR_RUNTIME) && \
     !defined(runtime_physical_dimension_systems_h) ) || \
    (!defined(PHYSICAL_DATA_FOR_RUNTIME) && \
     !defined(physical_dimension_systems_h) )

#  if defined(PHYSICAL_DATA_FOR_RUNTIME)
#    define runtime_physical_dimension_systems_h
#  else
#    define physical_dimension_systems_h
#  endif

#include <physical/system.h>
#include <physical/constant/si.h>
#include <physical/dimension/define.h>



#  if defined (PHYSICAL_DATA_FOR_RUNTIME)
namespace runtime {
#  endif


namespace physical {
  /* **** BEGIN UNIT SYSTEM CONSTANTS **** */
  namespace dimension {
#define PHYSICAL_TCQ    template<> const Quantity

    /* {****** BEGIN SI UNIT SYSTEM ****** */
    using namespace system;
    PHYSICAL_TCQ  length     <si>::value = unit::m;
    PHYSICAL_TCQ  mass       <si>::value = unit::kg;
    PHYSICAL_TCQ  time       <si>::value = unit::s;
    PHYSICAL_TCQ  charge     <si>::value = unit::Coulomb;
    /* }****** END SI UNIT SYSTEM ****** */


    /* {****** BEGIN ATOMIC UNIT SYSTEM ****** */
    PHYSICAL_TCQ  length     <atomic>::value  = constant::si::a_0;
    PHYSICAL_TCQ  mass       <atomic>::value  = constant::si::m_e;
    PHYSICAL_TCQ  time       <atomic>::value  = constant::si::h_bar
                                              / constant::si::Hartree;
    PHYSICAL_TCQ  charge     <atomic>::value  = constant::si::e;
    /* }******   END ATOMIC UNIT SYSTEM ****** */


    /* {****** BEGIN cgs UNIT SYSTEM ****** */
    PHYSICAL_TCQ  length     <cgs>::value = unit::cm;
    PHYSICAL_TCQ  mass       <cgs>::value = unit::g;
    PHYSICAL_TCQ  time       <cgs>::value = unit::s;
    /* NOTE:  charge is not specified for general cgs system */
    /* }******   END cgs UNIT SYSTEM ****** */


    /* {****** BEGIN esu UNIT SYSTEM ****** */
    PHYSICAL_TCQ  length     <esu>::value = length<cgs>::value;
    PHYSICAL_TCQ  mass       <esu>::value = mass<cgs>::value;
    PHYSICAL_TCQ  time       <esu>::value = time<cgs>::value;
    PHYSICAL_TCQ  charge     <esu>::value = unit::statCoulomb;
    /* }******   END esu UNIT SYSTEM ****** */


    /* {****** BEGIN emu UNIT SYSTEM ****** */
    PHYSICAL_TCQ  length     <emu>::value = length<cgs>::value;
    PHYSICAL_TCQ  mass       <emu>::value = mass<cgs>::value;
    PHYSICAL_TCQ  time       <emu>::value = time<cgs>::value;
    PHYSICAL_TCQ  charge     <emu>::value = unit::abCoulomb;
    /* }******   END emu UNIT SYSTEM ****** */



    /* {****** BEGIN gaussian UNIT SYSTEM ****** */
    PHYSICAL_TCQ  length     <gaussian>::value = length<cgs>::value;
    PHYSICAL_TCQ  mass       <gaussian>::value = mass<cgs>::value;
    PHYSICAL_TCQ  time       <gaussian>::value = time<cgs>::value;
    /* }******   END gaussian UNIT SYSTEM ****** */



    /* {****** BEGIN heaviside_lorentz UNIT SYSTEM ****** */
    PHYSICAL_TCQ  length     <heaviside_lorentz>::value = length<cgs>::value;
    PHYSICAL_TCQ  mass       <heaviside_lorentz>::value = mass<cgs>::value;
    PHYSICAL_TCQ  time       <heaviside_lorentz>::value = time<cgs>::value;
    /* }******   END heaviside_lorentz UNIT SYSTEM ****** */
  }


#undef PHYSICAL_TCQ
}

#  if defined (PHYSICAL_DATA_FOR_RUNTIME)
}/* namespace runtime. */
#  endif

#endif // physical_dimension_systems_h
