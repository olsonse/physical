
#ifndef PHYSICAL_CALC_INFIX_H
#define PHYSICAL_CALC_INFIX_H


#include <boost/spirit.hpp>
#include <boost/spirit/phoenix/binders.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <istream>
#include <map>
#include <ostream>
#include <string>
#include <stdexcept>
#include <math.h>
#include <vector>

#include <physical/quantity.h>
#include <physical/calc/symbol.h>
#include <physical/calc/BaseCalc.h>

namespace runtime { namespace physical { namespace calc {

// Semantic actions can be functors. The operator() function is called
// with two iterators that specify the range of input that matches the production.

struct do_quit {
    template<typename Iter>
    void operator()(Iter, Iter) const {
        std::exit(EXIT_SUCCESS);
    }
};



class InfixCalcEngine : public boost::spirit::grammar<InfixCalcEngine> {
  public:
    // The parser object is copied a lot, so instead of keeping its own table
    // of symbols, it keeps track of a reference to a common table.
    InfixCalcEngine(symbol::table& _symbols, Quantity & result, bool & result_set) :
        symbols(_symbols), resultRef(result), result_setRef(result_set) {}

    // A production can have an associated closure, to store information
    // for that production.
    struct value_closure : boost::spirit::closure<value_closure, Quantity> {
        member1 value;
    };
 
    struct assignment_closure :
      boost::spirit::closure<assignment_closure, Quantity, std::string> {
        member1 value;
        member2 name;
    };
 
    struct string_closure : boost::spirit::closure<string_closure, std::string> {
        member1 str;
    };

    struct sym_closure :
      boost::spirit::closure<sym_closure, std::string, std::string, std::string> {
        member1 base;
        member2 regex;
        member3 to_ns;
    };
 
