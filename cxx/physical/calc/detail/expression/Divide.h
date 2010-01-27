// $Id: expression.h 48 2009-09-05 08:07:10Z tb $
/** \file expression.h Implements an example calculator class group. */

#ifndef physical_calc_detail_expression_Divide_h
#define physical_calc_detail_expression_Divide_h

#include <physical/calc/detail/expression/Node.h>

#include <ostream>

namespace physical {
  namespace calc {
    namespace detail {
      namespace expression {

        /** Calculation node dividing two operand nodes. */
        class Divide : public Node {
          /// left calculation operand
          Node* left;

          /// right calculation operand
          Node* right;
          
        public:
          explicit Divide(Node* _left, Node* _right)
            : Node(), left(_left), right(_right) { }

          virtual ~Divide() {
            delete left;
            delete right;
          }

          virtual Quantity evaluate() const {
            return left->evaluate() / right->evaluate();
          }

          virtual void print(std::ostream &os, unsigned int depth) const {
            os << indent(depth) << "/ divide" << std::endl;
            left->print(os, depth+1);
            right->print(os, depth+1);
          }
        };

      } /* namespace physical::calc::detail::expression */
    } /* namespace physical::calc::detail */
  } /* namespace physical::calc */
} /* namespace physical */

#endif // physical_calc_detail_expression_Divide_h
