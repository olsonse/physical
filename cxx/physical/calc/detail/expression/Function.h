// $Id: expression.h 48 2009-09-05 08:07:10Z tb $
/** \file expression.h Implements an example calculator class group. */

#ifndef physical_calc_detail_expression_Function_h
#define physical_calc_detail_expression_Function_h

#include <physical/calc/symbol.h>
#include <physical/calc/detail/expression/Node.h>

#include <vector>
#include <ostream>
#include <string>
#include <sstream>

namespace runtime {
  namespace physical {
    namespace calc {
      namespace detail {
        namespace expression {

          /** Calculation node raising one operand to the power of the second. */
          class Function : public Node {
            /* TYPEDEFS */
            typedef std::vector< Node * > ArgList;

            /** Reference to the symbol table. */
            const symbol::table & symbols;

            /// left calculation operand
            std::string funcname;

            /// right calculation operand
            ArgList args;
            
          public:
            explicit Function( const symbol::table & symbols,
                               const std::string & funcname )
              : Node(), symbols(symbols), funcname(funcname), args() { }

            explicit Function( const symbol::table & symbols,
                               const std::string & funcname,
                               const ArgList & args )
              : Node(), symbols(symbols), funcname(funcname), args(args) { }

            virtual ~Function() {
              while ( !args.empty() ) {
                delete args.back();
                args.pop_back();
              }
            }

            virtual Quantity evaluate() const {
              symbol::table::const_iterator it = symbols.find(funcname);
              if (it == symbols.end())
                throw undefined_function(funcname);
              else if (it->second.type != symbol::FUNCTION)
                throw undefined_function(funcname);

              int args_accepted = it->second.numberOfArguments();
              if ( args_accepted >= 0 &&
                   static_cast<unsigned int>(args_accepted) != args.size() ) {
                std::ostringstream outs;
                outs << "incorrect number of arguments "
                        "(" << args.size() << ")"
                        " for function '" << funcname << "'"
                        " which accepts " << args_accepted << " arguments";
                throw symbol_error( outs.str() );
              }

              /* we first need to build a list of the evaluation of each of the
               * arguements. */
              std::vector<Quantity> eargs;
              {
                const ArgList::const_iterator end = args.end();
                for ( ArgList::const_iterator i = args.begin(); i != end; ++i )
                  eargs.push_back( (*i)->evaluate() );
              }

              return it->second.evaluate( eargs );
            }

            virtual std::ostream & print(std::ostream &os, unsigned int depth) const {
              os << indent(depth) << funcname << "()" << std::endl;
              const ArgList::const_iterator end = args.end();
              for ( ArgList::const_iterator i = args.begin(); i != end; ++i ) {
                (*i)->print(os, depth+1);
              }
              return os;
            }
          };

        } /* namespace physical::calc::detail::expression */
      } /* namespace physical::calc::detail */
    } /* namespace physical::calc */
  } /* namespace runtime::physical */
} /* namespace runtime */

#endif // physical_calc_detail_expression_Function_h
