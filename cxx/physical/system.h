/** \file
 * Definitions of unit systems.
 *
 * Note:  there is very little actual useful code here.  This file mainly
 * provides the unit system tag types that can be used to select system
 * dependent dimensions and constants.
 */

#if ( defined(PHYSICAL_DATA_FOR_RUNTIME) && \
     !defined(runtime_physical_system_h) ) || \
    (!defined(PHYSICAL_DATA_FOR_RUNTIME) && \
     !defined(physical_system_h) )

#  if defined(PHYSICAL_DATA_FOR_RUNTIME)
#    define runtime_physical_system_h
#  else
#    define physical_system_h
#  endif

#include <string>

#  if defined (PHYSICAL_DATA_FOR_RUNTIME)
namespace runtime {
#  endif

namespace physical {
  namespace system {
    namespace id {
      enum SYSTEM {
        si,
        cgs,
        esu,
        emu,
        atomic,
        gaussian,
        heaviside_lorentz
      };
    }

    /** template tag class for unit systems. */
    template < enum id::SYSTEM ID >
    struct define {
      static const enum id::SYSTEM Id = ID;
      static const std::string name;
    };


#define physical_make_sys(sys)   typedef define<id::sys> sys

    physical_make_sys(si);
    physical_make_sys(atomic);

    /* *** CGS UNIT SYSTEMS *** */
    /** Basic CGS unit system -- no electromagnetic dimensions. */
    physical_make_sys(cgs);
    physical_make_sys(esu);
    physical_make_sys(emu);
    typedef esu electrostatic;
    typedef emu electromagnetic;

    physical_make_sys(gaussian);
    physical_make_sys(heaviside_lorentz);
    typedef heaviside_lorentz hlu;

#undef physical_make_sys
  }/* namespace physical::system */
}/* namespace physical */

#  if defined (PHYSICAL_DATA_FOR_RUNTIME)
}/* namespace runtime. */
#  endif

#endif // physical_sysytem_h
