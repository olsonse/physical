#ifndef PHYSICAL_CALC_UNITS_H
#define PHYSICAL_CALC_UNITS_H

#include "symbol.h"

namespace physical {
namespace calc {

static void addPhysicalUnits(symbol::table & symbols) {
    using physical::Quantity;

    for ( Quantity::registry_type::list_type::iterator i =
             Quantity::registry().list.begin() ;
          i != Quantity::registry().list.end();
          ++i) {
        symbols[i->first] = *(i->second);
    }

    symbol::import(symbols, "physical::element::hydrogen",  "*", "physical::element::H" );
    symbol::import(symbols, "physical::element::helium",    "*", "physical::element::He");
    symbol::import(symbols, "physical::element::lithium",   "*", "physical::element::Li");
    symbol::import(symbols, "physical::element::beryllium", "*", "physical::element::Be");
    symbol::import(symbols, "physical::element::carbon",    "*", "physical::element::C" );
    symbol::import(symbols, "physical::element::nitrogen",  "*", "physical::element::N" );
    symbol::import(symbols, "physical::element::oxygen",    "*", "physical::element::O" );
    symbol::import(symbols, "physical::element::fluorine",  "*", "physical::element::F" );
    symbol::import(symbols, "physical::element::neon",      "*", "physical::element::Ne");
    symbol::import(symbols, "physical::element::sodium",    "*", "physical::element::Na");
    symbol::import(symbols, "physical::element::silicon",   "*", "physical::element::Si");
    symbol::import(symbols, "physical::element::sulfur",    "*", "physical::element::S" );
    symbol::import(symbols, "physical::element::chlorine",  "*", "physical::element::Cl");
    symbol::import(symbols, "physical::element::argon",     "*", "physical::element::Ar");
    symbol::import(symbols, "physical::element::potassium", "*", "physical::element::K" );
    symbol::import(symbols, "physical::element::krypton",   "*", "physical::element::Kr");
    symbol::import(symbols, "physical::element::rubidium",  "*", "physical::element::Rb");
    symbol::import(symbols, "physical::element::xenon",     "*", "physical::element::Xe");
    symbol::import(symbols, "physical::element::cesium",    "*", "physical::element::Cs");
    symbol::import(symbols, "physical::element::mercury",   "*", "physical::element::Hg");
    symbol::import(symbols, "physical::element::francium",  "*", "physical::element::Fr");
}

}
}

#endif // PHYSICAL_CALC_UNITS_H
