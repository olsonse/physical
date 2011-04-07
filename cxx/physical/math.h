/** \file
 * Definition of math functions that can be used on runtime::physical::quantity
 * class instances.
 */

#ifndef physical_math_h
#define physical_math_h

#include <physical/runtime.h>

#ifndef BOOST_MATH_NOT_FOUND
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

  #ifdef _MSC_VER
    #include <boost/math/special_functions/acosh.hpp>
    #include <boost/math/special_functions/asinh.hpp>
    #include <boost/math/special_functions/atanh.hpp>
    #include <boost/math/special_functions/gamma.hpp>
    #include <boost/math/special_functions/erf.hpp>
  #endif
#endif

#include <complex>
#include <cmath>

namespace runtime {
  namespace physical {
    /** As set of unary mathematical functions that operate on quantity<T>
     * types.  Many of these are just wrappers for math.h functions.
     * \cond PHYSICAL_DETAIL_MATH
     * */
    namespace detail {

      /** collection of trig and other functions to use below. */
      namespace stdmath {
        using std::cos;
        using std::cosh;
        using std::acos;
        using std::sin;
        using std::sinh;
        using std::asin;
        using std::tan;
        using std::tanh;
        using std::atan;

        #ifndef _MSC_VER
          using ::acosh;
          using ::asinh;
          using ::atanh;

          using ::tgamma;
          using ::erf;
          using ::erfc;
        #else
          using boost::math::tgamma;
          using boost::math::erf;
          using boost::math::erfc;
        #endif

        #ifndef BOOST_MATH_NOT_FOUND
          using boost::math::acos;
          using boost::math::asin;
          using boost::math::atan;
          using boost::math::acosh;
          using boost::math::asinh;
          using boost::math::atanh;
        #else
          #define MISSING_FUNC(fun) \
          template <typename T> \
          static inline std::complex<T> fun ( const std::complex<T> & t ) { \
            using runtime::physical::exception; \
            throw exception(#fun ":  MISSING COMPLEX FUNCTION, no boost::math?"); \
          }

          MISSING_FUNC(acos)
          MISSING_FUNC(asin)
          MISSING_FUNC(atan)
          MISSING_FUNC(acosh)
          MISSING_FUNC(asinh)
          MISSING_FUNC(atanh)
        #endif
      } /* namespace runtime::physical::detail::stdmath. */


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
          if (!q.units.empty() && q.units != physical::unit::radian.units)
            throw exception(UnitsMismatchF);
        }
      };

      /** help physical::conj succeed. */
      inline const double & conj( const double & d ) {
        return d;
      }

      /** help physical::conj succeed. */
      inline const float & conj( const float & f ) {
        return f;
      }


      /** Helper struct for physical::real(). */
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

      /** Helper struct for physical::imag(). */
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

      /** helper for physical::erf. */
      template < typename T >
      inline std::complex<T> erf( const std::complex<T> & ct ) {
        if (ct.imag() != 0.0)
          throw exception(ComplexNotSupported);
        return detail::stdmath::erf(ct.real());
      }

      /** helper for physical::erfc. */
      template < typename T >
      inline std::complex<T> erfc( const std::complex<T> & ct ) {
        if (ct.imag() != 0.0)
          throw exception(ComplexNotSupported);
        return detail::stdmath::erfc(ct.real());
      }

      /** helper for physical::tgamma. */
      template < typename T >
      inline std::complex<T> tgamma( const std::complex<T> & ct ) {
        if (ct.imag() != 0.0)
          throw exception(ComplexNotSupported);
        return detail::stdmath::tgamma(ct.real());
      }

      /** helper for physical::floor. */
      template < typename T >
      inline std::complex<T> floor( const std::complex<T> & c ) {
        using std::floor;
        return std::complex<T>( floor(c.real()), floor(c.imag()) );
      }

