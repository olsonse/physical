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
    template < int U > \
    struct dim<SYS,U> { \
      static const Quantity value; \
    }; \
    template<int U> const Quantity dim<SYS,U>::value = val;

#ifdef PTU
#  error PTU was already defined.  Need to pick another name for this macro!
#endif
/** The stupid IBM compiler doesn't respect default parameters correctly. */
#define PTU(SYS)  SYS,U

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
    PHYSICAL_TCQ(length, esu, length<PTU(cgs)>::value);
    PHYSICAL_TCQ(mass  , esu, mass<PTU(cgs)>::value);
    PHYSICAL_TCQ(time  , esu, time<PTU(cgs)>::value);
    PHYSICAL_TCQ(charge, esu, unit::statCoulomb);
    /* }******   END esu UNIT SYSTEM ****** */


    /* {****** BEGIN emu UNIT SYSTEM ****** */
    PHYSICAL_TCQ(length, emu, length<PTU(cgs)>::value);
    PHYSICAL_TCQ(mass  , emu, mass<PTU(cgs)>::value);
    PHYSICAL_TCQ(time  , emu, time<PTU(cgs)>::value);
    PHYSICAL_TCQ(charge, emu, unit::abCoulomb);
    /* }******   END emu UNIT SYSTEM ****** */



    /* {****** BEGIN gaussian UNIT SYSTEM ****** */
    PHYSICAL_TCQ(length, gaussian, length<PTU(cgs)>::value);
    PHYSICAL_TCQ(mass  , gaussian, mass<PTU(cgs)>::value);
    PHYSICAL_TCQ(time  , gaussian, time<PTU(cgs)>::value);
    /* }******   END gaussian UNIT SYSTEM ****** */



    /* {****** BEGIN heaviside_lorentz UNIT SYSTEM ****** */
    PHYSICAL_TCQ(length, heaviside_lorentz, length<PTU(cgs)>::value);
    PHYSICAL_TCQ(mass  , heaviside_lorentz, mass<PTU(cgs)>::value);
    PHYSICAL_TCQ(time  , heaviside_lorentz, time<PTU(cgs)>::value);
    /* }******   END heaviside_lorentz UNIT SYSTEM ****** */
  }


#undef PHYSICAL_TCQ
#undef PTU
}

#  if defined (PHYSICAL_DATA_FOR_RUNTIME)
}/* namespace runtime. */
#  endif

#endif // physical_dimension_systems_h
