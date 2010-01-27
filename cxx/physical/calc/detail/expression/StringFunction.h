// $Id: expression.h 48 2009-09-05 08:07:10Z tb $
/** \file expression.h Implements an example calculator class group. */

#ifndef physical_calc_detail_expression_StringFunction_h
#define physical_calc_detail_expression_StringFunction_h

#include <physical/calc/detail/expression/Node.h>

#include <vector>
#include <ostream>
#include <string>

namespace physical {
  namespace calc {
    namespace detail {
      namespace expression {

        /** Calculation node raising one operand to the power of the second. */
        class StringFunction : public Node {
          /* TYPEDEFS */
          typedef std::vector< std::string > ArgList;

          /// left calculation operand
          std::string funcname;

          /// right calculation operand
          ArgList args;
          
        public:
          explicit StringFunction( const std::string & funcname,
                                   const ArgList & args )
            : Node(), funcname(funcname), args(args) { }

          virtual ~StringFunction() {}

          virtual Quantity evaluate() const {
            symbol::table::iterator it = symbols.find(funcname);
            if (it == symbols.end())
              throw undefined_function(funcname);
            else if (it->second.type != symbol::FUNCTION)
              throw undefined_function(funcname);

            int args_accepted = it->second.numberOfArguments();
            if ( args_accepted >= 0 && args_accepted != args.size() ) {
              std::ostringstream outs;
              outs << "incorrect number of arguments "
                      "(" << args.size() << ")"
                      " for function '" << funcname << "'"
                      " which accepts " << args_accepted << " arguments";
              throw symbol_error( outs.str() );
            }

            return it->second.evaluate( args );
          }


          virtual void print(std::ostream &os, unsigned int depth) const {
            os << indent(depth) << funcname << std::endl;

            const ArgList::const_iterator end = args.end();
            for ( ArgList::const_iterator i = args.begin(); i != end; ++i ) {
              char quo = '\'';
              if ( i->find("'") != std::string::npos )
                quo = '"';

              os << indent(depth+1) << quo << (*i) << quo << std::endl;
            }
          }
        };

      } /* namespace physical::calc::detail::expression */
    } /* namespace physical::calc::detail */
  } /* namespace physical::calc */
} /* namespace physical */

#endif // physical_calc_detail_expression_StringFunction_h
