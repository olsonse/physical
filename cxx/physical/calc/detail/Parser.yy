/* $Id: parser.yy 48 2009-09-05 08:07:10Z tb $ -*- mode: c++ -*- */
/** \file parser.yy Contains the example Bison parser source */

%{ /*** C/C++ Declarations ***/

#include <physical/runtime.h>
#include <physical/calc/Driver.h>
#include <physical/calc/detail/expression/Literal.h>
#include <physical/calc/detail/expression/Function.h>
#include <physical/calc/detail/expression/StringFunction.h>
#include <physical/calc/detail/expression/Power.h>
#include <physical/calc/detail/expression/Negate.h>
#include <physical/calc/detail/expression/Multiply.h>
#include <physical/calc/detail/expression/Divide.h>
#include <physical/calc/detail/expression/Modulo.h>
#include <physical/calc/detail/expression/Add.h>
#include <physical/calc/detail/expression/Subtract.h>
#include <physical/calc/detail/expression/Assign.h>
#include <physical/calc/detail/expression/VariableLookup.h>

#include <stdio.h>
#include <string>
#include <vector>

namespace runtime { namespace physical { namespace calc { namespace detail {
  void bison_parser_help();

  inline std::string sstrip( const std::string & s );
} } } }

%}

/*** yacc/bison Declarations ***/

/* Require bison 2.4 or later */
%require "2.4"

/* add debug output code to generated parser. disable this for release
 * versions. */
%debug

/* start symbol is named "start" */
%start start

/* write out a header file containing the token defines */
%defines

/* use newer C++ skeleton file */
%skeleton "lalr1.cc"

/* namespace to enclose parser in */
%define api.namespace {runtime::physical::calc::detail}

/* set the parser's class identifier */
%define "parser_class_name" {Parser}

/* keep track of the current position within the input */
%locations
%initial-action {
  // initialize the initial location object
  @$.begin.filename = @$.end.filename = &driver.streamname;
};

/* The driver is passed by reference to the parser and to the scanner. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class Driver& driver }

/* verbose error messages */
%error-verbose

%code requires {
#include <vector>

namespace runtime {
  namespace physical {
    namespace calc {
      namespace detail {
        namespace expression {
          class Node;
        }
      }
    }
  }
}
}

 /*** BEGIN EXAMPLE - Change the example grammar's tokens below ***/

%union {
  int                                     integerVal;
  double                                  doubleVal;
  std::string*                            stringVal;
  std::vector< std::string >*             stringVector;
  class expression::Node*                 calcnode;
  std::vector< class expression::Node* >* nodeVector;
}

%token                  END          0  "end of file"
%token                  EOL             "end of line"
%token <doubleVal>      DOUBLE          "double"
%token <stringVal>      STRING          "string"
%token <stringVal>      IDENTIFIER      "identifier"
%token <stringVal>      KEYWORD_QUIT    "quit keyword"
%token <stringVal>      KEYWORD_DUMP    "dump keyword"
%token <stringVal>      KEYWORD_SET     "set keyword"
%token <stringVal>      KEYWORD_HELP    "help keyword"
%token <stringVal>      KEYWORD_FROM    "from keyword"
%token <stringVal>      KEYWORD_CLEAR   "clear keyword"

%type <calcnode>        literal variable
%type <calcnode>        atomexpr function powexpr factor term expr assignment
%type <stringVector>    string_list
%type <nodeVector>      expr_list

%left '-' '+'
%left '*' '/'
%right '^'

%destructor { delete $$; } STRING IDENTIFIER
%destructor { delete $$; } literal variable
%destructor { delete $$; } atomexpr function powexpr factor term expr assignment
%destructor { delete $$; } string_list
%destructor {
  while ( !$$->empty() ) {
    delete $$->back();
    $$->pop_back();
  }
  
  delete $$;
} expr_list

 /*** END EXAMPLE - Change the example grammar's tokens above ***/

%{

#include <physical/calc/detail/Scanner.h>

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex

%}

%% /*** Grammar Rules ***/

 /*** BEGIN EXAMPLE - Change the example grammar rules below ***/

literal : DOUBLE
      {
        $$ = new expression::Literal($1);
      }

variable : IDENTIFIER
      {
        $$ = new expression::VariableLookup(driver.symbols, *$1);
        delete $1;
      }

expr_list : expr
      {
        $$ = new std::vector< expression::Node * >();
        $$->push_back( $1 );
      }
    | expr_list ',' expr
      {
        $$ = $1;
        $$->push_back( $3 );
      }

string_list : STRING
      {
        $$ = new std::vector< std::string >();
        $$->push_back( sstrip(*$1) );
        delete $1;
      }
    | string_list ',' STRING
      {
        $$ = $1;
        $$->push_back( sstrip(*$3) );
        delete $3;
      }

