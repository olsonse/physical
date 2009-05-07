/** \file
 * Definitions of unit systems.
 *
 * Note:  there is very little actual useful code here.  This file mainly
 * provides the unit system tag types that can be used to select system
 * dependent dimensions and constants.
 */

#ifndef physical_sysytem_h
#define physical_sysytem_h

#include <string>

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


#define make_sys(sys,label) \
    typedef define<id::sys> sys; template<> const std::string sys::name = label;

    make_sys(    si, "SI");
    make_sys(atomic, "atomic");

    /* *** CGS UNIT SYSTEMS *** */
    /** Basic CGS unit system -- no electromagnetic dimensions. */
    make_sys(   cgs, "cgs");
    make_sys(   esu, "esu");
    make_sys(   emu, "emu");
    typedef esu electrostatic;
    typedef emu electromagnetic;

    make_sys(gaussian, "gaussian");
    make_sys(heaviside_lorentz, "heaviside_lorentz");
    typedef heaviside_lorentz hlu;
  }/* namespace physical::system */
}/* namespace physical */

/* import the system tags into runtime as well. */
namespace runtime {
  namespace physical {
    namespace system = ::physical::system;
  }
}

#endif // physical_sysytem_h
