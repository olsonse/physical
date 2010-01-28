// $Id: expression.h 48 2009-09-05 08:07:10Z tb $
/** \file expression.h Implements an example calculator class group. */

#ifndef physical_calc_detail_expression_VariableLookup_h
#define physical_calc_detail_expression_VariableLookup_h

#include <physical/calc/symbol.h>
#include <physical/calc/detail/expression/Node.h>

#include <vector>
#include <ostream>
#include <string>
#include <stdexcept>

namespace runtime {
  namespace physical {
    namespace calc {
      namespace detail {
        namespace expression {

          /** Calculation node raising one operand to the power of the second. */
          class VariableLookup : public Node {
            /** Reference to the symbol table. */
            const symbol::table & symbols;

            /// left calculation operand
            std::string name;

          public:
            explicit VariableLookup( const symbol::table & symbols,
                                     const std::string & name )
              : Node(), symbols(symbols), name(name) { }

            virtual ~VariableLookup() { }

            virtual Quantity evaluate() const {
              symbol::table::const_iterator it = symbols.find(name);
              if ( it == symbols.end() )
                throw undefined_variable(name);
              else
                return it->second.evaluate();
            }/* evaluate() */

            virtual std::ostream & print(std::ostream &os, unsigned int depth) const {
              os << indent(depth) << "variable(" << '\'' << name << "')" << std::endl;
              return os;
            }
          };

        } /* namespace physical::calc::detail::expression */
      } /* namespace physical::calc::detail */
    } /* namespace physical::calc */
  } /* namespace runtime::physical */
} /* namespace runtime */

#endif // physical_calc_detail_expression_VariableLookup_h
