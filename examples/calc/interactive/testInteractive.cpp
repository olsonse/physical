/** \file This file was originally intended to be a test program for the
 * calculator grammar engine, but has ended up being a fairly capable units
 * calculator.  It can function as a simple calculator with variables,
 * constants, and (at-compile-time-added) mathematical unary functions.
 *
 * Perhaps it might even rival with GNU units. :-)
 *
 * - 2007-2009 Spencer E. Olson
 * */

/** Intro message displayed in interactive mode. */
const char * opening_msg =
"physical::calculator: \n"
"Perhaps it might even rival with GNU units. :-)\n"
"\n"
"- 2007-2009 Spencer E. Olson\n"
"  type 'help' for usage information.\n\n";

#include <physical/calc/infix.h>
#include <set>
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
#  endif /* defined(HAVE_READLINE_HISTORY_H) */
  /* no history */
#endif /* HAVE_READLINE_HISTORY */








physical::calc::InfixCalc calc;

typedef physical::calc::symbol sym;

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

using physical::calc::symbol;

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

int main() {
#ifdef HAVE_LIBREADLINE
    rl_completion_entry_function = variable_completer;
#endif

    bool interactive = true;
    if (!isatty(0) || !isatty(1))
        interactive = false;

    calc.addMathLib();
    calc.addPhysicalUnits();

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

        // Read one line of text and parse it. If the parser does not consume
        // the entire string, keep parsing the same string until an error occurs
        // or the string is consumed. Then go back and read another string.
        std::string::iterator first = line.begin();
        bool finished = false;
        bool result_set = false;
        do {
            try {
                physical::Quantity result = calc.parse_statement(first, line.end(), finished, result_set);
                if (result_set)
                    std::cout << result << std::endl;
            } catch (physical::calc::symbol_error & e) {
                std::cout << e.what() << std::endl;
                break;
            } catch (physical::calc::syntax_error & e) {
                // Display a caret that points to the position where the error
                // was detected.
                std::cerr << std::setw(e.stop - line.begin() + 3) << " " << "^ error\n";
                break;
            } catch (physical::exception & e) {
                std::cout << e.what() << std::endl;
                break;
            }
        } while(!finished);
    }
    return 0;
}

