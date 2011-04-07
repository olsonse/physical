/** \file
 * Assignment of unit system names (from string values).
 */

#include <physical/system.h>
#define PHYSICAL_DATA_FOR_RUNTIME
#  include <physical/system.h>
#undef PHYSICAL_DATA_FOR_RUNTIME


namespace physical {
  namespace system {
    template<> const std::string si::name = "SI";
    template<> const std::string atomic::name = "atomic";
    template<> const std::string cgs::name = "cgs";
    template<> const std::string esu::name = "esu";
    template<> const std::string emu::name = "emu";
    template<> const std::string gaussian::name = "gaussian";
    template<> const std::string heaviside_lorentz::name = "heaviside_lorentz";
  }/* namespace physical::system */
}/* namespace physical */

namespace runtime {
namespace physical {
  namespace system {
    template<> const std::string si::name = ::physical::system::si::name;
    template<> const std::string atomic::name = ::physical::system::atomic::name;
    template<> const std::string cgs::name = ::physical::system::cgs::name;
    template<> const std::string esu::name = ::physical::system::esu::name;
    template<> const std::string emu::name = ::physical::system::emu::name;
    template<> const std::string gaussian::name = ::physical::system::gaussian::name;
    template<> const std::string heaviside_lorentz::name = ::physical::system::heaviside_lorentz::name;
  }/* namespace runtime::physical::system */
}/* namespace runtime::physical */
}/* namespace runtime */
