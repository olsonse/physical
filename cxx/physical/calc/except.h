/** \file
 * Parsing exceptions used in runtime::physical::calc::Driver.
 */

#ifndef  physical_calc_except_h
#define  physical_calc_except_h

#include <physical/except.h>

#include <string>

namespace runtime {
  namespace physical {
    namespace calc {

      struct no_result : physical::exception {
        typedef physical::exception super;
        no_result( const std::string & err = "" ) : super(err) { }
      };

      struct syntax_error : physical::exception {
        typedef physical::exception super;
        syntax_error( const std::string & msg = "" ) : super(msg) {}
      };

    } /* namespace calc */
  } /* namespace runtime::physical */
} /* namespace runtime */

#endif // physical_calc_except_h
