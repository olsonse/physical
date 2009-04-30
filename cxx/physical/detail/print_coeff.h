
#ifndef physical_detail_print_coeff_h
#define physical_detail_print_coeff_h

#include <complex>
#include <string>

namespace runtime {
  namespace physical {
    namespace detail {
      /** The possible printing modes. */
      enum PRINT_TYPE {
          /** Pretty formatting similar to GNU units. */
          PRETTY_PRINT,
          /** Mathematically correct. */
          MATH_PRINT,
          /** Format for latex math mode. This format uses fractional
           * format. */
          LATEX_PRINT,
          /** Format for latex math mode. This format is for single line
           * fractions. */
          LATEX_ONELINE_PRINT,
          /** Unpleasant formatting that demonstrates the units structure. */
          UGLY_PRINT
      };

      template < typename C, enum PRINT_TYPE >
      struct print_coeff {
        std::string operator() ( const C & coeff ) {
          std::ostringstream out;
          out << coeff;
          return out.str();
        }
      };

      template < typename C, enum PRINT_TYPE pT >
      struct print_coeff< std::complex<C>, pT > {
        std::string operator() ( const std::complex<C> & coeff ) {
          std::ostringstream out;
          if (coeff.imag() != 0.0)
            out << '('
                << print_coeff<C,pT>()(coeff.real())
                << " + i*"
                << print_coeff<C,pT>()(coeff.imag())
                << ')';
          else
            out << print_coeff<C,pT>()(coeff.real());
          return out.str();
        }
      };

      template < typename C >
      struct print_coeff< std::complex<C>, PRETTY_PRINT > {
        std::string operator() ( const std::complex<C> & coeff ) {
          std::ostringstream out;
          out << coeff.real();
          if (coeff.imag() != 0.0)
            out << " + i" << coeff.imag();
          return out.str();
        }
      };

      template < typename C >
      struct print_coeff< C, LATEX_PRINT> {
        std::string operator() ( const C & coeff ) {
          std::ostringstream out;
          int decade = int(std::log10(coeff));
          C sig_figs = coeff / std::pow(static_cast<C>(10),decade);

          out << sig_figs;
          if (decade > 1)
              out << " \\times 10^{" << decade << "} ";
          return out.str();
        }
      };

      template < typename C >
      struct print_coeff< std::complex<C>, LATEX_PRINT > {
        std::string operator() ( const std::complex<C> & coeff ) {
          std::ostringstream out;

          if (coeff.real() == 0.0 && coeff.imag() == 0.0)
            return "0";

          if (coeff.real() != 0.0) {
            if (coeff.imag() != 0.0)
              out << '(';

            out << print_coeff<C,LATEX_PRINT>()(coeff.real());

            if (coeff.imag() != 0.0)
              out << " + ";
          }

          if (coeff.imag() != 0.0) {
            out << "i" << print_coeff<C,LATEX_PRINT>()(coeff.imag());
            if (coeff.real() != 0.0)
              out << ')';
          }

          return out.str();
        }
      };
    }
  }
}

#endif // physical_detail_print_coeff_h