function : IDENTIFIER '(' ')'
      {
        $$ = new expression::Function(driver.symbols, *$1);
        delete $1;
      }
    | IDENTIFIER '(' expr_list ')'
      {
        $$ = new expression::Function(driver.symbols, *$1, *$3);
        delete $1;
        delete $3;
      }
    | IDENTIFIER '(' string_list ')'
      {
        $$ = new expression::StringFunction(driver.symbols, *$1, *$3);
        delete $1;
        delete $3;
      }

atomexpr : literal
      {
        $$ = $1;
      }
    | variable
      {
        $$ = $1;
      }
    | '(' expr ')'
      {
        $$ = $2;
      }
    | function
      {
        $$ = $1;
      }

powexpr :  atomexpr
      {
        $$ = $1;
      }
    | atomexpr '^' factor
      {
        $$ = new expression::Power($1, $3);
      }

factor : powexpr
      {
        $$ = $1;
      }
    | '+' powexpr
      {
        $$ = $2;
      }
    | '-' powexpr
      {
        $$ = new expression::Negate($2);
      }

term : factor
      {
        $$ = $1;
      }
    | term '*' factor
      {
        $$ = new expression::Multiply($1, $3);
      }
    | term '/' factor
      {
        $$ = new expression::Divide($1, $3);
      }
    | term '%' factor
      {
        $$ = new expression::Modulo($1, $3);
      }

expr : term
      {
        $$ = $1;
      }
    | expr '+' expr
      {
        $$ = new expression::Add($1, $3);
      }
    | expr '-' expr
      {
        $$ = new expression::Subtract($1, $3);
      }

assignment : IDENTIFIER '=' expr
      {
        $$ = new expression::Assign(driver.symbols, *$1, $3);
        delete $1;
      }
    | IDENTIFIER '=' assignment /* for chained assignments. */
      {
        $$ = new expression::Assign(driver.symbols, *$1, $3);
        delete $1;
      }

dump_command : KEYWORD_DUMP
      {
        driver.dump( std::cout );
        delete $1;
      }
    | KEYWORD_DUMP IDENTIFIER
      { /* e.g. dump constants */
        enum symbol::TYPE sym_type = symbol::UNDEFINED;
        if      ( (*$2) == "constants" )
            sym_type = symbol::CONSTANT;
        else if ( (*$2) == "variables" )
            sym_type = symbol::VARIABLE;
        else if ( (*$2) == "functions" )
            sym_type = symbol::FUNCTION;

        driver.dump( std::cout, sym_type );

        delete $1;
        delete $2;
      }

set_command : KEYWORD_SET IDENTIFIER IDENTIFIER
      { /* e.g.  set output pretty */
        bool success = false;
        if (*$2 == "output") {
          success = true;
          if        (*$3 == "pretty") {
            Quantity::setPrintMode(Quantity::PRETTY_PRINT);
          } else if (*$3 == "math") {
            Quantity::setPrintMode(Quantity::MATH_PRINT);
          } else if (*$3 == "latex") {
            Quantity::setPrintMode(Quantity::LATEX_PRINT);
          } else if (*$3 == "latex::oneline") {
            Quantity::setPrintMode(Quantity::LATEX_ONELINE_PRINT);
          } else if (*$3 == "ugly") {
            Quantity::setPrintMode(Quantity::UGLY_PRINT);
          } else
            success = false;
        }

        delete $1;
        delete $2;
        delete $3;

        if ( !success ) {
          error(yyla.location, "invalid set command " );
          YYERROR;
        }
      }

