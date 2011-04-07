/** \file
 * Symbol class for all symbols (constants, variables, functions) used in the
 * runtime::physical::calc::Driver calculator class.
 */

#ifndef physical_calc_symbol_h
#define physical_calc_symbol_h

#include <boost/regex.hpp>
//#include <regex> // have to wait until the new std:: stl

#include <string>

#include <physical/runtime.h>

namespace runtime {
  namespace physical {
    namespace calc {

      /* *** BEGIN SYMBOL EXCEPTIONS *** */
      /** The generic symbol error--inherits from physical::exception. */
      struct symbol_error : physical::exception {
        typedef physical::exception super;
        symbol_error(const std::string & err) : super(err) {}
      };
      
      /** Immutable symbol error--user tried to change a CONSTANT. */
      struct symbol_immutable : symbol_error {
        symbol_immutable(const std::string & name)
          : symbol_error("cannot change symbol:  " + name) {}
      };
      
      /** The user requested a symbol that does not (yet) exist. */
      struct undefined_symbol : symbol_error {
        undefined_symbol(const std::string & typ,
                         const std::string & var)
          : symbol_error("undefined " + typ + ":  " + var) {}
      };
      
      /** The user requested a variable that does not (yet) exist. */
      struct undefined_variable : undefined_symbol {
        undefined_variable(const std::string & var)
          : undefined_symbol("variable",var) {}
      };
      
      /** The user requested a function that does not (yet) exist. */
      struct undefined_function : undefined_symbol {
        undefined_function(const std::string & var)
          : undefined_symbol("function", var) {}
      };
      /* ***   END SYMBOL EXCEPTIONS *** */
      
      
      
      /** The symbol type for variables, constants, and functions as used in the
       * symbol table for the units calculators. */
      struct symbol {
        /* TYPEDEFS */
      
        /** /Type of a single pair in the symbol table. */
        typedef std::pair<const std::string, symbol > entry;
        
        /** Symbol table for storing variables, constants, and math functions. */
        typedef std::map<std::string, symbol > table;
      
        typedef physical::Quantity (*func_qargs0)();
        typedef physical::Quantity (*func_qargs1)( const physical::Quantity & );
        typedef physical::Quantity (*func_qargs2)( const physical::Quantity &,
                                                   const physical::Quantity & );
        typedef physical::Quantity (*func_qargsN)
          ( const std::vector<physical::Quantity> & );

        typedef physical::Quantity (*func_str_args1)( const std::string & );
        typedef physical::Quantity (*func_str_args2)( const std::string &,
                                                      const std::string & );
        typedef physical::Quantity (*func_str_argsN)
          ( const std::vector<std::string> & );

        /** The type of symbols stored in the symbol table. */
        enum TYPE {
          UNDEFINED,
          VARIABLE,
          CONSTANT,
          FUNCTION
        };

        /** Additional type information when the symbol is a FUNCTION. */
        enum FUNCTION_TYPE {
          QARGS0,
          QARGS1,
          QARGS2,
          QARGSN,
          STR_ARGS1,
          STR_ARGS2,
          STR_ARGSN
        };

        /** Regular expression matcher for symbols. */
        struct regex_matcher {
          /* MEMBER STORAGE */
          boost::regex expression;

          /* MEMBER FUNCTIONS */
          regex_matcher(const std::string & regex) {
            expression = boost::regex(regex == "*" ? ".*" : regex);
          }

          bool matches(const std::string & test) {
            return boost::regex_match( test.begin(), test.end(), expression );
          }
        };
      
      


        /* MEMBER STORAGE */
        /** The type of this particular symbol. */
        enum TYPE type;

        /** The type of this particular symbol. This value is undefined when
         * type != FUNCTION */
        enum FUNCTION_TYPE function_type;
      
        /** The value of this particular symbol.  Note that although this struct
         * is better thought of as a union, a union with physical::Quantity is
         * impossible since it has a constructor. */
        struct {
          /** The value of the symbol if it is a physical::Quantity type. */
          physical::Quantity dval;

