#ifndef physical_detail_errs_h
#define physical_detail_errs_h

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
  }
}

#endif // physical_detail_errs_h
