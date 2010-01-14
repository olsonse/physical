#ifndef  PHYSICAL_CALC_CALC_H
#define  PHYSICAL_CALC_CALC_H

#include <physical/runtime.h>
#include <physical/calc/symbol.h>
#include <physical/calc/units.h>
#include <physical/calc/math.h>

#include <boost/spirit.hpp>

#include <sstream>
#include <iomanip>

namespace runtime { namespace physical {
    namespace calc {

        struct no_result : physical::exception {
            typedef physical::exception super;
            no_result(const std::string & err = "") : super(err) {}
        };

        struct syntax_error : physical::exception {
            typedef physical::exception super;
            syntax_error(      std::string::iterator stop,
                         const std::string & msg = "") :
                super(msg), stop(stop) {}
            std::string::iterator stop;
        };



        /** Base class to be inherited (before BaseCalc) by boost::spirit
         * based grammar/parsers. */
        template <class Engin>
        struct BaseBoostCalc {
            Engin & engine;

            BaseBoostCalc(Engin & engine) : engine(engine) {}

            /** Parse a single statement contained within a iterator 'stream'.
             * */
            Quantity parse_statement( std::string::iterator & first,
                            const std::string::iterator last,
                            bool & finished,
                            bool & result_set) throw (physical::exception) {
                using boost::spirit::parse;
                using boost::spirit::space_p;
                using boost::spirit::parse_info;

                engine.reset_result_set();

                parse_info<std::string::iterator> info;
                info = parse(first, last, engine, space_p);

                if (!info.hit)
                    throw syntax_error(info.stop);
                if (!info.full) {
                    // Keep track of where to start
                    // parsing the next statement.
                    first = info.stop;
                    finished = false;
                } else
                    finished = true;

                result_set = engine.result_set();
                if (!result_set)
                    return Quantity();
                else
                    return engine.result();
            }
        };

        /** The base class for all physical calculator types. */
        template<class sub>
        struct BaseCalc {
            symbol::table symbols;
            void addPhysicalUnits() { physical::calc::addPhysicalUnits(symbols); }
            void addMathLib() { physical::calc::addMathLib(symbols); }

            static BaseCalc & instance() {
                static BaseCalc * calc = new sub;
                return *calc;
            }

            /** Parse a input string and return the results in units of
             * q_units_out.
             *
             * If the results do not match the base units of the q_units_out
             * parameter, then a UnitsMismatchR exception is thrown.
             *
             * @return the coefficient of the resulting physical::Quantity in
             * units of q_units_out (result/q_units_out).
             * */
            Quantity::coeff_type parse(const std::string & in, const Quantity & q_units_out) {
                Quantity q = parse(in);
                return q.assertMatch(q_units_out).coeff / q_units_out.coeff;
            }
        
            /** Parse a input string and check the results against the units of
             * q_check.
             *
             * If the results do not match the base units of the q_check
             * parameter, then a UnitsMismatchR exception is thrown.
             *
             * @return the coefficient of the resulting physical::Quantity.
             * */
            Quantity::coeff_type parse_w_check_only(const std::string & in, const Quantity & q_check) {
                Quantity q = parse(in);
                return q.assertMatch(q_check).coeff;
            }

            Quantity parse(std::string s) throw (physical::exception) {
                std::string::iterator first = s.begin();
                bool finished = false;
                bool result_set = false;
                Quantity result;
                do {
                    try {
                        result = static_cast<sub&>(*this).parse_statement(first, s.end(), finished, result_set);
                    } catch (syntax_error & e) {
                        // Display a caret that points to the position where the error
                        // was detected.
                        std::ostringstream outs;
                        int w = e.stop - s.begin();
                        outs << s << '\n'
                             << std::setw(w) << (w ? " " : "") << "^ error\n";
                        throw syntax_error(e.stop, outs.str());
                    }
                } while(!finished);
                if (!result_set)
                    throw no_result();
                else
                    return result;
            }

            void exec(std::string s) throw (physical::exception) {
                try {
                    parse(s);
                } catch (no_result) {
                }
            }
        };
    } /* namespace calc */
}} /* namespace runtime::physical */

#endif // PHYSICAL_CALC_CALC_H
