#ifndef physical_detail_ConvertCoeff_h
#define physical_detail_ConvertCoeff_h

#include <complex>

namespace runtime {
  namespace physical {
    namespace detail {

      template < typename T, typename T2 >
      struct ConvertCoeff {
        T2 operator()( const T & coeff ) {
          return static_cast<T2>(coeff);
        }
      };

      template < typename T, typename T2 >
      struct ConvertCoeff< std::complex<T>, std::complex<T2> > {
        T2 operator()( const T & coeff ) {
          return static_cast< std::complex<T2> >(coeff);
        }
      };

      template < typename T, typename T2 >
      struct ConvertCoeff< std::complex<T>, T2 > {
        T2 operator()( const T & coeff ) {
          if (coeff.imag() != 0.0)
            throw exception(ComplexNotSupported);
          else
            return static_cast< T2 >(coeff.real());
        }
      };

    }/* namespace runtime::physical::detail */
  }/* namespace runtime::physical */
}/* namespace runtime */

#endif // physical_detail_ConvertCoeff_h