    // Following is the grammar definition.
    template <typename ScannerT>
    struct definition {
        definition(InfixCalcEngine const& self) {
            using namespace boost::spirit;
            using namespace phoenix;

            // A statement can end at the end of the line, or with a semicolon.
            statement
                =   ( command
                    | assignment
                    | expression[bind(&InfixCalcEngine::save_result)(self, arg1)]
                    )
                >> (end_p | ';')
                ;
           

            // The commands are linked to functors or member functions,
            // to demonstrate both styles. In real code, you should choose
            // one style and use it uniformly.
            command
                = lexeme_d[str_p("quit")][do_quit()]
                | (
                    lexeme_d[str_p("dump")]
                    >> (
                        lexeme_d[str_p("constants")][bind(&InfixCalcEngine::dump)(self, symbol::CONSTANT)]
                       |lexeme_d[str_p("variables")][bind(&InfixCalcEngine::dump)(self, symbol::VARIABLE)]
                       |lexeme_d[str_p("functions")][bind(&InfixCalcEngine::dump)(self, symbol::FUNCTION)]
                       |eps_p                       [bind(&InfixCalcEngine::dump)(self, symbol::UNDEFINED)]
                       )
                  )
                | lexeme_d[str_p("help")][bind(&InfixCalcEngine::help)(self)]
                | sym_command
                ;

            sym_command
                = (
                    lexeme_d[ str_p("from") ]
                    >> identifier[ sym_command.base = arg1 ]
                    >> lexeme_d[ str_p("import") ]
                    >> (
                        str[ sym_command.regex = arg1 ]
                       |ch_p('*')[ sym_command.regex = arg1 ]
                       )
                    >> (
                        (
                         lexeme_d[ str_p("to") ]
                         >> identifier[ /*sym_command.to_ns = arg1*/ sym_command.base += ">" + arg1 ]
                        ) //[bind(&InfixCalcEngine::symbol_import)(self, sym_command.base, sym_command.regex, sym_command.to_ns)]
                       | eps_p //[bind(&InfixCalcEngine::symbol_import)(self, sym_command.base, sym_command.regex)]
                       )
                  )[bind(&InfixCalcEngine::symbol_import)(self, sym_command.base, sym_command.regex)] 
                | (
                    lexeme_d[ str_p("clear") ]
                    >> (
                        identifier[ sym_command.base = arg1 ][ sym_command.regex = "" ]
                       |str[ sym_command.regex = arg1 ]
                       |ch_p('*')[ sym_command.regex = arg1 ]
                       )
                  ) [bind(&InfixCalcEngine::symbol_clear)(self, sym_command.base, sym_command.regex)]
                | (
                    lexeme_d[ str_p("from") ]
                    >> identifier[ sym_command.base = arg1 ]
                    >> lexeme_d[ str_p("clear") ]
                    >> (
                        str[ sym_command.regex = arg1 ]
                       |ch_p('*')[ sym_command.regex = arg1 ]
                       )
                  ) [bind(&InfixCalcEngine::symbol_clear)(self, sym_command.base, sym_command.regex)]
                ;

            str = lexeme_d[
                       ch_p('\'')
                    >> +(anychar_p - '\'')
                    >> ch_p('\'')
                  ][str.str = construct_<std::string>(arg1+1,arg2-1)]
                ;
           
            // An assignment statement must store the variable name and value.
            // The name and the value are stored in the closure, then the define
            // function is called to store the definition. Notice how a rule can
            // have multiple semantic actions.
            assignment
                = (
                    identifier[assignment.name = arg1]
                    >> '='
                    >> assignment[assignment.value = arg1]
                  ) [bind(&InfixCalcEngine::define_variable)(self, assignment.name, assignment.value)]
                | (
                    identifier[assignment.name = arg1]
                    >> '='
                    >> expression[assignment.value = arg1]
                  ) [bind(&InfixCalcEngine::define_variable)(self, assignment.name, assignment.value)]
                ;
           
            expression
                = term[expression.value = arg1]
                  >> *( ('+' >> term[expression.value += arg1])
                      | ('-' >> term[expression.value -= arg1])
                      )
                ;

            // The lexeme_d directive tells the scanner to treat white space as
            // significant. Thus, an identifier cannot have internal white space.
            // The alpha_p and alnum_p parsers are built-in.
            // Notice how the semantic action uses a Phoenix lambda function
            // that constructs a std::string. The arg1 and arg2 placeholders are
            // are bound at runtime to the iterator range that matches this rule.
            identifier
                = lexeme_d [
                  !str_p("::")
                  >> ( alpha_p | '_')
                  >> *(
                        (
                         str_p("::")
                         >> ( alpha_p | '_')
                        )
                        | (alnum_p | '_')
                      )
                ][identifier.str = construct_<std::string>(arg1, arg2)]
                ;
           
            term
                = (
                  factor[term.value = arg1]
                  >> *( ('*' >> factor[term.value *= arg1])
                      | ('/' >> factor[term.value /= arg1])
                      | ('%' >> factor[term.value %= arg1])
                    )
                  )
                ;
           
            // A variable name must be looked up. This is a straightforward
            // Phoenix binding.
            factor
                = exponentiation[factor.value = arg1]
                | exp_factor    [factor.value = arg1]
                ;

            exponentiation
                =    exp_factor[exponentiation.value = arg1]
                  >> '^'
                  >> exp_factor[exponentiation.value ^= arg1]
                ;

            exp_factor
                = function[  exp_factor.value = arg1]
                | group   [  exp_factor.value = arg1]
                | literal [  exp_factor.value = arg1]
                | identifier[exp_factor.value = bind(&InfixCalcEngine::lookup_val)(self, arg1)]
                ;

            function
                = identifier[function.name = arg1]
                  >> group[function.value = bind(&InfixCalcEngine::exec_func)(self, function.name,arg1)]
                ;
           
            // The longest_d directive is built-in to tell the parser to make
            // the longest match it can. Thus "1.23" matches real_p rather than
            // int_p followed by ".23".
            literal
                = longest_d
                [
                     int_p[literal.value = arg1]
                  | real_p[literal.value = arg1]
                ]
                ;
           
            group
                = '('
                  >> expression[group.value = arg1]
                  >> ')'
                ;
        }
       
        // The start symbol is returned from start().
        boost::spirit::rule<ScannerT> const& start() const { return statement; }
       
        // Each rule must be declared, optionally with an associated closure.
        boost::spirit::rule<ScannerT>                                statement,
                                                                     command;
        boost::spirit::rule<ScannerT, assignment_closure::context_t> assignment,
                                                                     function;
        boost::spirit::rule<ScannerT, string_closure::context_t>     identifier,
                                                                     str;
        boost::spirit::rule<ScannerT, sym_closure::context_t>        sym_command;
        boost::spirit::rule<ScannerT, value_closure::context_t>      expression,
                                                                     factor,
                                                                     exp_factor,
                                                                     group,
                                                                     literal,
                                                                     term,
                                                                     exponentiation;
    };
 
    // Member functions that are called in semantic actions.
    void define_variable(const std::string& name, const Quantity & value) const {
        symbol::table::iterator it = symbols.find(name);
        if (it != symbols.end() && (*it).second.type == symbol::CONSTANT)
            throw symbol_immutable(name);
        symbols[name] = symbol(value,symbol::VARIABLE);
    }

