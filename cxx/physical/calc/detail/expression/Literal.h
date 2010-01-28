// $Id: expression.h 48 2009-09-05 08:07:10Z tb $
/** \file expression.h Implements an example calculator class group. */

#ifndef physical_calc_detail_expression_Literal_h
#define physical_calc_detail_expression_Literal_h

#include <physical/calc/detail/expression/Node.h>

#include <ostream>

namespace runtime {
  namespace physical {
    namespace calc {
      namespace detail {
        namespace expression {

          /** Calculation node always returning a constant value. */
          class Literal : public Node {
            /// the constant value returned
            double value;
            
          public:
            /// construct a constant calculation node from a value
            explicit Literal(const double & value) : Node(), value(value) { }

            virtual Quantity evaluate() const {
              return Quantity(value);
            }

            virtual std::ostream & print(std::ostream &os, unsigned int depth) const {
              os << indent(depth) << value << std::endl;
              return os;
            }
          };

        } /* namespace physical::calc::detail::expression */
      } /* namespace physical::calc::detail */
    } /* namespace physical::calc */
  } /* namespace runtime::physical */
} /* namespace runtime */

#endif // physical_calc_detail_expression_Literal_h
