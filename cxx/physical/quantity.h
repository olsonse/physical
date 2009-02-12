/** \file
 * A runtime library for a multitude of physical constants and units (mks
 * where applicable) organized into a bunch of namespaces.
 *
 * By runtime, I mean that errors from units mismatch will NOT be caught at
 * compile time like for boost units and other implementions, but rather
 * exceptions will be thrown when such errors are encountered. 
 *
 * One of the main benefits to having runtime error control is that
 * interactive user input may be parsed, translated into Quantity objects, and
 * then automatically tested for units mismatch (this is at least the reason
 * why I wrote this library).
 *
 * Copyright 2008 Spencer E. Olson
 *
 * */

#ifndef PHYSICAL_QUANTITY_H
#define PHYSICAL_QUANTITY_H

#include <map>
#include <string>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <complex>
#include <vector>





#ifndef PHYSICAL_QUANTITY
    /** The type of the coefficient in the physical::quantity<T> template and
     * throughout the units/constants library in general.
     *
     * Note that if you change this macro parameter, it is possible that some
     * of the functions within the quantity<> portion of the library may not
     * be able to instantiate.
     * */
#  define PHYSICAL_QUANTITY_COEFF_TYPE physical::quantity<>::coeff_type
#else
#  define PHYSICAL_QUANTITY_COEFF_TYPE PHYSICAL_QUANTITY
#endif

#define PHYSICAL_QUANTITY_CLASS quantity<PHYSICAL_QUANTITY_COEFF_TYPE>


