#ifndef PHYSICAL_CALC_SYMBOL_H
#define PHYSICAL_CALC_SYMBOL_H

#include <boost/regex.hpp>
//#include <regex> // have to wait until the new std:: stl

#include <string>

#include <physical/quantity.h>
#include <physical/registry.h>

namespace runtime {
    namespace physical { namespace calc {

    /* *** BEGIN SYMBOL EXCEPTIONS *** */
    struct symbol_error : physical::exception {
        typedef physical::exception super;
        symbol_error(const std::string & err) : super(err) {}
    };
    
    struct symbol_immutable : symbol_error {
        symbol_immutable(const std::string & name) :
            symbol_error("cannot change symbol:  " + name) {}
    };
    
    struct undefined_symbol : symbol_error {
        undefined_symbol(const std::string & typ,
                         const std::string & var) :
            symbol_error("undefined " + typ + ":  " + var) {}
    };
    
    struct undefined_variable : undefined_symbol {
        undefined_variable(const std::string & var) :
            undefined_symbol("variable",var) {}
    };
    
    struct undefined_function : undefined_symbol {
        undefined_function(const std::string & var) :
            undefined_symbol("function", var) {}
    };
     
    /* ***   END SYMBOL EXCEPTIONS *** */
    
    
    
    struct symbol {
    
        /** /Type of a single pair in the symbol table. */
        typedef std::pair<const std::string, symbol > entry;
        
        /** Symbol table for storing variables, constants, and math functions. */
        typedef std::map<std::string, symbol > table;
    
        typedef physical::Quantity (*math_function)(const physical::Quantity &);
        enum TYPE {
            UNDEFINED,
            VARIABLE,
            CONSTANT,
            FUNCTION
        };
    
        enum TYPE type;
    
        struct {
            physical::Quantity dval;
            math_function mfunc;
        } value;
    
        symbol() : type(UNDEFINED) {}
    
        symbol(const physical::Quantity & _dval, const enum TYPE & _type = CONSTANT) {
            type = _type;
            value.dval = _dval;
        }
    
        symbol(const math_function & _mfunc) {
            type = FUNCTION;
            value.mfunc = _mfunc;
        }
    
    
        struct regex_matcher {
            regex_matcher(const std::string & regex) {
                expression = boost::regex(regex == "*" ? ".*" : regex);
            }
            bool matches(const std::string & test) {
                return boost::regex_match(
                           test.begin(),
                           test.end(),
                           expression
                       );
            }

            boost::regex expression;
        };
    
        static void import(table & tab,
                           const std::string & base,
                           const std::string & regex,
                           const std::string & new_ns = "") {
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
    
        static void clear(table & tab,
                          const std::string & base,
                          const std::string & regex) {
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
    
    };
    
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
                out << "()";
                break;
        }
        return out;
    }



}}} /* namespace runtime::physical */

#endif // PHYSICAL_CALC_SYMBOL_H
