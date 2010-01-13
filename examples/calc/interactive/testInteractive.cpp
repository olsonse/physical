/** \file This file was originally intended to be a test program for the
 * calculator grammar engine, but has ended up being a fairly capable units
 * calculator.  It can function as a simple calculator with variables,
 * constants, and (at-compile-time-added) mathematical unary functions.
 *
 * Perhaps it might even rival with GNU units. :-)
 *
 * - 2007-2009 Spencer E. Olson
 * */

/* version info updated 23 june 2009 */

#ifndef PHYSICAL_VERSION
#  define PHYSICAL_VERSION ""
#endif

/** Intro message displayed in interactive mode. */
const char * opening_msg =
"physical::calculator: " PHYSICAL_VERSION " compiled on " __DATE__ "\n"
"Perhaps it might even rival with GNU units. :-)\n"
"\n"
"- 2007-2009 Spencer E. Olson\n"
"  type 'help' for usage information.\n\n";

#include <physical/calc/infix.h>


#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <fstream>
#include <cstdlib>

#include <unistd.h>

#ifdef HAVE_LIBREADLINE
#  if defined(HAVE_READLINE_READLINE_H)
#    include <readline/readline.h>
#  elif defined(HAVE_READLINE_H)
#    include <readline.h>
#  else /* !defined(HAVE_READLINE_H) */
extern char *readline ();
#  endif /* !defined(HAVE_READLINE_H) */
char *cmdline = NULL;
#else /* !defined(HAVE_READLINE_READLINE_H) */
  /* no readline */


/* I'll define my own readline function */
char * readline(const std::string & prompt) {
    std::cout << prompt << std::flush;
    std::string ins;
    std::getline(std::cin, ins);
    if (!std::cin)
        return NULL;
    char * s = (char*)malloc(ins.length()+1);
    strcpy(s,ins.c_str());
    return s;
}

#endif /* HAVE_LIBREADLINE */

#ifdef HAVE_READLINE_HISTORY
#  if defined(HAVE_READLINE_HISTORY_H)
#    include <readline/history.h>
#  elif defined(HAVE_HISTORY_H)
#    include <history.h>
#  else /* !defined(HAVE_HISTORY_H) */
extern void add_history ();
extern int write_history ();
extern int read_history ();
extern void stifle_history ();
#  endif /* defined(HAVE_READLINE_HISTORY_H) */
  /* no history */
#endif /* HAVE_READLINE_HISTORY */








runtime::physical::calc::InfixCalc calc;

typedef runtime::physical::calc::symbol sym;

template <class T>
void fill_completion_container(const std::string & text,
                               T & matches,
                               bool recursion = false) {
    /* find the location of the last '::' */
    size_t ns_loc = text.rfind("::");
    if (ns_loc == std::string::npos)
        ns_loc = 0;
    else
        ns_loc += 2;
    /* initialize completion generator. */
    matches.clear();
    sym::table::const_iterator i = calc.symbols.lower_bound(text);
    while (i != calc.symbols.end() &&
           i->first.compare(0,text.size(), text) == 0) {
        /* don't transcend into additional namespaces and try not to add
         * duplicate sub-namespaces.  */
        size_t pos = i->first.find("::", ns_loc);
        if (pos != std::string::npos)
            pos += 2;
        matches.insert(i->first.substr(0, pos));
        ++i;
    }

    if (recursion && matches.size() == 0)
        matches.insert(text);
    else if (matches.size() == 1 &&
             matches.begin()->compare(matches.begin()->size()-2,2,"::")==0) {
        std::string txt = *matches.begin();
        fill_completion_container(txt, matches, true);
    }
}

char * variable_completer(const char * text, int state) {
    static std::set<std::string> matches;
    static std::set<std::string>::const_iterator m_i = matches.end();

    if (state == 0) {
        fill_completion_container(text, matches);
        m_i = matches.begin();
    }

    if (m_i == matches.end())
        return NULL;

    std::string txt = *m_i;
    ++m_i;
    return strncpy((char*)malloc(txt.length()+1), txt.c_str(), txt.length() + 1);
}

