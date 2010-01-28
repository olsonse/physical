// $Id: driver.cc 39 2008-08-03 10:07:15Z tb $
/** \file driver.cc Implementation of the physical::Driver class. */

#include <physical/calc/Driver.h>
#include <physical/calc/except.h>
#include <physical/calc/detail/Scanner.h>
#include <physical/calc/units.h>
#include <physical/calc/math.h>

#include <fstream>
#include <sstream>
#include <string>

namespace runtime {
  namespace physical {
    namespace calc {

      Driver::Driver()
        : trace_scanning(false),
          trace_parsing(false),
          lexer(NULL) { }

      bool Driver::parse( std::istream & in, const std::string & sname ) {
        streamname = sname;

        detail::Scanner scanner(&in);
        scanner.set_debug(trace_scanning);
        this->lexer = &scanner;

        detail::Parser parser(*this);
        parser.set_debug_level(trace_parsing);
        bool has_result = (parser.parse() == 0);

        /* Now let's do something about all the errors that occurred:  throw
         * syntax errors! */
        if ( errors.size() > 0u ) {
          /* build error string first */
          std::ostringstream ostr;
          char sep = '\0';
          for ( unsigned int i = 0u; i < errors.size(); ++i ) {
            ostr << errors[i].first << ": " << errors[i].second << sep;
            sep = '\n';
          }

          /* clean up the errors */
          errors.clear();

          throw syntax_error( ostr.str() );
        }

        return has_result;
      }

      bool Driver::parse( const std::string & input,
                          const std::string & sname ) {
        std::istringstream sin(input);
        try {
          return parse( sin, sname );
        } catch ( const syntax_error & e ) {
          throw syntax_error( input + '\n' + e.what() );
        }
      }

      Quantity Driver::eval( std::istream & in,
                             const std::string & sname ) {
        /* First get a 'pointer' to the last valid expression since we will only
         * evaluate recent entries to the expression tree vector. */
        unsigned int prev_sz = expressions.size();
        bool result = parse( in, sname );

        if (!result) {
          throw no_result();
        }

        Quantity retval;

        const EIter begin = expressions.begin() + prev_sz;
        const EIter end = expressions.end();
        for ( EIter i = begin; i != end; ++i ) {
          retval = (*i)->evaluate();
        }

        /* and now we will remove all the entries from the expression tree
         * vector that we just added by this parse. */
        expressions.erase( begin, end );

        return retval;
      }

      Quantity::coeff_type Driver::eval( std::istream & in,
                                         const Quantity & u_out,
                                         const std::string & sname ) {
        return eval( in, sname ).assertMatch(u_out).coeff / u_out.coeff;
      }

      Quantity Driver::eval( const std::string & input,
                             const std::string & sname ) {
        std::istringstream sin(input);
        try {
          return eval( sin, sname );
        } catch ( const syntax_error & e ) {
          throw syntax_error( input + '\n' + e.what() );
        }
      }

      Quantity::coeff_type Driver::eval( const std::string & input,
                                         const Quantity & u_out,
                                         const std::string & sname ) {
        try {
          return eval( input, sname ).assertMatch(u_out).coeff / u_out.coeff;
        } catch ( const syntax_error & e ) {
          throw syntax_error( input + '\n' + e.what() );
        }
      }

      void Driver::exec( std::istream & in, const std::string & sname ) {
        try {
          (void)eval( in, sname );
        } catch ( const no_result & e ) {
          /* ignore lack of results. */
        }
      }

      void Driver::exec( const std::string & input, const std::string & sname ) {
        std::istringstream sin(input);
        try {
          exec( sin, sname );
        } catch ( const syntax_error & e ) {
          throw syntax_error( input + '\n' + e.what() );
        }
      }

      void Driver::error( const detail::location& l, const std::string& m ) {
        errors.push_back( std::make_pair(l,m) );
      }

      void Driver::dump( std::ostream & out,
                         const enum symbol::TYPE & typ
                            /* = symbol::UNDEFINED */ ) const {
        // Dump the entire symbol table. 
        symbol::table::const_iterator i = symbols.begin();
        symbol::table::const_iterator end = symbols.end();

        if ( typ == symbol::UNDEFINED ) {
          for ( ; i != end; ++i )
            out << i->first << "\t=  " << i->second << '\n';

        } else {
          for ( ; i != end; ++i )
            if (i->second.type == typ)
              out << i->first << "\t=  " << i->second << '\n';
        }
      }

      void Driver::addPhysicalUnits() {
        physical::calc::addPhysicalUnits(symbols);
      }

      void Driver::addMathLib() {
        physical::calc::addMathLib(symbols);
      }

      Driver::~Driver() {
        clearExpressions();
      }


      Driver & Driver::instance() {
        static Driver * driver = new Driver();
        return *driver;
      }

    }/* namespace physical::calc */
  }/* namespace runtime::physical */
}/* namespace runtime */
