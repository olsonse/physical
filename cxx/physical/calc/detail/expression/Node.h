// $Id: expression.h 48 2009-09-05 08:07:10Z tb $
/** \file expression.h Implements an example calculator class group. */

#ifndef physical_calc_detail_expression_Node_h
#define physical_calc_detail_expression_Node_h

#include <physical/runtime.h>

#include <string>
#include <ostream>

namespace runtime {
  namespace physical {
    namespace calc {
      namespace detail {
        namespace expression {

          /** Node is the abstract base class for calculation nodes. From it the
           * different nullary, unary and binary nodes are derived. */
          class Node {
          public:
            /// required for virtual functions. in the derived classes the operands are
            /// deleted.
            virtual ~Node() { }

            /// evaluate the complete calculation tree and return the floating point
            /// result value
            virtual Quantity evaluate() const = 0;

            /// output the calculation tree to the given stream. tries to format the
            /// output to make tree levels visible.
            virtual std::ostream & print(std::ostream &os, unsigned int depth=0) const = 0;

            /// helper function for print() which makes the indention string
            static inline std::string indent(unsigned int d) {
              return std::string(d * 2, ' ');
            }
          };

        } /* namespace physical::calc::detail::expression */
      } /* namespace physical::calc::detail */
    } /* namespace physical::calc */
  } /* namespace runtime::physical */
} /* namespace runtime */

#endif // physical_calc_detail_expression_Node_h