using runtime::physical::calc::symbol;

char * get_line(const bool & interactive) {
    if (interactive)
        return readline(">  ");
    else {
        std::string ins;
        std::getline(std::cin, ins);
        if (!std::cin)
            return NULL;
        char * s = (char*)malloc(ins.length()+1);
        strcpy(s,ins.c_str());
        return s;
    }
}


/** Implementation of string.split(delim) in c++. */
std::vector<std::string> &split( const std::string &s, char delim,
                                 std::vector<std::string> &elems ) {
  std::stringstream ss(s);
  std::string item;
  while( std::getline(ss, item, delim) ) {
    elems.push_back(item);
  }
  return elems;
}

/** Implementation of string.split(delim) in c++. */
std::vector<std::string> split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  return split(s, delim, elems);
}

/** Execute all lines from a stream */
template < typename Functor >
void foreach_line( std::istream & in, Functor & f ) {
  std::string line;
  while( std::getline(in, line, '\n') ) {
    f(line);
  }
}


struct Executor {
  typedef runtime::physical::calc::InfixCalc InfixCalc;
  typedef runtime::physical::Quantity        Quantity;

  InfixCalc & calc;
  std::ostream & out;

  Executor( InfixCalc & calc, std::ostream & out ) : calc(calc), out(out) { }

  void operator() ( std::string & line ) {
    this->operator() ( line.begin(), line.end() );
  }

  void operator() ( const std::string::iterator & begin,
                    const std::string::iterator & end ) {
    // Read one line of text and parse it. If the parser does not consume
    // the entire string, keep parsing the same string until an error occurs
    // or the string is consumed. Then go back and read another string.
    std::string::iterator first = begin;
    bool finished = false;
    bool result_set = false;
    do {
        try {
            Quantity result
              = calc.parse_statement(first, end, finished, result_set);

            if (result_set)
                out << result << std::endl;
        } catch (runtime::physical::calc::symbol_error & e) {
            out << e.what() << std::endl;
            break;
        } catch (runtime::physical::calc::syntax_error & e) {
            // Display a caret that points to the position where the error
            // was detected.
            std::cerr << std::setw(e.stop - begin + 3) << " " << "^ error\n";
            break;
        } catch (runtime::physical::exception & e) {
            out << e.what() << std::endl;
            break;
        }
    } while(!finished);
  }
};



int main( int argc, char * argv[] ) {
    calc.addMathLib();
    calc.addPhysicalUnits();
    Executor executor( calc, std::cout );

    std::string HOME( getenv("HOME") ? getenv("HOME") : "/tmp/" );
    std::string PROG( * split(argv[0], '/').rbegin() );
    { /* try and read initial commands saved by the user. */
      std::ifstream frc( (HOME + "/." + PROG + "rc").c_str() );
      foreach_line( frc, executor );
    }

#ifdef HAVE_READLINE_HISTORY
    std::string history_file = HOME + "/." + PROG + "_history";

    read_history(history_file.c_str());

    stifle_history(1000); // we'll only allow up to 1000 lines of history
#endif

#ifdef HAVE_LIBREADLINE
    rl_completion_entry_function = variable_completer;
#endif

    bool interactive = true;
    if (!isatty(0) || !isatty(1))
        interactive = false;

    if (interactive)
        /* spit out a tiny little message. */
        std::cout << opening_msg << std::flush;

    char * line_cstr = NULL;
    while ((line_cstr = get_line(interactive)) != NULL) {
        std::string line(line_cstr);
        free(line_cstr);

#ifdef HAVE_READLINE_HISTORY
        add_history(line.c_str());
#endif
        executor( line );
    }

#ifdef HAVE_READLINE_HISTORY
    write_history(history_file.c_str());
#endif

    return 0;
}

