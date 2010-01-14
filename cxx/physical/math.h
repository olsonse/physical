#ifndef physical_math_h
#define physical_math_h

#include <physical/runtime.h>

/* FIXME:  the following should be removed if the new standard is used.
 * For now we use boost to implement the inverse trig functions for
 * std::complex.
 */
#include <boost/math/complex/acos.hpp>
#include <boost/math/complex/asin.hpp>
#include <boost/math/complex/atan.hpp>
#include <boost/math/complex/acosh.hpp>
#include <boost/math/complex/asinh.hpp>
#include <boost/math/complex/atanh.hpp>

#include <complex>
#include <cmath>

namespace std {
  using ::acosh;
  using ::asinh;
  using ::atanh;

  using boost::math::acos;
  using boost::math::asin;
  using boost::math::atan;
  using boost::math::acosh;
  using boost::math::asinh;
  using boost::math::atanh;
}

namespace runtime {
  namespace physical {
    /** As set of unary mathematical functions that operate on quantity<T>
     * types.  Many of these are just wrappers for math.h functions.
     * */
    namespace math {
        /** Perform units checking for math functions of strictly dimensionless
         * arguments. */
        struct no_dims {
            template <class T>
            static inline void check(const quantity<T> & q) {
                (void)q.assertUnitless();
            }
        };
 
        /** Perform units checking for math functions of angle or dimensionless
         * arguments. */
        template <class T>
        struct w_angle {
            static inline void check(const quantity<T> & q) {
                /* FIXME:  should we allow the dimensionless case here too? */
                if (!q.units.empty() && q.units != physical::unit::radian.units) {
                    throw exception(UnitsMismatchF);
                }
            }
        };


        /** The power operator.
         * The templated ExpT parameter allows this function to instantiate the
         * correct pow<ExpT>(units_map&) function. 
         * */
        template<class T, class ExpT>
        inline quantity<T> pow(const quantity<T> & q, const ExpT & exponent) {
            return quantity<T>(std::pow(q.coeff, exponent), pow(q.units,exponent));
        }
 
        template<class T>
        inline quantity<T> sqrt(const quantity<T> & q) {
            return quantity<T>(std::sqrt(q.coeff), pow(q.units,0.5));
        };

        inline const double & conj( const double & d ) {
          return d;
        }

        inline const float & conj( const float & f ) {
          return f;
        }

        template<class T>
        inline quantity<T> conj(const quantity<T> & q) {
          using math::conj;
          using std::conj;
          return quantity<T>(conj(q.coeff), q.units);
        };

        template < typename T >
        struct Real {
          inline const T & operator()( const T & t ) {
            return t;
          }
        };

        template < typename T >
        struct Real< std::complex<T> > {
          inline const T & operator()( const std::complex<T> & t ) {
            return t.real();
          }
        };

        template<class T>
        inline quantity<T> real(const quantity<T> & q) {
          return quantity<T>(Real<T>()(q.coeff), q.units);
        };
 
        template < typename T >
        struct Imag {
          inline T operator()( const T & t ) {
            return 0;
          }
        };

        template < typename T >
        struct Imag< std::complex<T> > {
          inline const T & operator()( const std::complex<T> & t ) {
            return t.imag();
          }
        };

        template<class T>
        inline quantity<T> imag(const quantity<T> & q) {
          return quantity<T>(Imag<T>()(q.coeff), q.units);
        };
 
        template<class T>
        inline quantity<T> sin(const quantity<T> & q) {
            w_angle<T>::check(q);
            return std::sin(q.coeff);
        };
 
        template<class T>
        inline quantity<T> cos(const quantity<T> & q) {
            w_angle<T>::check(q);
            return std::cos(q.coeff);
        };
 
        template<class T>
        inline quantity<T> tan(const quantity<T> & q) {
            w_angle<T>::check(q);
            return std::tan(q.coeff);
        };
 
        template<class T>
        inline quantity<T> asin(const quantity<T> & q) {
            no_dims::check(q);
            return std::asin(q.coeff) * physical::unit::radian;
        };
 
        template<class T>
        inline quantity<T> acos(const quantity<T> & q) {
            no_dims::check(q);
            return std::acos(q.coeff) * physical::unit::radian;
        };
 
