#include <physical/calc/infix.h>

#include <iostream>

using namespace runtime; /* strip runtime:: prefix off of physical::* */
physical::calc::InfixCalc calc;

typedef physical::calc::symbol sym;

using physical::calc::symbol;

int main(int argc, char *argv[]) {
    try {
        calc.addMathLib();
        calc.addPhysicalUnits();

        const char * input = argc>1 ? argv[1] : "from physical::unit import *; 10*m";

        if (argc>1)
            std::cout << "results of argv[1]" << std::endl;
        try {
            physical::Quantity result = calc.parse(input);
            std::cout << '\t' << result << std::endl;
        } catch (physical::calc::no_result) {
            std::cout << "no results" << std::endl;
        }

        input = argc > 2 ? argv[2] : "from physical::unit import *; 10*m/s";

        if (argc>2)
            std::cout << "results of argv[2] in units of physical::constant::c" << std::endl;
        try {
            physical::Quantity::coeff_type res = calc.parse(input, physical::constant::c);
            std::cout << '\t' << res << std::endl;
        } catch (physical::calc::no_result) {
            std::cout << "no results" << std::endl;
        }
    } catch (physical::exception & e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

