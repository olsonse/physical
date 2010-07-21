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
#define PHYSICAL_TCQ(dim,SYS,val) \
    template<> \
    struct dim<SYS> { \
      static const Quantity & value() { \
        static const Quantity _value = val; \
        return _value; \
      } \
    };


    /* {****** BEGIN SI UNIT SYSTEM ****** */
    using namespace system;
    PHYSICAL_TCQ(length, si, unit::m);
    PHYSICAL_TCQ(mass  , si, unit::kg);
    PHYSICAL_TCQ(time  , si, unit::s);
    PHYSICAL_TCQ(charge, si, unit::Coulomb);
    /* }****** END SI UNIT SYSTEM ****** */


    /* {****** BEGIN ATOMIC UNIT SYSTEM ****** */
    PHYSICAL_TCQ(length, atomic, constant::si::a_0);
    PHYSICAL_TCQ(mass  , atomic, constant::si::m_e);
    PHYSICAL_TCQ(time  , atomic, constant::si::h_bar
                                 / constant::si::Hartree
                                 * unit::radian);
    PHYSICAL_TCQ(charge, atomic, constant::si::e);
    /* }******   END ATOMIC UNIT SYSTEM ****** */


    /* {****** BEGIN cgs UNIT SYSTEM ****** */
    PHYSICAL_TCQ(length, cgs,  unit::cm);
    PHYSICAL_TCQ(mass  , cgs,  unit::g);
    PHYSICAL_TCQ(time  , cgs,  unit::s);
    /* NOTE:  charge is not specified for general cgs system */
    /* }******   END cgs UNIT SYSTEM ****** */


    /* {****** BEGIN esu UNIT SYSTEM ****** */
    PHYSICAL_TCQ(length, esu, length<cgs>::value());
    PHYSICAL_TCQ(mass  , esu, mass<cgs>::value());
    PHYSICAL_TCQ(time  , esu, time<cgs>::value());
    PHYSICAL_TCQ(charge, esu, unit::statCoulomb);
    /* }******   END esu UNIT SYSTEM ****** */


    /* {****** BEGIN emu UNIT SYSTEM ****** */
    PHYSICAL_TCQ(length, emu, length<cgs>::value());
    PHYSICAL_TCQ(mass  , emu, mass<cgs>::value());
    PHYSICAL_TCQ(time  , emu, time<cgs>::value());
    PHYSICAL_TCQ(charge, emu, unit::abCoulomb);
    /* }******   END emu UNIT SYSTEM ****** */



    /* {****** BEGIN gaussian UNIT SYSTEM ****** */
    PHYSICAL_TCQ(length, gaussian, length<cgs>::value());
    PHYSICAL_TCQ(mass  , gaussian, mass<cgs>::value());
    PHYSICAL_TCQ(time  , gaussian, time<cgs>::value());
    /* }******   END gaussian UNIT SYSTEM ****** */



    /* {****** BEGIN heaviside_lorentz UNIT SYSTEM ****** */
    PHYSICAL_TCQ(length, heaviside_lorentz, length<cgs>::value());
    PHYSICAL_TCQ(mass  , heaviside_lorentz, mass<cgs>::value());
    PHYSICAL_TCQ(time  , heaviside_lorentz, time<cgs>::value());
    /* }******   END heaviside_lorentz UNIT SYSTEM ****** */
  }


#undef PHYSICAL_TCQ
}

#  if defined (PHYSICAL_DATA_FOR_RUNTIME)
}/* namespace runtime. */
#  endif

#endif // physical_dimension_systems_h
