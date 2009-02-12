/** Demonstrates the use of the "registry" mechanism to store a list of
 * variable names (in std::string format) linked to a particular object in
 * memory.
 *
 * This mechanism is not yet currently in use in the initialization of the
 * units/constants physical::Quantity items.  
 * */


#include <iostream>
#include <physical/quantity.h>

int main() {
    using namespace runtime; /* strip the runtime:: prefix on runtime::physical::* */
    using physical::Quantity;
    Quantity a = Quantity(physical::unit::m,"","other::m");

    std::cout << "a  = " << a << "\n"
                 "&a = " << &a << "\n"
                 "&m = " << Quantity::registry().list["other::m"] << "\n"
              << std::flush;

    for (Quantity::registry_type::list_type::iterator i = Quantity::registry().list.begin() ;
         i != Quantity::registry().list.end(); ++i) {
        std::cout << i->first << " :  " << i->second << std::endl;
    }
    
    return 0;
}
