// $Id: expression.h 48 2009-09-05 08:07:10Z tb $
/** \file expression.h Implements an example calculator class group. */

#ifndef physical_calc_detail_expression_Negate_h
#define physical_calc_detail_expression_Negate_h

#include <physical/calc/detail/expression/Node.h>

#include <ostream>

namespace runtime {
  namespace physical {
    namespace calc {
      namespace detail {
        namespace expression {

          /** Calculation node negating the value of the operand subtree. */
          class Negate : public Node {
            /// calculation subtree
            Node* node;

          public:
            explicit Negate(Node* _node)
              : Node(), node(_node) { }

            virtual ~Negate() {
              delete node;
            }

            virtual Quantity evaluate() const {
              return - node->evaluate();
            }

            virtual std::ostream & print( std::ostream &os, unsigned int depth ) const {
              os << indent(depth) << "- negate" << std::endl;
              node->print(os, depth+1);
              return os;
            }
          };

        } /* namespace physical::calc::detail::expression */
      } /* namespace physical::calc::detail */
    } /* namespace physical::calc */
  } /* namespace runtime::physical */
} /* namespace runtime */

#endif // physical_calc_detail_expression_Negate_h
