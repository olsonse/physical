// $Id: expression.h 48 2009-09-05 08:07:10Z tb $
/** \file expression.h Implements an example calculator class group. */

#ifndef physical_calc_detail_expression_Add_h
#define physical_calc_detail_expression_Add_h

#include <physical/calc/detail/expression/Node.h>

#include <ostream>

namespace physical {
  namespace calc {
    namespace detail {
      namespace expression {

        /** Calculation node adding two operand nodes. */
        class Add : public Node {
          /// left calculation operand
          Node* left;

          /// right calculation operand
          Node* right;
          
        public:
          explicit Add(Node* _left, Node* _right)
            : Node(), left(_left), right(_right) { }

          virtual ~Add() {
            delete left;
            delete right;
          }

          virtual Quantity evaluate() const {
            return left->evaluate() + right->evaluate();
          }

          virtual void print(std::ostream &os, unsigned int depth) const {
            os << indent(depth) << "+ add" << std::endl;
            left->print(os, depth+1);
            right->print(os, depth+1);
          }
        };

      } /* namespace physical::calc::detail::expression */
    } /* namespace physical::calc::detail */
  } /* namespace physical::calc */
} /* namespace physical */

#endif // physical_calc_detail_expression_Add_h
