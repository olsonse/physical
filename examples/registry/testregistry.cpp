/** Demonstrates the use of the "registry" mechanism to store a list of
 * variable names (in std::string format) linked to a particular object in
 * memory.
 * */


#include <iostream>
#include <physical/runtime.h>

int main() {
    namespace rphysical = runtime::physical; /* strip the runtime:: prefix on runtime::physical::* */
    using rphysical::Quantity;
    Quantity a = Quantity(rphysical::unit::m,"","other::m");

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
