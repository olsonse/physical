#include <physical/runtime.h>
#include <physical/math.h>
#include <iostream>

using namespace runtime::physical;
using runtime::physical::system::si;

int main() {
    Quantity a = 2 * units::m;
    Quantity b = pow(a,10.0);
    Quantity c = pow(b,0.5);
    c = 1;
    c *= constant::sigma_SB<si>::value();
    c /= constant::sigma_SB<si>::value();

    Quantity d = 10*unit::radian;


    b.print(std::cout << "b:  ", Quantity::UGLY_PRINT) << '\n';
    c.print(std::cout << "c:  ", Quantity::UGLY_PRINT) << '\n';
    pow(b,0.1).print(std::cout << "pow(b,0.1):  ", Quantity::UGLY_PRINT) << '\n';
    std::cout << "b = " << b << "\n\n";

    d.print(std::cout << "d:  ") << '\n';
    if (d.units.find("radian") == d.units.end())
        std::cout << "d:  could not find radian\n";

    std::cout << "sigma_SB\t: " << constant::sigma_SB<si>::value() << '\n';
    std::cout << "h_bar\t\t: " << constant::h_bar<si>::value() << "\n\n";

    Quantity v = unit::m / unit::s;
    Quantity A = v + constant::c<si>::value();
    std::cout << v << v.units << constant::c<si>::value().units << std::endl;
    /* For quantity<T>::operator+(T), and T = std::complex<>,
     * this line does not work unless the 1.0 is wrapped inside something that
     * will convert it to std::complex.
     */
    Quantity v0 = v / constant::c<si>::value() + Quantity(1.0);

    std::cout << "c\t\t: " << constant::c<si>::value() << "\n"
                 "v\t\t: " << v << "\n"
                 "A = v + c\t: " << A << "\n"
                 "v0 = v / c\t: " << v0
              << std::endl;
    return 0;
}
