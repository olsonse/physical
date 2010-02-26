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
        /* these casts were necessary to appease the PGI compiler.  Perhaps this
         * is caused by ADL not working so well with PGI. */

        #define physical_F1(f) \
          static_cast<symbol::func_qargs1>(physical::f <Quantity::coeff_type>)

        #define physical_F2(f) \
          static_cast<symbol::func_qargs2>(physical::f <Quantity::coeff_type>)

        #define physical_SF1(f) \
          static_cast<symbol::func_str_args1>(physical::f<Quantity::coeff_type>)

        /** Several single argument math functions. */
        symbols["conj"]  = physical_F1( conj   );
        symbols["real"]  = physical_F1( real   );
        symbols["imag"]  = physical_F1( imag   );
        symbols["sin"]   = physical_F1( sin    );
        symbols["cos"]   = physical_F1( cos    );
        symbols["tan"]   = physical_F1( tan    );
        symbols["asin"]  = physical_F1( asin   );
        symbols["acos"]  = physical_F1( acos   );
        symbols["atan"]  = physical_F1( atan   );
        symbols["sinh"]  = physical_F1( sinh   );
        symbols["cosh"]  = physical_F1( cosh   );
        symbols["tanh"]  = physical_F1( tanh   );
        symbols["asinh"] = physical_F1( asinh  );
        symbols["acosh"] = physical_F1( acosh  );
        symbols["atanh"] = physical_F1( atanh  );
        symbols["sinc"]  = physical_F1( sinc   );
        symbols["exp"]   = physical_F1( exp    );
        symbols["erf"]   = physical_F1( erf    );
        symbols["erfc"]  = physical_F1( erfc   );
        symbols["ln"]    = physical_F1( log    );
        symbols["log10"] = physical_F1( log10  );
        symbols["sqrt"]  = physical_F1( sqrt   );
        symbols["gamma"] = physical_F1( tgamma );
        symbols["floor"] = physical_F1( floor  );
        symbols["ceil"]  = physical_F1( ceil   );
        symbols["abs"]   = physical_F1( abs    );

        /* two argument functions */
        symbols["min"]   = physical_F2( min );
        symbols["max"]   = physical_F2( max );

        /* single argument string functions */
        symbols["new_unit"]=physical_SF1(new_unit);

        #undef physical_F1
        #undef physical_F2
        #undef physical_SF1
      }
    }
  }
}

#endif // physical_calc_math_h
