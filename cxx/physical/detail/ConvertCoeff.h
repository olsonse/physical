#ifndef physical_detail_ConvertCoeff_h
#define physical_detail_ConvertCoeff_h

#include <physical/except.h>

#include <complex>

namespace runtime {
  namespace physical {
    namespace detail {

      template < typename Tdst >
      struct ConvertHelp {
        template < typename Tsrc >
        Tdst operator()( const Tsrc & coeff ) {
          return static_cast<Tdst>(coeff);
        }

        template < typename Tcsrc >
        Tdst operator()( const std::complex<Tcsrc> & coeff ) {
          if (coeff.imag() != 0.0)
            throw exception(ComplexNotSupported);
          else
            return static_cast< Tdst >(coeff.real());
        }
      };

      template < typename Tdst>
      struct ConvertHelp< std::complex<Tdst> > {
        template < typename Tcsrc >
        std::complex<Tdst> operator()( const std::complex<Tcsrc> & coeff ) {
          return static_cast< std::complex<Tdst> >(coeff);
        }
      };

      template < typename Tdst, typename Tsrc >
      Tdst ConvertCoeff( const Tsrc & coeff ) {
        return ConvertHelp<Tdst>()(coeff);
      }

    }/* namespace runtime::physical::detail */
  }/* namespace runtime::physical */
}/* namespace runtime */

#endif // physical_detail_ConvertCoeff_h
