// $Id: expression.h 48 2009-09-05 08:07:10Z tb $
/** \file expression.h Implements an example calculator class group. */

#ifndef physical_calc_detail_expression_Assign_h
#define physical_calc_detail_expression_Assign_h

#include <physical/calc/symbol.h>
#include <physical/calc/detail/expression/Node.h>

#include <vector>
#include <ostream>
#include <string>

namespace runtime {
  namespace physical {
    namespace calc {
      namespace detail {
        namespace expression {

          /** Calculation node raising one operand to the power of the second. */
          class Assign : public Node {
            /** Reference to the symbol table. */
            symbol::table & symbols;

            /// left calculation operand
            std::string name;

            /// right calculation operand
            Node * value;
            
          public:
            explicit Assign( symbol::table & symbols,
                             const std::string & name, Node * value )
              : Node(), symbols(symbols), name(name), value(value) { }

            virtual ~Assign() {
              delete value;
            }

            virtual Quantity evaluate() const {
              symbol::table::iterator it = symbols.find(name);
              if (it != symbols.end() && (*it).second.type == symbol::CONSTANT)
                throw symbol_immutable(name);

              return (symbols[name] =
                        symbol(value->evaluate(), symbol::VARIABLE)
                     ).evaluate();
            }

            virtual std::ostream & print(std::ostream &os, unsigned int depth) const {
              os << indent(depth) << "= Assign(" << '\'' << name << "')" << std::endl;
              value->print(os, depth+1);
              return os;
            }
          };

        } /* namespace physical::calc::detail::expression */
      } /* namespace physical::calc::detail */
    } /* namespace physical::calc */
  } /* namespace runtime::physical */
} /* namespace runtime */

#endif // physical_calc_detail_expression_Assign_h
