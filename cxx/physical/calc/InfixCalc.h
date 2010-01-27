
#ifndef physical_calc_InfixCalc_h
#define physical_calc_InfixCalc_h

#include <physical/runtime.h>
#include <physical/calc/symbol.h>
#include <physical/calc/BaseCalc.h>

#include <ostream>
#include <string>
#include <vector>

namespace runtime {
  namespace physical {
    namespace calc {

      struct InfixCalc : BaseCalc<InfixCalc> {
        /* TYPEDEFS */
        typedef BaseCalc<InfixCalc>                 base_calc;


        /* MEMBER STORAGE */
        Quantity                                    result;
        bool                                        result_set;


        /* MEMBER FUNCTIONS */
      public:
        InfixCalc() : base_calc(), result(), result_set(false) { }

        void dump( std::ostream & out,
                   const enum symbol::TYPE & typ = symbol::UNDEFINED) const {
          // Dump the entire symbol table. 
          symbol::table::const_iterator i = symbols.begin();
          symbol::table::const_iterator end = symbols.end();

          if ( typ == symbol::UNDEFINED ) {
            for ( ; i != end; ++i )
              out << i->first << "\t=  " << i->second << '\n';

          } else {
            for ( ; i != end; ++i )
              if (i->second.type == typ)
                out << i->first << "\t=  " << i->second << '\n';
          }
        }

        const Quantity & result() const { return resultRef; }
        const bool & result_set() const { return result_setRef; }
        void reset_result_set() { result_setRef = false; }
      };

    } /* namespace runtime::physical::calc */
  } /* namespace runtime::physical */
} /* namespace runtime */

#endif // physical_calc_InfixCalc_h
