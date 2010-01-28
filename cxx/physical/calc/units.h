#ifndef physical_calc_units_h
#define physical_calc_units_h

#include <physical/calc/symbol.h>

#include <complex>

namespace runtime {
  namespace physical {
    namespace calc {

      namespace detail {

        template < typename T >
        struct AddOtherSymbols {
          void operator() ( symbol::table & symbols ) {
          }
        };

        template < typename T >
        struct AddOtherSymbols< std::complex<T> > {
          void operator() ( symbol::table & symbols ) {
            using physical::Quantity;
            Quantity i = std::complex<T>(0.0,1.0);
            symbols["i"] = i;
          }
        };

      } /* namespace runtime::physical::calc::detail */

      /** Add all the physical units that were registered to the symbol table.
       * There are a few other things that are added depending on the type of
       * Quantity::coeff_type.  For example, if we are dealing with complex
       * values, we also add the symbol for 'i'.
       */
      static void addPhysicalUnits(symbol::table & symbols) {
        using physical::Quantity;

        for ( Quantity::registry_type::list_type::iterator i =
                 Quantity::registry().list.begin() ;
              i != Quantity::registry().list.end();
              ++i ) {
          symbols[i->first] = *(i->second);
        }

        /* add the "other" symbols last to make sure that these have precedence. */
        detail::AddOtherSymbols<Quantity::coeff_type>()(symbols);
      }

    } /* namespace runtime::physical::calc */
  } /* namespace runtime::physical */
} /* namespace runtime */

#endif // physical_calc_units_h