          /** The pointer to the function if the symbol is a function. */
          union {
            func_qargs0 qargs0;
            func_qargs1 qargs1;
            func_qargs2 qargs2;
            func_qargsN qargsN;
            func_str_args1 str_args1;
            func_str_args2 str_args2;
            func_str_argsN str_argsN;
          } func;
        } value;
      


        /* MEMBER FUNCTIONS */
        /** Default symbol constructor creates an UNDEFINED symbol. */
        symbol() : type(UNDEFINED) {}
      
        /** Construct a physical::Quantity symbol and optionally define it as a
         * constant or variable... */
        symbol( const physical::Quantity & dval,
                const enum TYPE & type = CONSTANT ) {
          if ( type != VARIABLE && type != CONSTANT )
            throw symbol_error( "Symbols with quantity values must be assigned "
                                "as either VARIABLE or CONSTANT types" );

          this->type = type;
          this->value.dval = dval;
        }
      
        /** Contruct a FUNCTION symbol with zero arguments. */
        symbol( const func_qargs0 & f ) {
          this->type = FUNCTION;
          this->function_type = QARGS0;
          this->value.func.qargs0 = f;
        }

        /** Contruct a FUNCTION symbol with 1 argument. */
        symbol( const func_qargs1 & f ) {
          this->type = FUNCTION;
          this->function_type = QARGS1;
          this->value.func.qargs1 = f;
        }
      
        /** Contruct a FUNCTION symbol with 2 arguments. */
        symbol( const func_qargs2 & f ) {
          this->type = FUNCTION;
          this->function_type = QARGS2;
          this->value.func.qargs2 = f;
        }
      
        /** Contruct a FUNCTION symbol with N arguments. */
        symbol( const func_qargsN & f ) {
          this->type = FUNCTION;
          this->function_type = QARGSN;
          this->value.func.qargsN = f;
        }

        /** Contruct a FUNCTION symbol with 1 string argument. */
        symbol( const func_str_args1 & f ) {
          this->type = FUNCTION;
          this->function_type = STR_ARGS1;
          this->value.func.str_args1 = f;
        }
      
        /** Contruct a FUNCTION symbol with 2 string arguments. */
        symbol( const func_str_args2 & f ) {
          this->type = FUNCTION;
          this->function_type = STR_ARGS2;
          this->value.func.str_args2 = f;
        }
      
        /** Contruct a FUNCTION symbol with N string arguments. */
        symbol( const func_str_argsN & f ) {
          this->type = FUNCTION;
          this->function_type = STR_ARGSN;
          this->value.func.str_argsN = f;
        }

        /** Provided this symbol is a function, return the number of arguments
         * that it requires/supports.
         * @returns -1 if a vector of arguments required.
         */
        int numberOfArguments() const {
          if ( type != FUNCTION )
            throw symbol_error( "non-function symbol cannot "
                                "be treated as function" );

          switch (function_type) {
            default:
            case QARGS0:
              return 0;
            case QARGS1:
              return 1;
            case QARGS2:
              return 2;
            case QARGSN:
              return -1;
            case STR_ARGS1:
              return 1;
            case STR_ARGS2:
              return 2;
            case STR_ARGSN:
              return -1;
          }
        }

        /** Provided this symbol is a function, return the number of arguments
         * that it requires/supports.
         * @returns -1 if a vector of arguments required.
         */
        const physical::Quantity & evaluate() const {
          switch ( type ) {
            case VARIABLE:
            case CONSTANT:
              return value.dval;

            default:
            case UNDEFINED:
            case FUNCTION:
              throw symbol_error( "non-value symbol cannot "
                                  "be treated as value" );
          }/* switch */
        }