        template<class T>
        inline quantity<T> atan(const quantity<T> & q) {
            no_dims::check(q);
            return std::atan(q.coeff) * physical::unit::radian;
        };
 
        template<class T>
        inline quantity<T> sinh(const quantity<T> & q) {
            w_angle<T>::check(q);
            return std::sinh(q.coeff);
        };
 
        template<class T>
        inline quantity<T> cosh(const quantity<T> & q) {
            w_angle<T>::check(q);
            return std::cosh(q.coeff);
        };
 
        template<class T>
        inline quantity<T> tanh(const quantity<T> & q) {
            w_angle<T>::check(q);
            return std::tanh(q.coeff);
        };
 
        template<class T>
        inline quantity<T> asinh(const quantity<T> & q) {
            no_dims::check(q);
            return std::asinh(q.coeff) * physical::unit::radian;
        };
 
        template<class T>
        inline quantity<T> acosh(const quantity<T> & q) {
            no_dims::check(q);
            return std::acosh(q.coeff) * physical::unit::radian;
        };
 
        template<class T>
        inline quantity<T> atanh(const quantity<T> & q) {
            no_dims::check(q);
            return std::atanh(q.coeff) * physical::unit::radian;
        };
 
        template<class T>
        inline quantity<T> sinc(const quantity<T> & q) {
            w_angle<T>::check(q);
            return q.coeff== T(0) ? T(1) : std::sin(q.coeff) / q.coeff;
        };
 
        template<class T>
        inline quantity<T> exp(const quantity<T> & q) {
            w_angle<T>::check(q);
            return std::exp(q.coeff);
        };

        using ::erf;

        template < typename T >
        inline std::complex<T> erf( const std::complex<T> & ct ) {
          if (ct.imag() != 0.0)
            throw exception(ComplexNotSupported);
          return ::erf(ct.real());
        }
 
        template<class T>
        inline quantity<T> erf(const quantity<T> & q) {
            w_angle<T>::check(q);
            return erf(q.coeff);
        };

        using ::erfc;

        template < typename T >
        inline std::complex<T> erfc( const std::complex<T> & ct ) {
          if (ct.imag() != 0.0)
            throw exception(ComplexNotSupported);
          return ::erfc(ct.real());
        }
 
        template<class T>
        inline quantity<T> erfc(const quantity<T> & q) {
            w_angle<T>::check(q);
            return erfc(q.coeff);
        };
 
        template<class T>
        inline quantity<T> log(const quantity<T> & q) {
            no_dims::check(q);
            return std::log(q.coeff);
        };
 
        template<class T>
        inline quantity<T> log10(const quantity<T> & q) {
            no_dims::check(q);
            return std::log10(q.coeff);
        };
 
        using ::tgamma;
 
        template < typename T >
        inline std::complex<T> tgamma( const std::complex<T> & ct ) {
          if (ct.imag() != 0.0)
            throw exception(ComplexNotSupported);
          return ::tgamma(ct.real());
        }

        template<class T>
        inline quantity<T> tgamma(const quantity<T> & q) {
            no_dims::check(q);
            return tgamma(q.coeff);
        };

        template < typename T >
        inline std::complex<T> floor( const std::complex<T> & c ) {
          using std::floor;
          return std::complex<T>( floor(c.real()), floor(c.imag()) );
        }
 
        /** Compute the floor of the quantity. */
        template<class T>
        inline quantity<T> floor(const quantity<T> & q) {
            using math::floor;
            using std::floor;
            return quantity<T>(floor(q.coeff), q.units);
        };

        template < typename T >
        inline std::complex<T> ceil( const std::complex<T> & c ) {
          using std::ceil;
          return std::complex<T>( ceil(c.real()), ceil(c.imag()) );
        }
 
        /** Compute the ceil of the quantity. */
        template<class T>
        inline quantity<T> ceil(const quantity<T> & q) {
            using std::ceil;
            using math::ceil;
            return quantity<T>(ceil(q.coeff), q.units);
        };
 
        /** Compute the absolute value (magnitude) of the quantity. */
        template<class T>
        inline quantity<T> abs(const quantity<T> & q) {
            return quantity<T>(std::abs(q.coeff), q.units);
        };

    } /* namespace math. */

    /* ****   END QUANTITY OPERATORS **** */
  } /* namespace runtime::physical */
} /* namespace runtime */

#endif // physical_math_h
