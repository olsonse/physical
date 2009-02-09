/** \file
 * Example of using only the data from the physical library.  Everything is
 * stored in a native number format (e.g. double) and there is no typechecking
 * provided.  
 *
 * The benefit of this library is that it is very fast to compile code that
 * uses it and very fast for code to execute with it.
 * */

#include <physical/physical.h>

#include <iostream>

using namespace physical::unit;
using namespace physical::constant;

int main() {
    /* This access to the units/constants data provides the numbers only, in
     * double format in this case.  */
    double v1 = 10*m;
    double v2 = 10*cm;


    /* The caveat with using this access model to the units/constants data is
     * that there will be no intrinsic units mismatch checking.  Therefore,
     * there is no error generated when you try and add units in a incorrect
     * manner.  */
    double v3 = v1 + v2 * s + sigma_SB + K_B;

    std::cout << v1 << '\n'
              << v2 << '\n'
              << v3
              << std::endl;
    return 0;
}
