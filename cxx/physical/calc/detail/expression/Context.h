// $Id: expression.h 48 2009-09-05 08:07:10Z tb $
/** \file expression.h Implements an example calculator class group. */

#ifndef physical_calc_detail_expression_Context_h
#define physical_calc_detail_expression_Context_h

#include <physical/calc/detail/expression/Node.h>

#include <map>
#include <vector>
#include <stdexcept>
#include <string>

namespace physical {
  namespace calc {
    namespace detail {
      namespace expression {

        /** Calculator context used to save the parsed expressions. This context is
         * passed along to the physical::Driver class and fill during parsing via bison
         * actions. */
        class Context {
        public:

          /// type of the variable storage
          typedef std::map<std::string, double> variablemap_type;

          /// variable storage. maps variable string to doubles
          variablemap_type variables;

          /// array of unassigned expressions found by the parser. these are then
          /// outputted to the user.
          std::vector<Node*> expressions;

          /// free the saved expression trees
          ~Context() {
            clearExpressions();
          }

          /// free all saved expression trees
          void clearExpressions() {
            for(unsigned int i = 0; i < expressions.size(); ++i) {
                delete expressions[i];
            }
            expressions.clear();
          }

          /// check if the given variable name exists in the storage
          bool existsVariable(const std::string &varname) const {
            return variables.find(varname) != variables.end();
          }
          
          /// return the given variable from the storage. throws an exception if it
          /// does not exist.
          double getVariable(const std::string &varname) const {
            variablemap_type::const_iterator vi = variables.find(varname);
            if (vi == variables.end())
              throw(std::runtime_error("Unknown variable."));
            else
              return vi->second;
          }
        };

      } /* namespace physical::calc::detail::expression */
    } /* namespace physical::calc::detail */
  } /* namespace physical::calc */
} /* namespace physical */

#endif // physical_calc_detail_expression_Context_h
