// $Id: expression.h 48 2009-09-05 08:07:10Z tb $
/** \file expression.h Implements an example calculator class group. */

#ifndef physical_calc_detail_expression_Constant_h
#define physical_calc_detail_expression_Constant_h

#include <physical/calc/detail/expression/Node.h>

#include <ostream>

namespace physical {
  namespace calc {
    namespace detail {
      namespace expression {

        /** Calculation node always returning a constant value. */
        class Constant : public Node {
          /// the constant value returned
          Quantity value;
          
        public:
          /// construct a constant calculation node from a value
          explicit Constant(const Quantity & value) : Node(), value(value) { }

          virtual Quantity evaluate() const {
            return value;
          }

          virtual void print(std::ostream &os, unsigned int depth) const {
            os << indent(depth) << value << std::endl;
          }
        };

      } /* namespace physical::calc::detail::expression */
    } /* namespace physical::calc::detail */
  } /* namespace physical::calc */
} /* namespace physical */

#endif // physical_calc_detail_expression_Constant_h
