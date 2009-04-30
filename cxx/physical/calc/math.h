#ifndef PHYSICAL_CALC_MATH_H
#define PHYSICAL_CALC_MATH_H

#include <physical/quantity.h>
#include <physical/math.h>
#include <physical/calc/symbol.h>

namespace runtime { namespace physical {
    namespace calc {
        static void addMathLib(symbol::table & symbols) {
            symbols["conj"]  = physical::math::conj  <Quantity::coeff_type>;
            symbols["real"]  = physical::math::real  <Quantity::coeff_type>;
            symbols["imag"]  = physical::math::imag  <Quantity::coeff_type>;
            symbols["sin"]   = physical::math::sin   <Quantity::coeff_type>;
            symbols["cos"]   = physical::math::cos   <Quantity::coeff_type>;
            symbols["tan"]   = physical::math::tan   <Quantity::coeff_type>;
            symbols["asin"]  = physical::math::asin  <Quantity::coeff_type>;
            symbols["acos"]  = physical::math::acos  <Quantity::coeff_type>;
            symbols["atan"]  = physical::math::atan  <Quantity::coeff_type>;
            symbols["sinh"]  = physical::math::sinh  <Quantity::coeff_type>;
            symbols["cosh"]  = physical::math::cosh  <Quantity::coeff_type>;
            symbols["tanh"]  = physical::math::tanh  <Quantity::coeff_type>;
            symbols["asinh"] = physical::math::asinh <Quantity::coeff_type>;
            symbols["acosh"] = physical::math::acosh <Quantity::coeff_type>;
            symbols["atanh"] = physical::math::atanh <Quantity::coeff_type>;
            symbols["sinc"]  = physical::math::sinc  <Quantity::coeff_type>;
            symbols["exp"]   = physical::math::exp   <Quantity::coeff_type>;
            symbols["erf"]   = physical::math::erf   <Quantity::coeff_type>;
            symbols["erfc"]  = physical::math::erfc  <Quantity::coeff_type>;
            symbols["ln"]    = physical::math::log   <Quantity::coeff_type>;
            symbols["log10"] = physical::math::log10 <Quantity::coeff_type>;
            symbols["sqrt"]  = physical::math::sqrt  <Quantity::coeff_type>;
            symbols["gamma"] = physical::math::tgamma<Quantity::coeff_type>;
            symbols["floor"] = physical::math::floor <Quantity::coeff_type>;
            symbols["ceil"]  = physical::math::ceil  <Quantity::coeff_type>;
            symbols["abs"]   = physical::math::abs   <Quantity::coeff_type>;
        }
    }
}}

#endif // PHYSICAL_CALC_MATH_H
