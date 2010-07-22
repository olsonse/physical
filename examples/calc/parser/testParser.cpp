#include <physical/calc/Driver.h>
#include <physical/calc/except.h>

#include <iostream>

runtime::physical::calc::Driver calc;

using runtime::physical::system::si;

int main(int argc, char *argv[]) {
  try {
    calc.addMathLib();
    calc.addPhysicalUnits();

    const char * input = argc>1 ? argv[1] : "from physical::unit import *; 10*m";

    if (argc>1)
      std::cout << "results of argv[1]" << std::endl;
    try {
      runtime::physical::Quantity result = calc.eval(input);
      std::cout << '\t' << result << std::endl;
    } catch (runtime::physical::calc::no_result) {
      std::cout << "no results" << std::endl;
    }

    input = argc > 2 ? argv[2] : "from physical::unit import *; 10*m/s";

    if (argc>2)
      std::cout << "results of argv[2] in units of physical::constant::c" << std::endl;
    try {
      runtime::physical::Quantity::coeff_type res =
        calc.eval(input, runtime::physical::constant::c<si>::value());
      std::cout << '\t' << res << std::endl;
    } catch (runtime::physical::calc::no_result) {
      std::cout << "no results" << std::endl;
    }
  } catch (runtime::physical::exception & e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}

