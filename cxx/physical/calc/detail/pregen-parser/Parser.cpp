
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008 Free Software
   Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* First part of user declarations.  */

/* Line 311 of lalr1.cc  */
#line 4 "Parser.yy"
 /*** C/C++ Declarations ***/

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



/* Line 311 of lalr1.cc  */
#line 71 "pregen-parser/Parser.cpp"


#include "Parser.hpp"

/* User implementation prologue.  */

/* Line 317 of lalr1.cc  */
#line 135 "Parser.yy"


#include <physical/calc/detail/Scanner.h>

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex



/* Line 317 of lalr1.cc  */
#line 93 "pregen-parser/Parser.cpp"

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* Enable debugging if requested.  */
#if YYDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define yyerrok		(yyerrstatus_ = 0)
#define yyclearin	(yychar = yyempty_)

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


/* Line 380 of lalr1.cc  */
#line 52 "Parser.yy"
namespace runtime { namespace physical { namespace calc { namespace detail {

/* Line 380 of lalr1.cc  */
#line 161 "pregen-parser/Parser.cpp"
#if YYERROR_VERBOSE

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              /* Fall through.  */
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

#endif

  /// Build a parser object.
  Parser::Parser (class Driver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {
  }

  Parser::~Parser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  Parser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    switch (yytype)
      {
         default:
	  break;
      }
  }


  void
  Parser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif

  void
  Parser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
        case 5: /* "\"string\"" */

/* Line 480 of lalr1.cc  */
#line 120 "Parser.yy"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 268 "pregen-parser/Parser.cpp"
	break;
      case 6: /* "\"identifier\"" */

/* Line 480 of lalr1.cc  */
#line 120 "Parser.yy"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 277 "pregen-parser/Parser.cpp"
	break;
      case 25: /* "literal" */

/* Line 480 of lalr1.cc  */
#line 121 "Parser.yy"
	{ delete (yyvaluep->calcnode); };

/* Line 480 of lalr1.cc  */
#line 286 "pregen-parser/Parser.cpp"
	break;
      case 26: /* "variable" */

/* Line 480 of lalr1.cc  */
#line 121 "Parser.yy"
	{ delete (yyvaluep->calcnode); };

/* Line 480 of lalr1.cc  */
#line 295 "pregen-parser/Parser.cpp"
	break;
      case 27: /* "expr_list" */

/* Line 480 of lalr1.cc  */
#line 124 "Parser.yy"
	{
  while ( !(yyvaluep->nodeVector)->empty() ) {
    delete (yyvaluep->nodeVector)->back();
    (yyvaluep->nodeVector)->pop_back();
  }
  
  delete (yyvaluep->nodeVector);
};

/* Line 480 of lalr1.cc  */
#line 311 "pregen-parser/Parser.cpp"
	break;
      case 28: /* "string_list" */

/* Line 480 of lalr1.cc  */
#line 123 "Parser.yy"
	{ delete (yyvaluep->stringVector); };

/* Line 480 of lalr1.cc  */
#line 320 "pregen-parser/Parser.cpp"
	break;
      case 29: /* "function" */

/* Line 480 of lalr1.cc  */
#line 122 "Parser.yy"
	{ delete (yyvaluep->calcnode); };

/* Line 480 of lalr1.cc  */
#line 329 "pregen-parser/Parser.cpp"
	break;
      case 30: /* "atomexpr" */

/* Line 480 of lalr1.cc  */
#line 122 "Parser.yy"
	{ delete (yyvaluep->calcnode); };

/* Line 480 of lalr1.cc  */
#line 338 "pregen-parser/Parser.cpp"
	break;
      case 31: /* "powexpr" */

/* Line 480 of lalr1.cc  */
#line 122 "Parser.yy"
	{ delete (yyvaluep->calcnode); };

/* Line 480 of lalr1.cc  */
#line 347 "pregen-parser/Parser.cpp"
	break;
      case 32: /* "factor" */

/* Line 480 of lalr1.cc  */
#line 122 "Parser.yy"
	{ delete (yyvaluep->calcnode); };

/* Line 480 of lalr1.cc  */
#line 356 "pregen-parser/Parser.cpp"
	break;
      case 33: /* "term" */

/* Line 480 of lalr1.cc  */
#line 122 "Parser.yy"
	{ delete (yyvaluep->calcnode); };

/* Line 480 of lalr1.cc  */
#line 365 "pregen-parser/Parser.cpp"
	break;
      case 34: /* "expr" */

/* Line 480 of lalr1.cc  */
#line 122 "Parser.yy"
	{ delete (yyvaluep->calcnode); };

/* Line 480 of lalr1.cc  */
#line 374 "pregen-parser/Parser.cpp"
	break;
      case 35: /* "assignment" */

/* Line 480 of lalr1.cc  */
#line 122 "Parser.yy"
	{ delete (yyvaluep->calcnode); };

/* Line 480 of lalr1.cc  */
#line 383 "pregen-parser/Parser.cpp"
	break;

