// $Id: expression.h 48 2009-09-05 08:07:10Z tb $
/** \file expression.h Implements an example calculator class group. */

#ifndef physical_calc_detail_expression_Power_h
#define physical_calc_detail_expression_Power_h

#include <physical/calc/detail/expression/Node.h>
#include <physical/math.h>

#include <ostream>
#include <cmath>

namespace runtime {
  namespace physical {
    namespace calc {
      namespace detail {
        namespace expression {

          /** Calculation node raising one operand to the power of the second. */
          class Power : public Node {
            /// left calculation operand
            Node* left;

            /// right calculation operand
            Node* right;
            
          public:
            explicit Power(Node* _left, Node* _right)
              : Node(), left(_left), right(_right) { }

            virtual ~Power() {
              delete left;
              delete right;
            }

            virtual Quantity evaluate() const {
              using std::pow;
              return pow(left->evaluate(), right->evaluate());
            }

            virtual std::ostream & print(std::ostream &os, unsigned int depth) const {
              os << indent(depth) << "^ power" << std::endl;
              left->print(os, depth+1);
              right->print(os, depth+1);
              return os;
            }
          };

        } /* namespace physical::calc::detail::expression */
      } /* namespace physical::calc::detail */
    } /* namespace physical::calc */
  } /* namespace runtime::physical */
} /* namespace runtime */

#endif // physical_calc_detail_expression_Power_h
