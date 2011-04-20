/** \file
 * Demonstrates how the expression parser can be used to create an abstract
 * expression tree that can be evaluated at some later time and can depend on
 * valued modified external to the Parser.
 */

#include <physical/calc/Driver.h>
#include <physical/calc/except.h>

#include <iostream>

namespace {
  runtime::physical::calc::Driver calc;
  using runtime::physical::Quantity;

  struct Something {
    /* TYPEDEFS */
    enum DTYPE {
      A,
      B,
      C
    };

    struct Value {
      double a,b,c;
      Value() : a(0.0), b(0.0), c(0.0) { }
    };

    Value values[2];

    /** Instance of this global data. */
    static Something & instance() {
      static Something s;
      return s;
    }

    /** Simple user command to specify precision on std::cout. */
    static Quantity P( const Quantity & indx, const Quantity & vname ) {
      const int vtype = vname.getCoeff<int>();

      switch ( indx.getCoeff<int>() ) {
        case 0:
          switch ( vtype ) {
            case 0:
              return Quantity( instance().values[0].a );
            case 1:
              return Quantity( instance().values[0].b );
            case 2:
              return Quantity( instance().values[0].c );
            default:
              throw runtime::physical::exception(
                "invalid argument.  Argument 1 must be one of 0,1,2" );
          }
        case 1:
          switch ( vtype ) {
            case 0:
              return Quantity( instance().values[1].a );
            case 1:
              return Quantity( instance().values[1].b );
            case 2:
              return Quantity( instance().values[1].c );
            default:
              throw runtime::physical::exception(
                "invalid argument.  Argument 1 must be one of 0,1,2" );
          }

        default:
          throw runtime::physical::exception(
            "invalid argument.  Argument 0 must either be 0 or 1" );
      }
    }

    /** Simple user command to specify precision on std::cout. */
    static Quantity setP( const std::vector<Quantity> & args ) {
      if ( args.size() != 3 )
        throw runtime::physical::exception( "setP:  requires three arguments" );

      const int vtype = args[1].getCoeff<int>();
      const double v = args[2].getCoeff<double>();

      switch ( args[0].getCoeff<int>() ) {
        case 0:
          switch ( vtype ) {
            case Something::A:
              return Quantity( instance().values[0].a = v );
            case Something::B:
              return Quantity( instance().values[0].b = v );
            case Something::C:
              return Quantity( instance().values[0].c = v );
            default:
              throw runtime::physical::exception(
                "invalid argument.  Argument 1 must be one of 0,1,2" );
          }

        case 1:
          switch ( vtype ) {
            case Something::A:
              return Quantity( instance().values[1].a = v );
            case Something::B:
              return Quantity( instance().values[1].b = v );
            case Something::C:
              return Quantity( instance().values[1].c = v );
            default:
              throw runtime::physical::exception(
                "invalid argument.  Argument 1 must be one of 0,1,2" );
          }

        default:
          throw runtime::physical::exception(
            "invalid argument.  Argument 0 must either be 0 or 1" );
      }
    }


    static void registerFunctions( runtime::physical::calc::Driver & c ) {
      c.symbols["P"] = & Something::P;
      c.symbols["setP"] = & Something::setP;
      c.symbols["A"] = Quantity( double(Something::A) );
      c.symbols["B"] = Quantity( double(Something::B) );
      c.symbols["C"] = Quantity( double(Something::C) );
    }
  };
}

int main(int argc, char *argv[]) {
  try {
    calc.addMathLib();
    calc.addPhysicalUnits();
    Something::registerFunctions( calc );

    calc.eval("from physical::constant import *;\n");
    calc.eval("from physical::unit import *;\n");
    calc.eval("from physical import 'unit::pi';\n");
    calc.eval("from physical import 'element::.*';\n");

    const char * input = argc>1 ? argv[1] : "10*m";

    if (argc>1)
      std::cout << "results of argv[1]" << std::endl;

    try {
      bool result = calc.parse( input );
      typedef runtime::physical::calc::Driver::ExpressionVector EVector;
      EVector expressions = calc.expressions;
      calc.expressions.clear();

      std::cout << "interrupting calculation:  "
                << calc.eval("some_variable = 10*sigma_SB")
                << "\n\n\n" << std::flush;

      if ( result ) {
        std::cout << "Result available using pre-built "
                     "abstract expression tree...\n" << std::flush;

        try {
          for ( unsigned int i = 0u; i < expressions.size(); ++i ) {

            /* should we print the expression tree? */
            expressions[i]->print(
              std::cout << "\ntree ("<< (i+1)
                                     << " of "
                                     << expressions.size() << "):\n"
            ) << '\n';

            /* modify Something AFTER the expression tree is built, but
             * BEFORE it is evaluated. */
            Something::instance().values[1].b = 52.42;

            std::cout << "evaluated:  " << expressions[i]->evaluate()
                      << "\n---------------------------\n"
                      << std::flush;
          }
        } catch ( const runtime::physical::exception & e ) {
          std::cerr << e.what() << std::endl;
        }

      } else {
        std::cout << "Result NOT available" << std::endl;
      }

      runtime::physical::calc::Driver::clearExpressions( expressions );
    } catch ( const runtime::physical::calc::syntax_error & e ) {
      std::cerr << e.what() << std::endl;
    }

  } catch ( const runtime::physical::exception & e ) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}