      /** helper for physical::ceil. */
      template < typename T >
      inline std::complex<T> ceil( const std::complex<T> & c ) {
        using std::ceil;
        return std::complex<T>( ceil(c.real()), ceil(c.imag()) );
      }

      /** helper for physical::min.
       * specialization of min(complex,complex) that throws errors if we are
       * actually comparing complex quantities. */
      template < typename T >
      std::complex<T> min( const std::complex<T> & lhs,
                           const std::complex<T> & rhs ) {
        if (lhs.imag() != 0.0 || rhs.imag() != 0.0)
          throw exception(ComplexNotSupported);
        return std::min(lhs.real(), rhs.real());
      }

      /** helper for physical::max.
       * specialization of min(complex,complex) that throws errors if we are
       * actually comparing complex quantities. */
      template < typename T >
      std::complex<T> max( const std::complex<T> & lhs,
                           const std::complex<T> & rhs ) {
        if (lhs.imag() != 0.0 || rhs.imag() != 0.0)
          throw exception(ComplexNotSupported);
        return std::max(lhs.real(), rhs.real());
      }
    } /* namespace runtime::physical::detail. */
    /** \endcond */


    /** The power operator.
     * The templated ExpT parameter allows this function to instantiate the
     * correct pow<ExpT>(units_map&) function.
     * */
    template < typename T, typename ExpT >
    inline quantity<T> pow( const quantity<T> & q, const ExpT & exponent ) {
      using std::pow;
      using physical::pow;
      return quantity<T>( pow(q.coeff, exponent), pow(q.units,exponent) );
    }

    template < typename T >
    inline quantity<T> pow( const quantity<T> & q, const quantity<T> & e ) {
      if (!e.units.empty())
        throw exception(UnitsNotDimensionlessExp);
      return pow(q, e.coeff);
    }

    /** Sqrt function of physical::Quantity types. */
    template<class T>
    inline quantity<T> sqrt(const quantity<T> & q) {
      return quantity<T>(std::sqrt(q.coeff), pow(q.units,0.5));
    };

    template<class T>
    inline quantity<T> conj(const quantity<T> & q) {
      using detail::conj;
      using std::conj;
      return quantity<T>(conj(q.coeff), q.units);
    };

    template<class T>
    inline quantity<T> real(const quantity<T> & q) {
      return quantity<T>(detail::Real<T>()(q.coeff), q.units);
    };

    template<class T>
    inline quantity<T> imag(const quantity<T> & q) {
      return quantity<T>(detail::Imag<T>()(q.coeff), q.units);
    };

    template<class T>
    inline quantity<T> sin(const quantity<T> & q) {
      detail::w_angle<T>::check(q);
      return detail::stdmath::sin(q.coeff);
    };

    template<class T>
    inline quantity<T> cos(const quantity<T> & q) {
      detail::w_angle<T>::check(q);
      return detail::stdmath::cos(q.coeff);
    };

    template<class T>
    inline quantity<T> tan(const quantity<T> & q) {
      detail::w_angle<T>::check(q);
      return detail::stdmath::tan(q.coeff);
    };

    template<class T>
    inline quantity<T> asin(const quantity<T> & q) {
      detail::no_dims::check(q);
      return detail::stdmath::asin(q.coeff) * physical::unit::radian;
    };

    template<class T>
    inline quantity<T> acos(const quantity<T> & q) {
      detail::no_dims::check(q);
      return detail::stdmath::acos(q.coeff) * physical::unit::radian;
    };

    template<class T>
    inline quantity<T> atan(const quantity<T> & q) {
      detail::no_dims::check(q);
      return detail::stdmath::atan(q.coeff) * physical::unit::radian;
    };

    template<class T>
    inline quantity<T> sinh(const quantity<T> & q) {
      detail::w_angle<T>::check(q);
      return detail::stdmath::sinh(q.coeff);
    };

    template<class T>
    inline quantity<T> cosh(const quantity<T> & q) {
      detail::w_angle<T>::check(q);
      return detail::stdmath::cosh(q.coeff);
    };