    const Quantity & lookup_val(const std::string& name) const {
        symbol::table::iterator it = symbols.find(name);
        if (it == symbols.end())
            throw undefined_variable(name);
        else {
            const symbol & sym = (*it).second;
            switch(sym.type) {
                case symbol::VARIABLE:
                case symbol::CONSTANT:
                    return sym.value.dval;;

                case symbol::FUNCTION:
                    throw undefined_variable(name);

                default:
                case symbol::UNDEFINED:
                    throw undefined_symbol("???",name);
            }
        }
    }

    Quantity exec_func(const std::string& name, const Quantity & arg) const {
        symbol::table::iterator it = symbols.find(name);
        if (it == symbols.end()) {
            throw undefined_function(name);
        } else {
            const symbol & sym = (*it).second;

            switch(sym.type) {
                case symbol::FUNCTION:
                    return sym.value.mfunc(arg);

                default:
                case symbol::UNDEFINED:
                    throw undefined_function(name);
            }
        }
    }
 
    void save_result(const Quantity & x) const {
        resultRef = x;
        result_setRef = true;
    }
 
    void dump(const enum symbol::TYPE & typ = symbol::UNDEFINED) const {
        // Dump the entire symbol table. Notice how this function uses
        // Boost lambda functions instead of Phoenix, just to show you that
        // you can mix the two in a single file.
        using namespace boost::lambda;
        switch (typ) {
            case symbol::UNDEFINED:
            for_each(symbols.begin(), symbols.end(),
                std::cout << bind(&symbol::entry::first, _1)  << "\t=  "
                          << bind(&symbol::entry::second, _1) << '\n');
                break;
            default: {
                symbol::table::iterator i;
                for (i = symbols.begin(); i != symbols.end(); i++)
                    if (i->second.type == typ)
                        std::cout << i->first << "\t=  " << i->second << '\n';
            }
        }
    }

    void help() const {
        std::cout << "Commands:\n"
                     "\tquit                             : quit (of course)\n"
                     "\tdump                             : dumps the list of all known symbols\n"
                     "\tdump constants                   : dumps the list of constant symbols\n"
                     "\tdump variables                   : dumps the list of variable symbols\n"
                     "\tdump functions                   : dumps the list of function symbols\n"
                     "\thelp                             : show this message\n"
                     "\tfrom <prefix> import {*|'regex'} : copy symbols from <prefix> into the\n"
                     "\t                                   root  namespace.  The symbols that\n"
                     "\t                                   are copied can be controlled further\n"
                     "\t                                   with a regular expression for the\n"
                     "\t                                   remaining portion of the symbol name\n"
                     "\tclear {*|'regex'}                : remove particular symbols from memory\n"
                     "\tfrom <prefix> clear {*|'regex'}  : remove symbols that are in the <prefix>\n"
                     "\t                                   namespace and match the regular\n"
                     "\t                                   expression string regex\n"
                     "\n"
                     "Operators supported:\n"
                     "\t<var-name> = <expression>        : Level 0 precedence (lowest)\n"
                     "\t+, -                             : Level 1 precedence\n"
                     "\t*, /, %                          : Level 2 precedence\n"
                     "\t^                                : Level 3 precedence\n"
                     "\n"
                     "Additional information:\n"
                     "\tUnary functions are supported (such as sin, cos, tan, exp, ...)\n"
                     "\tAssignment to variables is supported, such as: v = 10*m/s\n"
                     "\t(Note:  CONSTANT symbol names will not allow reassignment)\n"
                  << std::flush;
    }

    void symbol_import (const std::string & base, const std::string & regex) const {
        std::string to = "";
        std::string from = base;
        size_t pos = base.find(">");
        if (pos != std::string::npos) {
            from = base.substr(0,pos);
            to = base.substr(pos+1);
        }
        symbol::import(symbols, from, regex, to);
    }

    void symbol_clear (const std::string & base, const std::string & regex) const {
        symbol::clear(symbols, base, regex);
    }

    const Quantity & result() const {return resultRef;}
    const bool & result_set() const {return result_setRef;}
    void reset_result_set() {result_setRef = false;}

  private:
    symbol::table & symbols;

    /** The result of one engine operations.  This value is NOT thread-safe
     * for a single instance, of course. */
    Quantity & resultRef;

    bool & result_setRef;
};

struct InfixCalc : BaseBoostCalc<InfixCalcEngine>, BaseCalc<InfixCalc> {
    typedef BaseBoostCalc<InfixCalcEngine>      base_boost_calc;
    typedef BaseCalc<InfixCalc>                 base_calc;
    Quantity                                    result;
    bool                                        result_set;
    InfixCalcEngine                             engine;
    InfixCalc() : base_boost_calc(engine), base_calc(), result(),
                  engine(base_calc::symbols,result,result_set) {}
};

}}} /* namespace runtime::physical::calc */

#endif // PHYSICAL_CALC_INFIX_H