#define _OPEN_NAMESPACE(i,id)   namespace id { const int init_ ## i = monkeywrench::push_namespace(#id); } namespace id
#define  _CLOSE_NAMESPACE(i)    const int uninit_ ## i =  monkeywrench::pop_namespace();
#define _ALIAS_NAMESPACE(alias,ns) \
    const int I_ ## alias ## _ ## ns = \
        Quantity::registry().import(monkeywrench::get_prefix() + #ns, "*", \
                                    monkeywrench::get_prefix() + #alias); \
    namespace alias = ns



namespace runtime {
#define PHYSICAL_REGISTRY_FOR_RUNTIME
#include <physical/registry.h>
#undef PHYSICAL_REGISTRY_FOR_RUNTIME

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




    /* **** BEGIN UNITS MAP **** */


    /** The units map class.  
     * This class provides a list of all unique units and their exponent for a
     * set of unit factors in a unit term.  The physical Quantity class uses
     * this to represent the set of units and their exponents for a given
     * physical Quantity.
     *
     * We do this inherited class rather than just
     * using typedef directly so that we can ensure than any overloaded
     * operators for this class can only be used here.
     *
     * @see Quantity.
     * */
    struct units_map : std::map<std::string, int> {};
    typedef std::pair<const std::string, int> units_pair;

    /** A simple ostream helper class to print items in a container using
     * std::for_each
     * */
    template <class T>
    struct print_output {
        std::ostream & out;
        std::string sep;
        print_output(std::ostream & out, std::string sep) : out(out), sep(sep) {}

        void operator()(const T & t) {
            ugly_print(out,t) << sep;
        }
    };

    /** Print out a tuple (of type units_pair) in the units_map. */
    inline std::ostream & ugly_print (std::ostream & out, const units_pair & p) {
        return out << '(' << p.first << " : " << p.second << ')';
    }

    /** Print out a units_map. */
    inline std::ostream & ugly_print (std::ostream & out, const units_map & u) {
        out << '{';
        std::for_each(u.begin(), u.end(), print_output<units_pair>(out, ", "));
        out << '}';
        return out;
    }

    /** Pretty/math print the units_pair. */
    inline std::ostream & operator<< (std::ostream & out, const units_pair & p) {
        out << p.first;
        if (p.second > 1)
            out << '^' << p.second;
        return out;
    }

    /** Print the units_map with a given seperator. */
    inline std::ostream & sep_print (std::ostream & out, const units_map & u, const char * sep = " ") {
        const char * cur_sep = "";
        for (units_map::const_iterator i = u.begin(); i != u.end(); i++) {
            out << cur_sep << (*i);
            cur_sep = sep;
        }
        return out;
    }

    /** Math print the units_map. */
    inline std::ostream & math_print (std::ostream & out, const units_map & u) {
        return sep_print(out, u, " * ");
    }

    /** Pretty print the units_map. */
    inline std::ostream & operator<< (std::ostream & out, const units_map & u) {
        return sep_print(out, u);
    }


    /** Exponentiate a set of units by a non-integral factor. 
     * NOTE:  The result <b>MUST</b> be in integral units.
     * */
    inline units_map pow(const units_map & units, const double & exponent) {
        /* now loop through each of the units and try to divide/multiply the
         * power by the 'exponent'.  Throw an exception of this is not
         * possible. 
         * */
        units_map u = units;
        double fexp = fabs(exponent);
        for (units_map::iterator i = u.begin(); i != u.end(); i++) {
            units_pair & p = (*i);
            if (fexp < 1) {
                if (fmod((double)p.second, 1.0/fexp) != 0)
                    throw exception(UnitsNotRoot);
            } else if ( (int(fexp) - fexp) != 0 )
                throw exception(UnitsNotDimensionless);
            p.second = int(p.second * exponent);
        }
        return u;
    }

    /** Exponentiate a set of units by an integral factor. */
    inline units_map pow(const units_map & units, const int & exponent) {
        units_map u = units;
        for (units_map::iterator i = u.begin(); i != u.end(); i++)
            (*i).second *= exponent;
        return u;
    }

    /** Purge all empty units. */
    inline void drop_empty_units(units_map & u) {
        std::vector<std::string> emty;
        for (units_map::iterator i = u.begin(); i != u.end(); i++)
            if ((*i).second == 0)
                emty.push_back(i->first);
        for (std::vector<std::string>::iterator i = emty.begin(); i!=emty.end(); i++) {
            units_map::iterator j = u.find((*i));
            if (j != u.end())
                u.erase(j);
        }
    }

    /** Self-multiply the units of two units_map objects. */
    inline units_map & operator*=(units_map & u0, const units_map & u1) {
        /* start with a complete copy of u0. */

        /* Add exponents of all common units. */
        for (units_map::iterator i = u0.begin(); i != u0.end(); i++) {
            units_pair & p = (*i);
            units_map::const_iterator j = u1.find(p.first);
            if (j != u1.end())
                p.second += (*j).second;
        }

        /* Add non-common units from u1. */
        for (units_map::const_iterator i = u1.begin(); i != u1.end(); i++) {
            const units_pair & p = (*i);
            units_map::const_iterator j = u0.find(p.first);
            if (j == u0.end())
                u0[p.first] = p.second;
        }

        drop_empty_units(u0);
        return u0;
    }

    /** Divide the units of the first units_map object by the units in the
     * second. */
    inline units_map & operator/=(units_map & u0, const units_map & u1) {
        return u0 *= pow(u1, (int)-1);
    }

    /** Multiply the units of two units_map objects. */
    inline units_map operator*(const units_map & u0, const units_map & u1) {
        units_map u = u0;
        return u *= u1;
    }

    /** Divide the units of the first units_map object by the units in the
     * second. */
    inline units_map operator/(const units_map & u0, const units_map & u1) {
        units_map u = u0;
        return u /= u1;
    }

    /* **** END UNITS MAP **** */



    /** The basic physical quantity class where-in (almost) all units and
     * constants are stored. */
    template<class T = double>
    class quantity {
      public:
        typedef physical::registry::recorder< quantity<T> > registry_type;
        static registry_type & registry() {
            return registry_type::instance();
        }

        enum PRINT_TYPE {
            PRETTY_PRINT,
            MATH_PRINT,
            UGLY_PRINT
        };

        static enum PRINT_TYPE print_type;

        /** The data storage type of the coefficient of the physical
         * quantity. */
        typedef T coeff_type;

        /** The coefficient of this physical quantity. */
        coeff_type coeff;

        /** The units map of this physical quantity.
         * @see units_map
         * */
        units_map units;

        /** The (optional) name of this quantity.  This is currently used to
         * store the names of various physical constants, like the speed of
         * light.  This string is only used for printing the value out using
         * the prettyPrint() function.
         * */
        std::string name;

        /** Copy constructor that allows specification of a different name. */
        quantity(const quantity & q,
                 const std::string & _name = "", const std::string & rs = "") :
            coeff(q.coeff), units(q.units), name(q.name) {
            registry().record(rs,this);
            if (_name.length() > 0)
                name = _name;
        }

        /** Constructor that initializes the units from a single units_pair. */
        quantity(const coeff_type & _coeff, const units_pair & pair,
                 const std::string & _name = "", const std::string & rs = "") :
            coeff(_coeff), units(), name(_name) {
            registry().record(rs,this);
            if (pair.second != 0)
                units.insert(pair);
        }

        /** Constructor that initializes the units from a complete units_map
         * object. */
        quantity(const coeff_type & _coeff = 0.0,const units_map & _units = units_map(),
                 const std::string & _name = "", const std::string & rs = "") :
            coeff(_coeff), units(_units), name(_name) {
            registry().record(rs,this);
            drop_empty_units(units);
        }

        /** Convert the units to an equivalent string representation using the
         * current print_type. */
        inline std::string toString() const {
            std::ostringstream out;
            print(out);
            return out.str();
        }

        /** Prints the physical quantity in an easy-to-read format similar to
         * GNU units. */
        std::ostream & prettyPrint(std::ostream & out) const {
            units_map pos, neg;

            /* first sort into pos or neg exponent (of units).  The results
             * should already be sorted lexically because we use a map. */
            for (units_map::const_iterator i = units.begin(); i!= units.end(); i++) {
                const units_pair & p = (*i);
                if (p.second<0)
                    neg[p.first] = p.second;
                else
                    pos[p.first] = p.second;
            }

            out << '<' << coeff;
            
            if (!pos.empty() || !neg.empty())
                out << ' ' << pos;

            // now denominator
            if (!neg.empty())
                out <<  " / " << neg;

            out << '>';

            if (name.length() >0)
                out << " (" << name << ')';
 
            return out;
        }

        /** Prints the physical quantity in a mathematically format that can
         * be parsed by the calculator. */
        std::ostream & mathPrint(std::ostream & out) const {
            units_map pos, neg;

            /* first sort into pos or neg exponent (of units).  The results
             * should already be sorted lexically because we use a map. */
            for (units_map::const_iterator i = units.begin(); i!= units.end(); i++) {
                const units_pair & p = (*i);
                if (p.second<0)
                    neg[p.first] = p.second;
                else
                    pos[p.first] = p.second;
            }

            out << '(' << coeff;

            if (!pos.empty())
                math_print(out << " * ", pos);

            // now denominator
            if (neg.size() == 1)
                math_print(out <<  " / ", neg);
            else if (!neg.empty())
                math_print(out <<  " / (", neg) << ')';

            out << ')';

            return out;
        }

        inline std::ostream & print(std::ostream & out, const enum PRINT_TYPE & t) const {
            enum PRINT_TYPE old = quantity::print_type;
            quantity::print_type = t;
            print(out);
            quantity::print_type = old;
            return out;
        }

        inline std::ostream & print(std::ostream & out) const {
            switch(quantity::print_type) {
                case MATH_PRINT:
                    mathPrint(out);
                    break;

                case UGLY_PRINT:
                    out << coeff << " * ";
                    ugly_print(out,units);
                    break;

                default:
                case PRETTY_PRINT:
                    prettyPrint(out);
                    break;
            }
            return out;
        }

        inline const quantity & assertUnitless() const throw (exception) {
            if (!units.empty())
                throw exception(UnitsNotDimensionless);
            return *this;
        }

        inline const quantity & assertMatch(const quantity & q) const throw (exception) {
            if (units != q.units)
                throw exception(UnitsMismatch);
            return *this;
        }

        /* **** BEGIN QUANTITY OPERATORS **** */
        /* We are only going to define operators here that MUST check units */

        inline quantity & operator+=(const quantity & q) {
            assertMatch(q);
            coeff += q.coeff;
            /* There is no point in trying to keep the name now. */
            name.clear();
            return *this;
        }

        inline quantity & operator-=(const quantity & q) {
            assertMatch(q);
            coeff -= q.coeff;
            /* There is no point in trying to keep the name now. */
            name.clear();
            return *this;
        }

        inline quantity operator+(const quantity & q) const {
            assertMatch(q);
            return quantity(coeff + q.coeff, units);
        }

        inline quantity operator-(const quantity & q) const {
            assertMatch(q);
            return quantity(coeff - q.coeff, units);
        }

        inline bool operator>(const quantity & q) const {
            assertMatch(q);
            return coeff > q.coeff;
        }

        inline bool operator<(const quantity & q) const {
            assertMatch(q);
            return coeff < q.coeff;
        }

        inline bool operator>=(const quantity & q) const {
            assertMatch(q);
            return coeff >= q.coeff;
        }

        inline bool operator<=(const quantity & q) const {
            assertMatch(q);
            return coeff <= q.coeff;
        }

        inline bool operator==(const quantity & q) const {
            assertMatch(q);
            return coeff == q.coeff;
        }


        /* THESE FUNCTIONS MUST BE IN-CLASS. */

        /** The power operator. */
        template<class ExpT>
        inline quantity & savePow(const ExpT & exponent) {
            coeff = std::pow(coeff, exponent);
            units = pow(units, exponent);
            /* There is no point in trying to keep the name now. */
            name.clear();
            return *this;
        }
 
        inline quantity & savePow(const quantity<T> & e) {
            if (!e.units.empty())
                throw exception(UnitsNotDimensionlessExp);
            return savePow(e.coeff);
        }

        /** The power operator.
         * I could not figure out how to get boost::spirit to call my
         * savePow, but using this function seems to work.
         *
         * @param ExpT
         *     The type of the exponent may be int, double, or quantity<T>.
         * */
        template<class ExpT>
        inline quantity & operator^=(const ExpT & exponent) {
            return savePow(exponent);
        }
 
        /* ****   END QUANTITY OPERATORS **** */
    };

    template <class T>
    enum quantity<T>::PRINT_TYPE quantity<T>::print_type = quantity<T>::PRETTY_PRINT;


    /* **** BEGIN QUANTITY OPERATORS **** */
    /* we define all operators here that do not need assertMatch */

    /** The power operator.
     * The templated ExpT parameter allows this function to instantiate the
     * correct pow<ExpT>(units_map&) function. 
     * */
    template<class T, class ExpT>
    inline quantity<T> pow(const quantity<T> & q, const ExpT & exponent) {
        return quantity<T>(std::pow(q.coeff, exponent), pow(q.units,exponent));
    }

    /** The >> operator prints out the quantity in a semi pretty fashion
     * similar to GNU units. */
    template<class T>
    inline std::ostream & operator << (std::ostream & out, const quantity<T> & q) {
        return q.print(out);
    }

    /** Multiplication operator between two quantities. */
    template<class T>
    inline quantity<T> operator*(const quantity<T> & q0, const quantity<T> & q1) {
        return quantity<T>(q0.coeff * q1.coeff, q0.units * q1.units);
    }

    /** Self-multiplication operator between two quantities. */
    template<class T>
    inline quantity<T> & operator*=(quantity<T> & q0, const quantity<T> & q1) {
        q0.coeff *= q1.coeff;
        q0.units *= q1.units;
        /* There is no point in trying to keep the name now. */
        q0.name.clear();
        return q0;
    }

    /** Division operator between two quantities. */
    template<class T>
    inline quantity<T> operator/(const quantity<T> & q0, const quantity<T> & q1) {
        return quantity<T>(q0.coeff / q1.coeff, q0.units / q1.units);
    }

    /** Self-division operator between two quantities. */
    template<class T>
    inline quantity<T> & operator/=(quantity<T> & q0, const quantity<T> & q1) {
        q0.coeff /= q1.coeff;
        q0.units /= q1.units;
        /* There is no point in trying to keep the name now. */
        q0.name.clear();
        return q0;
    }

    /** Multiplication operator between a quantity and a scalar. */
    template<class T>
    inline quantity<T> operator*(const quantity<T> & q, const typename quantity<T>::coeff_type & f) {
        return quantity<T>(q.coeff * f, q.units);
    }

    /** Multiplication operator between a quantity and a scalar. */
    template<class T>
    inline quantity<T> operator*(const typename quantity<T>::coeff_type & f, const quantity<T> & q) {
        return quantity<T>(q.coeff * f, q.units);
    }

    /** Division operator between a quantity and a scalar. */
    template<class T>
    inline quantity<T> operator/(const quantity<T> & q, const typename quantity<T>::coeff_type & f) {
        return quantity<T>( q.coeff / f, q.units);
    }

    /** Division operator between a quantity and a scalar. */
    template<class T>
    inline quantity<T> operator/(const typename quantity<T>::coeff_type & f, const quantity<T> & q) {
        return quantity<T>( f / q.coeff, pow(q.units,(int)-1) );
    }

    /** Mod operator between a quantity and a quantity. */
    template<class T>
    inline quantity<T> operator%(const quantity<T> & q, const quantity<T> & d) {
        return quantity<T>( fmod(q.coeff, d.coeff), q.units );
    }

    /** Mod operator between a quantity and a quantity. */
    template<class T>
    inline quantity<T> & operator%=(quantity<T> & q, const quantity<T> & d) {
        q.coeff = fmod(q.coeff, d.coeff);
        return q;
    }

}

/* now finally, load the data. */
#define PHYSICAL_DATA_FOR_RUNTIME
#include <physical/physical.h>
#undef PHYSICAL_DATA_FOR_RUNTIME


namespace physical {
    /** As set of unary mathematical functions that operate on quantity<T>
     * types.  Many of these are just wrappers for math.h functions.
     * */
    namespace math {
        /** Perform units checking for math functions of strictly dimensionless
         * arguments. */
        struct no_dims {
            template <class T>
            static inline void check(const quantity<T> & q) {
                (void)q.assertUnitless();
            }
        };
 
        /** Perform units checking for math functions of angle or dimensionless
         * arguments. */
        template <class T>
        struct w_angle {
            static inline void check(const quantity<T> & q) {
                /* FIXME:  should we allow the dimensionless case here too? */
                if (!q.units.empty() && q.units != physical::unit::radian.units) {
                    throw exception(UnitsMismatchF);
                }
            }
        };
 
        template<class T>
        quantity<T> sin(const quantity<T> & q) {
            w_angle<T>::check(q);
            return std::sin(q.coeff);
        };
 
        template<class T>
        quantity<T> cos(const quantity<T> & q) {
            w_angle<T>::check(q);
            return std::cos(q.coeff);
        };
 
        template<class T>
        quantity<T> tan(const quantity<T> & q) {
            w_angle<T>::check(q);
            return std::tan(q.coeff);
        };
 
        template<class T>
        quantity<T> asin(const quantity<T> & q) {
            no_dims::check(q);
            return std::asin(q.coeff) * physical::unit::radian;
        };
 
        template<class T>
        quantity<T> acos(const quantity<T> & q) {
            no_dims::check(q);
            return std::acos(q.coeff) * physical::unit::radian;
        };
 
        template<class T>
        quantity<T> atan(const quantity<T> & q) {
            no_dims::check(q);
            return std::atan(q.coeff) * physical::unit::radian;
        };
 
        template<class T>
        quantity<T> sinh(const quantity<T> & q) {
            w_angle<T>::check(q);
            return std::sinh(q.coeff);
        };
 
        template<class T>
        quantity<T> cosh(const quantity<T> & q) {
            w_angle<T>::check(q);
            return std::cosh(q.coeff);
        };
 
        template<class T>
        quantity<T> tanh(const quantity<T> & q) {
            w_angle<T>::check(q);
            return std::tanh(q.coeff);
        };
 
        template<class T>
        quantity<T> asinh(const quantity<T> & q) {
            no_dims::check(q);
            return std::asin(q.coeff) * physical::unit::radian;
        };
 
        template<class T>
        quantity<T> acosh(const quantity<T> & q) {
            no_dims::check(q);
            return std::acos(q.coeff) * physical::unit::radian;
        };
 
        template<class T>
        quantity<T> atanh(const quantity<T> & q) {
            no_dims::check(q);
            return std::atan(q.coeff) * physical::unit::radian;
        };
 
        template<class T>
        quantity<T> sinc(const quantity<T> & q) {
            w_angle<T>::check(q);
            return q.coeff==0 ? 1 : std::sin(q.coeff) / q.coeff;
        };
 
        template<class T>
        quantity<T> exp(const quantity<T> & q) {
            w_angle<T>::check(q);
            return std::exp(q.coeff);
        };
 
        template<class T>
        quantity<T> erf(const quantity<T> & q) {
            w_angle<T>::check(q);
            return ::erf(q.coeff);
        };
 
        template<class T>
        quantity<T> erfc(const quantity<T> & q) {
            w_angle<T>::check(q);
            return ::erfc(q.coeff);
        };
 
        template<class T>
        quantity<T> log(const quantity<T> & q) {
            no_dims::check(q);
            return std::log(q.coeff);
        };
 
        template<class T>
        quantity<T> log10(const quantity<T> & q) {
            no_dims::check(q);
            return std::log10(q.coeff);
        };
 
        template<class T>
        quantity<T> sqrt(const quantity<T> & q) {
            return pow(q, 0.5);
        };
 
        template<class T>
        quantity<T> tgamma(const quantity<T> & q) {
            no_dims::check(q);
            return ::tgamma(q.coeff);
        };
 
        /** Compute the floor of the quantity. */
        template<class T>
        quantity<T> floor(const quantity<T> & q) {
            return quantity<T>(std::floor(q.coeff), q.units);
        };
 
        /** Compute the ceil of the quantity. */
        template<class T>
        quantity<T> ceil(const quantity<T> & q) {
            return quantity<T>(std::ceil(q.coeff), q.units);
        };
 
        /** Compute the absolute value of the quantity.
         * This function does not currently instantiate for std::complex types of
         * coefficients. */
        template<class T>
        quantity<T> fabs(const quantity<T> & q) {
            return quantity<T>(std::fabs(q.coeff), q.units);
        };

    } /* namespace math. */

    /* ****   END QUANTITY OPERATORS **** */
}} /* namespace runtime::physical */

#endif // PHYSICAL_QUANTITY_H