from_command : KEYWORD_FROM IDENTIFIER IDENTIFIER '*'
      { /* e.g.  from physical::unit import * */
        bool success = true;
        if ( *$3 == "import" )
          symbol::import( driver.symbols, *$2, "*" );
        else if ( *$3 == "clear" )
          symbol::clear(driver.symbols, *$2, "*" );
        else
          success = false;

        delete $1;
        delete $2;
        delete $3;

        if ( !success ) {
          error(yyla.location, "invalid from command " );
          YYERROR;
        }
      }
    | KEYWORD_FROM IDENTIFIER IDENTIFIER '*' IDENTIFIER IDENTIFIER
      { /* e.g.  from physical::unit import * to myunits */
        bool success = true;
        if ( *$3 == "import" && *$5 == "to" )
          symbol::import( driver.symbols, *$2, "*", *$6 );
        else
          success = false;

        delete $1;
        delete $2;
        delete $3;
        delete $5;
        delete $6;

        if ( !success ) {
          error(yyla.location, "invalid from command " );
          YYERROR;
        }
      }
    | KEYWORD_FROM IDENTIFIER IDENTIFIER STRING
      { /* e.g.  from physical import 'element::.*' */
        bool success = true;
        if ( *$3 == "import" )
          symbol::import( driver.symbols, *$2, sstrip(*$4) );
        else if ( *$3 == "clear" )
          symbol::clear(driver.symbols, *$2, sstrip(*$4) );
        else
          success = false;

        delete $1;
        delete $2;
        delete $3;
        delete $4;

        if ( !success ) {
          error(yyla.location, "invalid from command " );
          YYERROR;
        }
      }
    | KEYWORD_FROM IDENTIFIER IDENTIFIER STRING IDENTIFIER IDENTIFIER
      { /* e.g.  from physical::unit import 'element::.*' to myelements */
        bool success = true;
        if ( *$3 == "import" && *$5 == "to" )
          symbol::import( driver.symbols, *$2, sstrip(*$4), *$6 );
        else
          success = false;

        delete $1;
        delete $2;
        delete $3;
        delete $4;
        delete $5;
        delete $6;

        if ( !success ) {
          error(yyla.location, "invalid from command " );
          YYERROR;
        }
      }

clear_command : KEYWORD_CLEAR '*'
      { /* e.g. clear * */
        symbol::clear( driver.symbols, "", "*" );
        delete $1;
      }
    | KEYWORD_CLEAR IDENTIFIER
      { /* e.g. clear physcal::unit::m */
        symbol::clear( driver.symbols, *$2, "" );
        delete $1;
        delete $2;
      }
    | KEYWORD_CLEAR STRING
      { /* e.g. clear 'physical::element::.*' */
        symbol::clear( driver.symbols, "", sstrip(*$2) );
        delete $1;
        delete $2;
      }

command : KEYWORD_QUIT
      {
        std::cerr << "just hit CTL-C!" << std::endl;
        delete $1;
        /* std::exit(EXIT_SUCCESS); */
      }
    | dump_command
    | set_command
    | KEYWORD_HELP
      {
        bison_parser_help();
        delete $1;
      }
    | from_command
    | clear_command

/** End of statements. */
eos : ';'
    | EOL

/** End of All! */
eoa : eos
    | END

start : /* empty */
    | start eos
    | start command eoa
    | start assignment eoa
      {
        driver.expressions.push_back($2);
      }
    | start expr eoa
      {
        driver.expressions.push_back($2);
      }

/*** EN D EXAMPLE - Change the example grammar rules above ***/

%% /*** Additional Code ***/

namespace runtime { namespace physical { namespace calc { namespace detail {
  void Parser::error( const Parser::location_type& l,
                               const std::string& m ) {
    driver.error(l, m);
  }

  void bison_parser_help() {
    std::cerr <<
     "Commands:\n"
     "\tquit                             : quit (of course)\n"
     "\tdump                             : dumps the list of all known symbols\n"
     "\tdump constants                   : dumps the list of constant symbols\n"
     "\tdump variables                   : dumps the list of variable symbols\n"
     "\tdump functions                   : dumps the list of function symbols\n"
     "\tset output pretty                : sets the output to mimic GNU units output (default)\n"
     "\tset output math                  : sets the output to be mathematically correct\n"
     "\tset output latex                 : sets the output to formatted for latex math mode using \\frac{}{}\n"
     "\tset output latex::oneline        : sets the output to formatted for latex math mode on one line\n"
     "\tset output ugly                  : sets the output to demonstrate the underlying units structure\n"
     "\thelp                             : show this message\n"
     "\tfrom <prefix> import {*|'regex'} [to <new_prefix>]\n"
     "\t                                 : copy symbols from <prefix> into a new \n"
     "\t                                   namespace.  If the optional 'to <new_prefix>'\n"
     "\t                                   is not given, the root namespace will be targeted.\n"
     "\t                                   The symbols that are copied can be controlled further\n"
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
     "non-math builtin functions supported:\n"
     "\tnew_unit('unit-name')            : Creates a new fundamental unit called 'unit-name.'\n"
     "\t                                   This builtin function returns an\n"
     "\t                                   expression that can be used like\n"
     "\t                                   any other expression.\n"
     "\n"
     "Additional information:\n"
     "\tUnary functions are supported (such as sin, cos, tan, exp, ...)\n"
     "\tAssignment to variables is supported, such as: v = 10*m/s\n"
     "\t(Note:  CONSTANT symbol names will not allow reassignment)\n"
              << std::flush;
  }

  /** This function strips off the leading and trailing quotes.  */
  inline std::string sstrip( const std::string & s ) {
    return s.substr(1, s.size()-2);
  }

} } } }

