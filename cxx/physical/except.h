/** \file
 * Definitions of the exception class and associated error messages used in
 * the physical library.
 */

#ifndef physical_except_h
#define physical_except_h

#include <stdexcept>

namespace runtime {
  namespace physical {

    /** The base exception class for the physical namespace. */
    struct exception : std::runtime_error {
        exception(const std::string & s) : 
        std::runtime_error(s) {}
    };

    static const char * UnitsMismatch  = "Units mismatch:  cannot add/subtract/compare mismatched units";
    static const char * UnitsMismatchR = "Units mismatch:  mismatched units in read operation";
    static const char * UnitsMismatchF = "Units mismatch:  cannot operate on mismatched units";
    static const char * UnitsNotRoot   = "Units not root:  cannot take non-even root of units";
    static const char * UnitsNotDimensionless = "Units not dimensionless:  cannot create non-integer powers of unit";
    static const char * UnitsNotDimensionlessExp = "Units not dimensionless:  exponent must be dimensionless";
    static const char * ComplexNotSupported = "Operation on complex type not supported";

    /** The sole purpose of this function is to quiet the stupid compiler. */
    static inline unsigned long compiler_quietor() {
      return
        reinterpret_cast<unsigned long>(UnitsMismatch           ) 
       +reinterpret_cast<unsigned long>(UnitsMismatchR          )
       +reinterpret_cast<unsigned long>(UnitsMismatchF          )
       +reinterpret_cast<unsigned long>(UnitsNotRoot            )
       +reinterpret_cast<unsigned long>(UnitsNotDimensionless   )
       +reinterpret_cast<unsigned long>(UnitsNotDimensionlessExp)
       +reinterpret_cast<unsigned long>(ComplexNotSupported     );
    }
  }
}

#endif // physical_except_h