	default:
	  break;
      }
  }

  void
  Parser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif

  int
  Parser::parse ()
  {
    /// Lookahead and lookahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    /* State.  */
    int yyn;
    int yylen = 0;
    int yystate = 0;

    /* Error handling.  */
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    semantic_type yylval;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[2];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* User initialization code.  */
    
/* Line 553 of lalr1.cc  */
#line 59 "Parser.yy"
{
  // initialize the initial location object
  yylloc.begin.filename = yylloc.end.filename = &driver.streamname;
}

/* Line 553 of lalr1.cc  */
#line 469 "pregen-parser/Parser.cpp"

    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;

    /* Accept?  */
    if (yystate == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without lookahead.  */
    yyn = yypact_[yystate];
    if (yyn == yypact_ninf_)
      goto yydefault;

    /* Read a lookahead token.  */
    if (yychar == yyempty_)
      {
	YYCDEBUG << "Reading a token: ";
	yychar = yylex (&yylval, &yylloc);
      }


    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yyn == 0 || yyn == yytable_ninf_)
	goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted.  */
    yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
	  case 2:

/* Line 678 of lalr1.cc  */
#line 152 "Parser.yy"
    {
        (yyval.calcnode) = new expression::Literal((yysemantic_stack_[(1) - (1)].doubleVal));
      }
    break;

  case 3:

/* Line 678 of lalr1.cc  */
#line 157 "Parser.yy"
    {
        (yyval.calcnode) = new expression::VariableLookup(driver.symbols, *(yysemantic_stack_[(1) - (1)].stringVal));
        delete (yysemantic_stack_[(1) - (1)].stringVal);
      }
    break;

  case 4:

/* Line 678 of lalr1.cc  */
#line 163 "Parser.yy"
    {
        (yyval.nodeVector) = new std::vector< expression::Node * >();
        (yyval.nodeVector)->push_back( (yysemantic_stack_[(1) - (1)].calcnode) );
      }
    break;

  case 5:

/* Line 678 of lalr1.cc  */
#line 168 "Parser.yy"
    {
        (yyval.nodeVector) = (yysemantic_stack_[(3) - (1)].nodeVector);
        (yyval.nodeVector)->push_back( (yysemantic_stack_[(3) - (3)].calcnode) );
      }
    break;

  case 6:

/* Line 678 of lalr1.cc  */
#line 174 "Parser.yy"
    {
        (yyval.stringVector) = new std::vector< std::string >();
        (yyval.stringVector)->push_back( sstrip(*(yysemantic_stack_[(1) - (1)].stringVal)) );
        delete (yysemantic_stack_[(1) - (1)].stringVal);
      }
    break;

  case 7:

/* Line 678 of lalr1.cc  */
#line 180 "Parser.yy"
    {
        (yyval.stringVector) = (yysemantic_stack_[(3) - (1)].stringVector);
        (yyval.stringVector)->push_back( sstrip(*(yysemantic_stack_[(3) - (3)].stringVal)) );
        delete (yysemantic_stack_[(3) - (3)].stringVal);
      }
    break;

  case 8:

/* Line 678 of lalr1.cc  */
#line 187 "Parser.yy"
    {
        (yyval.calcnode) = new expression::Function(driver.symbols, *(yysemantic_stack_[(3) - (1)].stringVal));
        delete (yysemantic_stack_[(3) - (1)].stringVal);
      }
    break;

  case 9:

/* Line 678 of lalr1.cc  */
#line 192 "Parser.yy"
    {
        (yyval.calcnode) = new expression::Function(driver.symbols, *(yysemantic_stack_[(4) - (1)].stringVal), *(yysemantic_stack_[(4) - (3)].nodeVector));
        delete (yysemantic_stack_[(4) - (1)].stringVal);
        delete (yysemantic_stack_[(4) - (3)].nodeVector);
      }
    break;

  case 10:

/* Line 678 of lalr1.cc  */
#line 198 "Parser.yy"
    {
        (yyval.calcnode) = new expression::StringFunction(driver.symbols, *(yysemantic_stack_[(4) - (1)].stringVal), *(yysemantic_stack_[(4) - (3)].stringVector));
        delete (yysemantic_stack_[(4) - (1)].stringVal);
        delete (yysemantic_stack_[(4) - (3)].stringVector);
      }
    break;

  case 11:

/* Line 678 of lalr1.cc  */
#line 205 "Parser.yy"
    {
        (yyval.calcnode) = (yysemantic_stack_[(1) - (1)].calcnode);
      }
    break;

  case 12:

/* Line 678 of lalr1.cc  */
#line 209 "Parser.yy"
    {
        (yyval.calcnode) = (yysemantic_stack_[(1) - (1)].calcnode);
      }
    break;

  case 13:

/* Line 678 of lalr1.cc  */
#line 213 "Parser.yy"
    {
        (yyval.calcnode) = (yysemantic_stack_[(3) - (2)].calcnode);
      }
    break;

  case 14:

/* Line 678 of lalr1.cc  */
#line 217 "Parser.yy"
    {
        (yyval.calcnode) = (yysemantic_stack_[(1) - (1)].calcnode);
      }
    break;

  case 15:

/* Line 678 of lalr1.cc  */
#line 222 "Parser.yy"
    {
        (yyval.calcnode) = (yysemantic_stack_[(1) - (1)].calcnode);
      }
    break;

  case 16:

/* Line 678 of lalr1.cc  */
#line 226 "Parser.yy"
    {
        (yyval.calcnode) = new expression::Power((yysemantic_stack_[(3) - (1)].calcnode), (yysemantic_stack_[(3) - (3)].calcnode));
      }
    break;

  case 17:

/* Line 678 of lalr1.cc  */
#line 231 "Parser.yy"
    {
        (yyval.calcnode) = (yysemantic_stack_[(1) - (1)].calcnode);
      }
    break;

  case 18:

/* Line 678 of lalr1.cc  */
#line 235 "Parser.yy"
    {
        (yyval.calcnode) = (yysemantic_stack_[(2) - (2)].calcnode);
      }
    break;

  case 19:

/* Line 678 of lalr1.cc  */
#line 239 "Parser.yy"
    {
        (yyval.calcnode) = new expression::Negate((yysemantic_stack_[(2) - (2)].calcnode));
      }
    break;

  case 20:

/* Line 678 of lalr1.cc  */
#line 244 "Parser.yy"
    {
        (yyval.calcnode) = (yysemantic_stack_[(1) - (1)].calcnode);
      }
    break;

  case 21:

/* Line 678 of lalr1.cc  */
#line 248 "Parser.yy"
    {
        (yyval.calcnode) = new expression::Multiply((yysemantic_stack_[(3) - (1)].calcnode), (yysemantic_stack_[(3) - (3)].calcnode));
      }
    break;

  case 22:

/* Line 678 of lalr1.cc  */
#line 252 "Parser.yy"
    {
        (yyval.calcnode) = new expression::Divide((yysemantic_stack_[(3) - (1)].calcnode), (yysemantic_stack_[(3) - (3)].calcnode));
      }
    break;

  case 23:

/* Line 678 of lalr1.cc  */
#line 256 "Parser.yy"
    {
        (yyval.calcnode) = new expression::Modulo((yysemantic_stack_[(3) - (1)].calcnode), (yysemantic_stack_[(3) - (3)].calcnode));
      }
    break;

  case 24:

/* Line 678 of lalr1.cc  */
#line 261 "Parser.yy"
    {
        (yyval.calcnode) = (yysemantic_stack_[(1) - (1)].calcnode);
      }
    break;

  case 25:

/* Line 678 of lalr1.cc  */
#line 265 "Parser.yy"
    {
        (yyval.calcnode) = new expression::Add((yysemantic_stack_[(3) - (1)].calcnode), (yysemantic_stack_[(3) - (3)].calcnode));
      }
    break;

  case 26:

/* Line 678 of lalr1.cc  */
#line 269 "Parser.yy"
    {
        (yyval.calcnode) = new expression::Subtract((yysemantic_stack_[(3) - (1)].calcnode), (yysemantic_stack_[(3) - (3)].calcnode));
      }
    break;

  case 27:

/* Line 678 of lalr1.cc  */
#line 274 "Parser.yy"
    {
        (yyval.calcnode) = new expression::Assign(driver.symbols, *(yysemantic_stack_[(3) - (1)].stringVal), (yysemantic_stack_[(3) - (3)].calcnode));
        delete (yysemantic_stack_[(3) - (1)].stringVal);
      }
    break;

  case 28:

/* Line 678 of lalr1.cc  */
#line 279 "Parser.yy"
    {
        (yyval.calcnode) = new expression::Assign(driver.symbols, *(yysemantic_stack_[(3) - (1)].stringVal), (yysemantic_stack_[(3) - (3)].calcnode));
        delete (yysemantic_stack_[(3) - (1)].stringVal);
      }
    break;

  case 29:

/* Line 678 of lalr1.cc  */
#line 285 "Parser.yy"
    {
        driver.dump( std::cout );
        delete (yysemantic_stack_[(1) - (1)].stringVal);
      }
    break;

  case 30:

/* Line 678 of lalr1.cc  */
#line 290 "Parser.yy"
    { /* e.g. dump constants */
        enum symbol::TYPE sym_type = symbol::UNDEFINED;
        if      ( (*(yysemantic_stack_[(2) - (2)].stringVal)) == "constants" )
            sym_type = symbol::CONSTANT;
        else if ( (*(yysemantic_stack_[(2) - (2)].stringVal)) == "variables" )
            sym_type = symbol::VARIABLE;
        else if ( (*(yysemantic_stack_[(2) - (2)].stringVal)) == "functions" )
            sym_type = symbol::FUNCTION;

        driver.dump( std::cout, sym_type );

        delete (yysemantic_stack_[(2) - (1)].stringVal);
        delete (yysemantic_stack_[(2) - (2)].stringVal);
      }
    break;

  case 31:

/* Line 678 of lalr1.cc  */
#line 306 "Parser.yy"
    { /* e.g.  set output pretty */
        bool success = false;
        if (*(yysemantic_stack_[(3) - (2)].stringVal) == "output") {
          success = true;
          if        (*(yysemantic_stack_[(3) - (3)].stringVal) == "pretty") {
            Quantity::setPrintMode(Quantity::PRETTY_PRINT);
          } else if (*(yysemantic_stack_[(3) - (3)].stringVal) == "math") {
            Quantity::setPrintMode(Quantity::MATH_PRINT);
          } else if (*(yysemantic_stack_[(3) - (3)].stringVal) == "latex") {
            Quantity::setPrintMode(Quantity::LATEX_PRINT);
          } else if (*(yysemantic_stack_[(3) - (3)].stringVal) == "latex::oneline") {
            Quantity::setPrintMode(Quantity::LATEX_ONELINE_PRINT);
          } else if (*(yysemantic_stack_[(3) - (3)].stringVal) == "ugly") {
            Quantity::setPrintMode(Quantity::UGLY_PRINT);
          } else
            success = false;
        }

        delete (yysemantic_stack_[(3) - (1)].stringVal);
        delete (yysemantic_stack_[(3) - (2)].stringVal);
        delete (yysemantic_stack_[(3) - (3)].stringVal);

        if ( !success ) {
          error(yyloc, "invalid set command " );
          YYERROR;
        }
      }
    break;

  case 32:

/* Line 678 of lalr1.cc  */
#line 335 "Parser.yy"
    { /* e.g.  from physical::unit import * */
        bool success = true;
        if ( *(yysemantic_stack_[(4) - (3)].stringVal) == "import" )
          symbol::import( driver.symbols, *(yysemantic_stack_[(4) - (2)].stringVal), "*" );
        else if ( *(yysemantic_stack_[(4) - (3)].stringVal) == "clear" )
          symbol::clear(driver.symbols, *(yysemantic_stack_[(4) - (2)].stringVal), "*" );
        else
          success = false;

        delete (yysemantic_stack_[(4) - (1)].stringVal);
        delete (yysemantic_stack_[(4) - (2)].stringVal);
        delete (yysemantic_stack_[(4) - (3)].stringVal);

        if ( !success ) {
          error(yyloc, "invalid from command " );
          YYERROR;
        }
      }
    break;

  case 33:

/* Line 678 of lalr1.cc  */
#line 354 "Parser.yy"
    { /* e.g.  from physical::unit import * to myunits */
        bool success = true;
        if ( *(yysemantic_stack_[(6) - (3)].stringVal) == "import" && *(yysemantic_stack_[(6) - (5)].stringVal) == "to" )
          symbol::import( driver.symbols, *(yysemantic_stack_[(6) - (2)].stringVal), "*", *(yysemantic_stack_[(6) - (6)].stringVal) );
        else
          success = false;

        delete (yysemantic_stack_[(6) - (1)].stringVal);
        delete (yysemantic_stack_[(6) - (2)].stringVal);
        delete (yysemantic_stack_[(6) - (3)].stringVal);
        delete (yysemantic_stack_[(6) - (5)].stringVal);
        delete (yysemantic_stack_[(6) - (6)].stringVal);

        if ( !success ) {
          error(yyloc, "invalid from command " );
          YYERROR;
        }
      }
    break;

  case 34:

/* Line 678 of lalr1.cc  */
#line 373 "Parser.yy"
    { /* e.g.  from physical import 'element::.*' */
        bool success = true;
        if ( *(yysemantic_stack_[(4) - (3)].stringVal) == "import" )
          symbol::import( driver.symbols, *(yysemantic_stack_[(4) - (2)].stringVal), sstrip(*(yysemantic_stack_[(4) - (4)].stringVal)) );
        else if ( *(yysemantic_stack_[(4) - (3)].stringVal) == "clear" )
          symbol::clear(driver.symbols, *(yysemantic_stack_[(4) - (2)].stringVal), sstrip(*(yysemantic_stack_[(4) - (4)].stringVal)) );
        else
          success = false;

        delete (yysemantic_stack_[(4) - (1)].stringVal);
        delete (yysemantic_stack_[(4) - (2)].stringVal);
        delete (yysemantic_stack_[(4) - (3)].stringVal);
        delete (yysemantic_stack_[(4) - (4)].stringVal);

        if ( !success ) {
          error(yyloc, "invalid from command " );
          YYERROR;
        }
      }
    break;

  case 35:

/* Line 678 of lalr1.cc  */
#line 393 "Parser.yy"
    { /* e.g.  from physical::unit import 'element::.*' to myelements */
        bool success = true;
        if ( *(yysemantic_stack_[(6) - (3)].stringVal) == "import" && *(yysemantic_stack_[(6) - (5)].stringVal) == "to" )
          symbol::import( driver.symbols, *(yysemantic_stack_[(6) - (2)].stringVal), sstrip(*(yysemantic_stack_[(6) - (4)].stringVal)), *(yysemantic_stack_[(6) - (6)].stringVal) );
        else
          success = false;

        delete (yysemantic_stack_[(6) - (1)].stringVal);
        delete (yysemantic_stack_[(6) - (2)].stringVal);
        delete (yysemantic_stack_[(6) - (3)].stringVal);
        delete (yysemantic_stack_[(6) - (4)].stringVal);
        delete (yysemantic_stack_[(6) - (5)].stringVal);
        delete (yysemantic_stack_[(6) - (6)].stringVal);

        if ( !success ) {
          error(yyloc, "invalid from command " );
          YYERROR;
        }
      }
    break;

  case 36:

/* Line 678 of lalr1.cc  */
#line 414 "Parser.yy"
    { /* e.g. clear * */
        symbol::clear( driver.symbols, "", "*" );
        delete (yysemantic_stack_[(2) - (1)].stringVal);
      }
    break;

  case 37:

/* Line 678 of lalr1.cc  */
#line 419 "Parser.yy"
    { /* e.g. clear physcal::unit::m */
        symbol::clear( driver.symbols, *(yysemantic_stack_[(2) - (2)].stringVal), "" );
        delete (yysemantic_stack_[(2) - (1)].stringVal);
        delete (yysemantic_stack_[(2) - (2)].stringVal);
      }
    break;

  case 38:

/* Line 678 of lalr1.cc  */
#line 425 "Parser.yy"
    { /* e.g. clear 'physical::element::.*' */
        symbol::clear( driver.symbols, "", sstrip(*(yysemantic_stack_[(2) - (2)].stringVal)) );
        delete (yysemantic_stack_[(2) - (1)].stringVal);
        delete (yysemantic_stack_[(2) - (2)].stringVal);
      }
    break;

  case 39:

/* Line 678 of lalr1.cc  */
#line 432 "Parser.yy"
    {
        std::cerr << "just hit CTL-C!" << std::endl;
        delete (yysemantic_stack_[(1) - (1)].stringVal);
        /* std::exit(EXIT_SUCCESS); */
      }
    break;

  case 42:

/* Line 678 of lalr1.cc  */
#line 440 "Parser.yy"
    {
        bison_parser_help();
        delete (yysemantic_stack_[(1) - (1)].stringVal);
      }
    break;

  case 52:

/* Line 678 of lalr1.cc  */
#line 459 "Parser.yy"
    {
        driver.expressions.push_back((yysemantic_stack_[(3) - (2)].calcnode));
      }
    break;

  case 53:

/* Line 678 of lalr1.cc  */
#line 463 "Parser.yy"
    {
        driver.expressions.push_back((yysemantic_stack_[(3) - (2)].calcnode));
      }
    break;



/* Line 678 of lalr1.cc  */
#line 1077 "pregen-parser/Parser.cpp"
	default:
          break;
      }
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[0] = yylloc;
    if (yyerrstatus_ == 3)
      {
	/* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

	if (yychar <= yyeof_)
	  {
	  /* Return failure if at end of input.  */
	  if (yychar == yyeof_)
	    YYABORT;
	  }
	else
	  {
	    yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
	    yychar = yyempty_;
	  }
      }

