#include <physical/quantity.h>
#include <iostream>

using physical::Quantity;

int main() {
    Quantity a = 2 * physical::units::m;
    Quantity b = pow(a,10.0);
    Quantity c = pow(b,0.5);
    c = 1;
    c *= physical::constant::sigma_SB;
    c /= physical::constant::sigma_SB;

    Quantity d = 10*physical::unit::radian;


    b.print(std::cout << "b:  ", Quantity::UGLY_PRINT) << '\n';
    c.print(std::cout << "c:  ", Quantity::UGLY_PRINT) << '\n';
    pow(b,0.1).print(std::cout << "pow(b,0.1):  ", Quantity::UGLY_PRINT) << '\n';
    std::cout << "b = " << b << "\n\n";

    d.print(std::cout << "d:  ") << '\n';
    if (d.units.find("radian") == d.units.end())
        std::cout << "d:  could not find radian\n";

    std::cout << "sigma_SB\t: " << physical::constant::sigma_SB << '\n';
    std::cout << "h_bar\t\t: " << physical::constant::h_bar << "\n\n";

    Quantity v = physical::unit::m / physical::unit::s;
    Quantity A = v + physical::constant::c;
    std::cout << v << v.units << physical::constant::c.units << std::endl;
    Quantity v0 = v / physical::constant::c + 1;

    std::cout << "c\t\t: " << physical::constant::c << "\n"
                 "v\t\t: " << v << "\n"
                 "A = v + c\t: " << A << "\n"
                 "v0 = v / c\t: " << v0
              << std::endl;
    return 0;
}
