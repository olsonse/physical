#ifndef physical_calc_math_h
#define physical_calc_math_h

#include <physical/runtime.h>
#include <physical/math.h>
#include <physical/calc/symbol.h>

namespace runtime {
  namespace physical {
    namespace calc {

      /** Add all the math functions for physical::Quantity types that we know
       * of right now.
       *
       * @param symbols
       *    The symbol table to which to add the math function symbols.
       */
      static void addMathLib( symbol::table & symbols ) {
        /** Several single argument math functions. */
        symbols["conj"]  = physical::conj  <Quantity::coeff_type>;
        symbols["real"]  = physical::real  <Quantity::coeff_type>;
        symbols["imag"]  = physical::imag  <Quantity::coeff_type>;
        symbols["sin"]   = physical::sin   <Quantity::coeff_type>;
        symbols["cos"]   = physical::cos   <Quantity::coeff_type>;
        symbols["tan"]   = physical::tan   <Quantity::coeff_type>;
        symbols["asin"]  = physical::asin  <Quantity::coeff_type>;
        symbols["acos"]  = physical::acos  <Quantity::coeff_type>;
        symbols["atan"]  = physical::atan  <Quantity::coeff_type>;
        symbols["sinh"]  = physical::sinh  <Quantity::coeff_type>;
        symbols["cosh"]  = physical::cosh  <Quantity::coeff_type>;
        symbols["tanh"]  = physical::tanh  <Quantity::coeff_type>;
        symbols["asinh"] = physical::asinh <Quantity::coeff_type>;
        symbols["acosh"] = physical::acosh <Quantity::coeff_type>;
        symbols["atanh"] = physical::atanh <Quantity::coeff_type>;
        symbols["sinc"]  = physical::sinc  <Quantity::coeff_type>;
        symbols["exp"]   = physical::exp   <Quantity::coeff_type>;
        symbols["erf"]   = physical::erf   <Quantity::coeff_type>;
        symbols["erfc"]  = physical::erfc  <Quantity::coeff_type>;
        symbols["ln"]    = physical::log   <Quantity::coeff_type>;
        symbols["log10"] = physical::log10 <Quantity::coeff_type>;
        symbols["sqrt"]  = physical::sqrt  <Quantity::coeff_type>;
        symbols["gamma"] = physical::tgamma<Quantity::coeff_type>;
        symbols["floor"] = physical::floor <Quantity::coeff_type>;
        symbols["ceil"]  = physical::ceil  <Quantity::coeff_type>;
        symbols["abs"]   = physical::abs   <Quantity::coeff_type>;

        /* two argument functions */
        symbols["min"]   = physical::min   <Quantity::coeff_type>;
        symbols["max"]   = physical::max   <Quantity::coeff_type>;

        /* single argument string functions */
        symbols["new_unit"]=physical::new_unit<Quantity::coeff_type>;
      }
    }
  }
}

#endif // physical_calc_math_h