    /* Else will try to reuse lookahead token after shifting the error
       token.  */
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;

    yyerror_range[0] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (yyn != yypact_ninf_)
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	YYABORT;

	yyerror_range[0] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[1] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyempty_)
      yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval, &yylloc);

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (yystate_stack_.height () != 1)
      {
	yydestruct_ ("Cleanup: popping",
		   yystos_[yystate_stack_[0]],
		   &yysemantic_stack_[0],
		   &yylocation_stack_[0]);
	yypop_ ();
      }

    return yyresult;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (int yystate, int tok)
  {
    std::string res;
    YYUSE (yystate);
#if YYERROR_VERBOSE
    int yyn = yypact_[yystate];
    if (yypact_ninf_ < yyn && yyn <= yylast_)
      {
	/* Start YYX at -YYN if negative to avoid negative indexes in
	   YYCHECK.  */
	int yyxbegin = yyn < 0 ? -yyn : 0;

	/* Stay within bounds of both yycheck and yytname.  */
	int yychecklim = yylast_ - yyn + 1;
	int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
	int count = 0;
	for (int x = yyxbegin; x < yyxend; ++x)
	  if (yycheck_[x + yyn] == x && x != yyterror_)
	    ++count;

	// FIXME: This method of building the message is not compatible
	// with internationalization.  It should work like yacc.c does it.
	// That is, first build a string that looks like this:
	// "syntax error, unexpected %s or %s or %s"
	// Then, invoke YY_ on this string.
	// Finally, use the string as a format to output
	// yytname_[tok], etc.
	// Until this gets fixed, this message appears in English only.
	res = "syntax error, unexpected ";
	res += yytnamerr_ (yytname_[tok]);
	if (count < 5)
	  {
	    count = 0;
	    for (int x = yyxbegin; x < yyxend; ++x)
	      if (yycheck_[x + yyn] == x && x != yyterror_)
		{
		  res += (!count++) ? ", expecting " : " or ";
		  res += yytnamerr_ (yytname_[x]);
		}
	  }
      }
    else
#endif
      res = YY_("syntax error");
    return res;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const signed char Parser::yypact_ninf_ = -15;
  const signed char
  Parser::yypact_[] =
  {
       -15,     1,   -15,   -15,   -15,    42,   -15,    -4,    19,   -15,
      37,    22,    17,    17,    38,   -15,   -15,   -15,   -15,     5,
     -15,   -15,    51,    16,     3,   -15,   -15,   -15,   -15,     3,
     -15,    27,    49,   -15,    43,    48,   -15,   -15,   -15,    41,
     -15,   -15,    45,    38,    38,    38,    38,   -15,    38,    38,
     -15,   -15,   -15,   -15,   -15,   -15,    59,    60,    56,    56,
     -15,   -15,    33,   -15,   -15,   -15,   -15,   -15,   -15,   -15,
      38,   -15,    66,   -15,    77,    78,    56,   -15,    79,    80,
     -15,   -15
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
        49,     0,     1,    46,     2,     3,    39,    29,     0,    42,
       0,     0,     0,     0,     0,    45,    11,    12,    14,    15,
      17,    20,    24,     0,     0,    40,    41,    43,    44,     0,
      50,     0,     0,    30,     0,     0,    38,    37,    36,     3,
      19,    18,     0,     0,     0,     0,     0,    48,     0,     0,
      47,    53,    52,    51,     6,     8,     0,     0,     4,    27,
      28,    31,     0,    13,    16,    21,    22,    23,    26,    25,
       0,     9,     0,    10,    34,    32,     5,     7,     0,     0,
      35,    33
  };

  /* YYPGOTO[NTERM-NUM].  */
  const signed char
  Parser::yypgoto_[] =
  {
       -15,   -15,   -15,   -15,   -15,   -15,   -15,    69,    30,   -15,
     -14,    55,   -15,   -15,   -15,   -15,   -15,    87,    21,   -15
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  Parser::yydefgoto_[] =
  {
        -1,    16,    17,    56,    57,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    50,    51,     1
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -1;
  const unsigned char
  Parser::yytable_[] =
  {
        42,     2,    33,    47,     3,     4,     3,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    47,    58,    59,     3,
      14,     4,    43,    39,    15,    34,    15,    36,    37,    48,
      49,     4,    54,    39,    68,    69,    14,    38,    74,    15,
      12,    13,     4,    35,    39,    52,    14,    55,    75,    61,
      53,    12,    13,     4,    62,     5,    76,    14,    48,    49,
      31,    31,    12,    13,    32,    63,    44,    45,    14,    48,
      49,    77,    46,    64,    65,    66,    67,    70,    72,    71,
      73,    40,    41,    78,    79,    80,    81,    60,    30
  };

  /* YYCHECK.  */
  const unsigned char
  Parser::yycheck_[] =
  {
        14,     0,     6,     0,     3,     4,     3,     6,     7,     8,
       9,    10,    11,    12,    13,    14,     0,    31,    32,     3,
      19,     4,    17,     6,    23,     6,    23,     5,     6,    13,
      14,     4,     5,     6,    48,    49,    19,    15,     5,    23,
      13,    14,     4,     6,     6,    24,    19,    20,    15,     6,
      29,    13,    14,     4,     6,     6,    70,    19,    13,    14,
      19,    19,    13,    14,    22,    20,    15,    16,    19,    13,
      14,     5,    21,    43,    44,    45,    46,    18,    18,    20,
      20,    12,    13,     6,     6,     6,     6,    32,     1
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    43,     0,     3,     4,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    19,    23,    25,    26,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    19,    22,     6,     6,     6,     5,     6,    15,     6,
      31,    31,    34,    17,    15,    16,    21,     0,    13,    14,
      41,    42,    42,    42,     5,    20,    27,    28,    34,    34,
      35,     6,     6,    20,    32,    32,    32,    32,    34,    34,
      18,    20,    18,    20,     5,    15,    34,     5,     6,     6,
       6,     6
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  Parser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,    45,    43,    42,    47,    94,    44,    40,
      41,    37,    61,    59
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    24,    25,    26,    27,    27,    28,    28,    29,    29,
      29,    30,    30,    30,    30,    31,    31,    32,    32,    32,
      33,    33,    33,    33,    34,    34,    34,    35,    35,    36,
      36,    37,    38,    38,    38,    38,    39,    39,    39,    40,
      40,    40,    40,    40,    40,    41,    41,    42,    42,    43,
      43,    43,    43,    43
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     1,     1,     1,     3,     1,     3,     3,     4,
       4,     1,     1,     3,     1,     1,     3,     1,     2,     2,
       1,     3,     3,     3,     1,     3,     3,     3,     3,     1,
       2,     3,     4,     6,     4,     6,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       2,     3,     3,     3
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const Parser::yytname_[] =
  {
    "\"end of file\"", "error", "$undefined", "\"end of line\"",
  "\"double\"", "\"string\"", "\"identifier\"", "\"quit keyword\"",
  "\"dump keyword\"", "\"set keyword\"", "\"help keyword\"",
  "\"from keyword\"", "\"clear keyword\"", "'-'", "'+'", "'*'", "'/'",
  "'^'", "','", "'('", "')'", "'%'", "'='", "';'", "$accept", "literal",
  "variable", "expr_list", "string_list", "function", "atomexpr",
  "powexpr", "factor", "term", "expr", "assignment", "dump_command",
  "set_command", "from_command", "clear_command", "command", "eos", "eoa",
  "start", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        43,     0,    -1,     4,    -1,     6,    -1,    34,    -1,    27,
      18,    34,    -1,     5,    -1,    28,    18,     5,    -1,     6,
      19,    20,    -1,     6,    19,    27,    20,    -1,     6,    19,
      28,    20,    -1,    25,    -1,    26,    -1,    19,    34,    20,
      -1,    29,    -1,    30,    -1,    30,    17,    32,    -1,    31,
      -1,    14,    31,    -1,    13,    31,    -1,    32,    -1,    33,
      15,    32,    -1,    33,    16,    32,    -1,    33,    21,    32,
      -1,    33,    -1,    34,    14,    34,    -1,    34,    13,    34,
      -1,     6,    22,    34,    -1,     6,    22,    35,    -1,     8,
      -1,     8,     6,    -1,     9,     6,     6,    -1,    11,     6,
       6,    15,    -1,    11,     6,     6,    15,     6,     6,    -1,
      11,     6,     6,     5,    -1,    11,     6,     6,     5,     6,
       6,    -1,    12,    15,    -1,    12,     6,    -1,    12,     5,
      -1,     7,    -1,    36,    -1,    37,    -1,    10,    -1,    38,
      -1,    39,    -1,    23,    -1,     3,    -1,    41,    -1,     0,
      -1,    -1,    43,    41,    -1,    43,    40,    42,    -1,    43,
      35,    42,    -1,    43,    34,    42,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned char
  Parser::yyprhs_[] =
  {
         0,     0,     3,     5,     7,     9,    13,    15,    19,    23,
      28,    33,    35,    37,    41,    43,    45,    49,    51,    54,
      57,    59,    63,    67,    71,    73,    77,    81,    85,    89,
      91,    94,    98,   103,   110,   115,   122,   125,   128,   131,
     133,   135,   137,   139,   141,   143,   145,   147,   149,   151,
     152,   155,   159,   163
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   151,   151,   156,   162,   167,   173,   179,   186,   191,
     197,   204,   208,   212,   216,   221,   225,   230,   234,   238,
     243,   247,   251,   255,   260,   264,   268,   273,   278,   284,
     289,   305,   334,   353,   372,   392,   413,   418,   424,   431,
     437,   438,   439,   444,   445,   448,   449,   452,   453,   455,
     456,   457,   458,   462
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "):" << std::endl;
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    21,     2,     2,
      19,    20,    15,    14,    18,    13,     2,    16,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    23,
       2,    22,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    17,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 88;
  const int Parser::yynnts_ = 20;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 2;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 24;

  const unsigned int Parser::yyuser_token_number_max_ = 267;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


/* Line 1054 of lalr1.cc  */
#line 52 "Parser.yy"
} } } } // runtime::physical::calc::detail

/* Line 1054 of lalr1.cc  */
#line 1571 "pregen-parser/Parser.cpp"


/* Line 1056 of lalr1.cc  */
#line 469 "Parser.yy"
 /*** Additional Code ***/

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