        /** Provided this symbol is a function, evaluate it with the given
         * arguments--this is the version for physical::Quantity arguments.
         */
        physical::Quantity
        evaluate( const std::vector<physical::Quantity> & args ) const {
          switch ( type ) {
            case FUNCTION:
              switch (function_type) {
                case QARGS0:
                  if ( args.size() != 0u )
                    break;
                  return value.func.qargs0();

                case QARGS1:
                  if ( args.size() != 1u )
                    break;
                  return value.func.qargs1(args[0]);

                case QARGS2:
                  if ( args.size() != 2u )
                    break;
                  return value.func.qargs2(args[0], args[1]);

                case QARGSN:
                  return value.func.qargsN(args);

                case STR_ARGS1:
                case STR_ARGS2:
                case STR_ARGSN:
                  throw symbol_error( "function does not "
                                      "accept string arguments" );

                default:
                  throw symbol_error( "type==function but "
                                      "function_type is undefined" );
              }/* switch */
              /* if we made it this far, then we didn't have the correct number
               * of arguments. */
              throw symbol_error("incorrect number of args for function" );
              

            default:
            case VARIABLE:
            case CONSTANT:
            case UNDEFINED:
              throw symbol_error( "non-function symbol cannot "
                                  "be treated as function" );
          }/* switch */
        }

        /** Provided this symbol is a function, evaluate it with the given
         * arguments--this is the version for std::string arguments.
         */
        physical::Quantity
        evaluate( const std::vector<std::string> & args ) const {
          switch ( type ) {
            case FUNCTION:
              switch (function_type) {
                case QARGS0:
                case QARGS1:
                case QARGS2:
                case QARGSN:
                  throw symbol_error( "function takes string arguments" );

                case STR_ARGS1:
                  if ( args.size() != 1u )
                    break;
                  return value.func.str_args1(args[0]);

                case STR_ARGS2:
                  if ( args.size() != 2u )
                    break;
                  return value.func.str_args2(args[0], args[1]);

                case STR_ARGSN:
                  return value.func.str_argsN(args);

                default:
                  throw symbol_error( "type==function but "
                                      "function_type is undefined" );
              }/* switch */
              /* if we made it this far, then we didn't have the correct number
               * of arguments. */
              throw symbol_error("incorrect number of args for function" );
              

            default:
            case VARIABLE:
            case CONSTANT:
            case UNDEFINED:
              throw symbol_error( "non-function symbol cannot "
                                  "be treated as function" );
          }/* switch */
        }
      
      
        /** Perform an import of symbols in a symbol table from one namespace to
         * another. */
        static void import( table & tab,
                            const std::string & base,
                            const std::string & regex,
                            const std::string & new_ns = "" )
        throw (symbol_error) {
          try {
            registry::importer<regex_matcher>()(
                tab,
                base,
                regex,
                new_ns
            );
          } catch (boost::regex_error & e) {
            /* rethrow */
            throw symbol_error(e.what());
          }
        }
      
        /** Clear matched symbols from a symbol table. */
        static void clear( table & tab,
                           const std::string & base,
                           const std::string & regex )
        throw (symbol_error) {
          try {
            registry::clearer<regex_matcher>()(
                tab,
                base,
                regex
            );
          } catch (boost::regex_error & e) {
            /* rethrow */
            throw symbol_error(e.what());
          }
        }
      
      };/* symbol */
      
      /** Stream insertion for symbols. */
      inline std::ostream & operator<<(std::ostream &out, const symbol & sym) {
        switch(sym.type) {
          case symbol::UNDEFINED:
            out << "undefined";
            break;
      
          case symbol::VARIABLE:
            out << sym.value.dval;
            break;
      
          case symbol::CONSTANT:
            out << sym.value.dval << " (const)";
            break;
      
          case symbol::FUNCTION:
            out << '(';
            switch(sym.function_type) {
              case symbol::QARGS0:
                break;
              case symbol::QARGS1:
                out << " <value> ";
                break;
              case symbol::QARGS2:
                out << " <value>, <value> ";
                break;
              case symbol::QARGSN:
                out << " <value>, ... ";
                break;
              case symbol::STR_ARGS1:
                out << " <string> ";
                break;
              case symbol::STR_ARGS2:
                out << " <string>, <string> ";
                break;
              case symbol::STR_ARGSN:
                out << " <string>, ... ";
                break;
            }
            out << ')';
            break;
        }
        return out;
      }

    } /* namespace runtime::physical::calc */
  } /* namespace runtime::physical */
} /* namespace runtime */

#endif // physical_calc_symbol_h