    template<class T>
    inline quantity<T> tanh(const quantity<T> & q) {
      detail::w_angle<T>::check(q);
      return detail::stdmath::tanh(q.coeff);
    };

    template<class T>
    inline quantity<T> asinh(const quantity<T> & q) {
      detail::no_dims::check(q);
      return detail::stdmath::asinh(q.coeff) * physical::unit::radian;
    };

    template<class T>
    inline quantity<T> acosh(const quantity<T> & q) {
      detail::no_dims::check(q);
      return detail::stdmath::acosh(q.coeff) * physical::unit::radian;
    };

    template<class T>
    inline quantity<T> atanh(const quantity<T> & q) {
      detail::no_dims::check(q);
      return detail::stdmath::atanh(q.coeff) * physical::unit::radian;
    };

    template<class T>
    inline quantity<T> sinc(const quantity<T> & q) {
      detail::w_angle<T>::check(q);
      return q.coeff== T(0) ? T(1) : detail::stdmath::sin(q.coeff) / q.coeff;
    };

    template<class T>
    inline quantity<T> exp(const quantity<T> & q) {
      detail::w_angle<T>::check(q);
      return std::exp(q.coeff);
    };

    template<class T>
    inline quantity<T> erf(const quantity<T> & q) {
      detail::w_angle<T>::check(q);
      using detail::stdmath::erf;
      using detail::erf;
      return erf(q.coeff);
    };

    template<class T>
    inline quantity<T> erfc(const quantity<T> & q) {
      detail::w_angle<T>::check(q);
      using detail::stdmath::erfc;
      using detail::erfc;
      return erfc(q.coeff);
    };

    template<class T>
    inline quantity<T> log(const quantity<T> & q) {
      detail::no_dims::check(q);
      return std::log(q.coeff);
    };

    template<class T>
    inline quantity<T> log10(const quantity<T> & q) {
      detail::no_dims::check(q);
      return std::log10(q.coeff);
    };

    template<class T>
    inline quantity<T> tgamma(const quantity<T> & q) {
      detail::no_dims::check(q);
      using detail::stdmath::tgamma;
      using detail::tgamma;
      return tgamma(q.coeff);
    };

    /** Compute the floor of the quantity. */
    template<class T>
    inline quantity<T> floor(const quantity<T> & q) {
      using detail::floor;
      using std::floor;
      return quantity<T>(floor(q.coeff), q.units);
    };

    /** Compute the ceil of the quantity. */
    template<class T>
    inline quantity<T> ceil(const quantity<T> & q) {
      using std::ceil;
      using detail::ceil;
      return quantity<T>(ceil(q.coeff), q.units);
    };

    /** Compute the absolute value (magnitude) of the quantity. */
    template<class T>
    inline quantity<T> abs(const quantity<T> & q) {
        return quantity<T>(std::abs(q.coeff), q.units);
    };

    /** Compute the maximum value of two quantities--units must match. */
    template<class T>
    inline quantity<T> max( const quantity<T> & q0,
                            const quantity<T> & q1 ) {
      (void)q0.assertMatch( q1 );
      using detail::max;
      using std::max;
      return quantity<T>(max(q0.coeff, q1.coeff), q0.units);
    };

    /** Compute the minimum value of two quantities--units must match. */
    template<class T>
    inline quantity<T> min( const quantity<T> & q0,
                            const quantity<T> & q1 ) {
      (void)q0.assertMatch( q1 );
      using detail::min;
      using std::min;
      return quantity<T>(min(q0.coeff, q1.coeff), q0.units);
    };

    /** Helper function to make it really easy to define a new unit. */
    template<class T>
    inline quantity<T> new_unit( const std::string & name ) {
      return quantity<T>(T(1), units_pair(name, 1) );
    }

    /* ****   END QUANTITY OPERATORS **** */
  } /* namespace runtime::physical */
} /* namespace runtime */

#endif // physical_math_h
