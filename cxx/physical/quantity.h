/** \file
 * A runtime library for a multitude of physical constants and units (mks
 * where applicable) organized into a bunch of namespaces.
 *
 * By runtime, I mean that errors from units mismatch will NOT be caught at
 * compile time like for boost units and other implementations, but rather
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


#include <physical/detail/print_coeff.h>
#include <physical/detail/ConvertCoeff.h>
#include <physical/except.h>
#define PHYSICAL_DATA_FOR_RUNTIME
#  include <physical/registry.h>
#undef PHYSICAL_DATA_FOR_RUNTIME


#include <complex>
#include <map>
#include <string>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <vector>



#if !defined(RUNTIME_PHYSICAL_QUANTITY) && \
    !defined(RUNTIME_PHYSICAL_QUANTITY_INCLUDE)
    /** The type of the coefficient in the physical::quantity<T> template and
     * throughout the units/constants library in general.
     *
     * Note that if you change this macro parameter, it is possible that some
     * of the functions within the quantity<> portion of the library may not
     * be able to instantiate.
     * */
  #define PHYSICAL_QUANTITY_COEFF_TYPE physical::quantity<>::coeff_type
#else
  #ifdef RUNTIME_PHYSICAL_QUANTITY_INCLUDE
    #include RUNTIME_PHYSICAL_QUANTITY_INCLUDE

    #ifndef RUNTIME_PHYSICAL_QUANTITY
      #error Expected definition of RUNTIME_PHYSICAL_QUANTITY \
             in RUNTIME_PHYSICAL_QUANTITY_INCLUDE
    #endif
  #endif

  #define PHYSICAL_QUANTITY_COEFF_TYPE RUNTIME_PHYSICAL_QUANTITY
#endif

#define PHYSICAL_QUANTITY_CLASS quantity<PHYSICAL_QUANTITY_COEFF_TYPE>





namespace runtime {
  namespace physical {

    /** Less-than operation for complex types.
     * For better or for worse, we are going to define the comparison
     * between two complex numbers as a comparison between their real components
     * first and then imaginary components if the real components are equal. */
    template < typename T1, typename T2 >
    bool operator< ( const std::complex<T1> & lhs,
                     const std::complex<T2> & rhs ) {
      return lhs.real() < rhs.real() ||
             (lhs.real() == rhs.real() && lhs.imag() < rhs.imag());
    }

    /** Equality operation for complex types. */
    template < typename T1, typename T2 >
    bool operator== ( const std::complex<T1> & lhs,
                      const std::complex<T2> & rhs ) {
      return lhs.real() == rhs.real() && lhs.imag() == rhs.imag();
    }

    /** Inequality operation for complex types. */
    template < typename T1, typename T2 >
    bool operator!= ( const std::complex<T1> & lhs,
                      const std::complex<T2> & rhs ) {
      return !(lhs == rhs);
    }

    /** Greater-than operation for complex types. */
    template < typename T1, typename T2 >
    bool operator> ( const std::complex<T1> & lhs,
                     const std::complex<T2> & rhs ) {
      return !(lhs == rhs) && !(lhs < rhs);
    }

    /** Greater-than-or-equal-to operation for complex types. */
    template < typename T1, typename T2 >
    bool operator>= ( const std::complex<T1> & lhs,
                      const std::complex<T2> & rhs ) {
      return !(lhs < rhs);
    }

    /** Greater-than-or-equal-to operation for complex types. */
    template < typename T1, typename T2 >
    bool operator<= ( const std::complex<T1> & lhs,
                      const std::complex<T2> & rhs ) {
      return (lhs == rhs) || (lhs < rhs);
    }


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

    /** Pretty/math print the units_pair.
     * NOTE: that this function does NOT print negative powers, rather it
     * assumes that the calling function wraps this in the denominator
     * correctly if that is necessary. */
    inline std::ostream & operator<< (std::ostream & out, const units_pair & p) {
        out << p.first;
        if (std::abs(p.second) > 1)
            /* Again, NOTE that we print out positive exponents and assume
             * that the calling function puts this in the denominator
             * correctly. */
            out << '^' << std::abs(p.second);
        return out;
    }

    /** LaTeX print the units_pair.
     * NOTE: Just like operator<<(ostream,units_pair), this function does NOT
     * print negative powers, rather it assumes that the calling function
     * wraps this in the denominator correctly if that is necessary. */
    inline std::ostream & latex_print(std::ostream & out, const units_pair & p) {
        out << "\\mathrm{" << p.first << '}';
        if (std::abs(p.second) > 1)
            /* Again, NOTE that we print out positive exponents and assume
             * that the calling function puts this in the denominator
             * correctly. */
            out << '^' << '{' << std::abs(p.second) << '}';
        return out;
    }

    /** Print the units_map with a given separator. */
    inline std::ostream & sep_print ( std::ostream & out,
                                      const units_map & u,
                                      const char * sep = " ") {
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

    /** LaTeX print the units_map. */
    inline std::ostream & latex_print (std::ostream & out, const units_map & u) {
        // unfortunately, this one is a little more complicated.
        const char * cur_sep = "";
        const char * const sep = "~";
        for (units_map::const_iterator i = u.begin(); i != u.end(); i++) {
            latex_print(out << cur_sep, (*i));
            cur_sep = sep;
        }
        return out;
    }

    /** Exponentiate a set of units by a non-integral factor. 
     * NOTE:  The result <b>MUST</b> be in integral units.
     * */
    template < typename T >
    inline units_map pow_float(const units_map & units, const T & exponent) {
        /* now loop through each of the units and try to divide/multiply the
         * power by the 'exponent'.  Throw an exception of this is not
         * possible. 
         * */
        units_map u = units;
        T fexp = std::abs(exponent);
        for (units_map::iterator i = u.begin(); i != u.end(); i++) {
            units_pair & p = (*i);
            if (fexp < 1) {
                register T fexp_inv = static_cast<T>(1)/fexp;
                if (std::fmod(static_cast<T>(p.second), fexp_inv) != 0)
                    throw exception(UnitsNotRoot);
            } else if ( (int(fexp) - fexp) != 0 )
                throw exception(UnitsNotDimensionless);
            p.second = int(p.second * exponent);
        }
        return u;
    }

    template < typename T >
    inline units_map pow(const units_map & units, const T & exponent) {
      if ( (exponent - int(exponent)) == 0 )
        return pow<int>( units, int(exponent) );
      else
        return pow_float<T>( units, exponent );
    }

    template < typename T >
    inline units_map pow( const units_map & units,
                          const std::complex<T> & exponent) {
      if (units.size() == 0)
        return units;
      else if (exponent.imag() != 0.0)
        throw exception(ComplexNotSupported);
      else
        return pow<T>( units, exponent.real() );
    }

    /** Exponentiate a set of units by an integral factor. */
    template<>
    inline units_map pow<int>(const units_map & units, const int & exponent) {
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
        /* ******** BEGIN TYPEDEFS ***** */

        /** The data storage type of the coefficient of the physical
         * quantity. */
        typedef T coeff_type;

        /** The registry type for this quantity type. */
        typedef registry::recorder< quantity<T> > registry_type;

        /** The possible printing modes. */
        enum PRINT_TYPE {
            /** Pretty formatting similar to GNU units. */
            PRETTY_PRINT        = detail::PRETTY_PRINT,
            /** Mathematically correct. */
            MATH_PRINT          = detail::MATH_PRINT,
            /** Format for latex math mode. This format uses fractional
             * format. */
            LATEX_PRINT         = detail::LATEX_PRINT,
            /** Format for latex math mode. This format is for single line
             * fractions. */
            LATEX_ONELINE_PRINT = detail::LATEX_ONELINE_PRINT,
            /** Unpleasant formatting that demonstrates the units structure. */
            UGLY_PRINT          = detail::UGLY_PRINT
        };

        /* ********** END TYPEDEFS ***** */


        /* ******** BEGIN DATA MEMBERS ********** */
      public:

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

      private:

        /** The current printing mode (except when explicitly stated in
         * print(). */
        static enum PRINT_TYPE print_type;

        /* ********** END DATA MEMBERS ********** */



        /* ******** BEGIN FUNCTION MEMBERS ****** */
      public:

        /** Set the current default print mode for this quantity type.
         * @see PRINT_TYPE.
         * */
        static void setPrintMode(const enum PRINT_TYPE & t) {
            print_type = t;
        }

        /** Get the current default print mode for this quantity type.
         * @see PRINT_TYPE.
         * */
        static const PRINT_TYPE & getPrintMode() {
            return print_type;
        }

        /** Get the global instance of the registry for this type of quantity.
         * */
        static registry_type & registry() {
            return registry_type::instance();
        }

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

      private:
        /** Split the unit set in units into a numerator and denominator. */
        void splitNumeratorAndDenominator(units_map & num, units_map & den) const {
            /* first sort into num or den exponent (of units).  The results
             * should already be sorted lexically because we use a map. */
            for (units_map::const_iterator i = units.begin(); i!= units.end(); i++) {
                const units_pair & p = (*i);
                if (p.second<0)
                    den[p.first] = p.second;
                else
                    num[p.first] = p.second;
            }
        }



      public:
        /** Prints the physical quantity in an easy-to-read format similar to
         * GNU units.
         * This function is called indirectly from print().
         * */
        std::ostream & prettyPrint(std::ostream & out) const {
            units_map num, den;
            splitNumeratorAndDenominator(num, den);

            detail::print_coeff<coeff_type,detail::PRETTY_PRINT> print_coeff;
            out << '<' << print_coeff(coeff, out.precision());
            
            if (!num.empty() || !den.empty())
                out << ' ' << num;

            // now denominator
            if (!den.empty())
                out <<  " / " << den;

            out << '>';

            if (name.length() >0)
                out << " (" << name << ')';
 
            return out;
        }

        /** Prints the physical quantity in a mathematically format that can
         * be parsed by the calculator. 
         * This function is called indirectly from print().
         * */
        std::ostream & mathPrint(std::ostream & out) const {
            units_map num, den;
            splitNumeratorAndDenominator(num, den);

            detail::print_coeff<coeff_type,detail::MATH_PRINT> print_coeff;
            out << '(' << print_coeff(coeff, out.precision());

            if (!num.empty())
                math_print(out << " * ", num);

            // now denominator
            if (den.size() == 1)
                math_print(out <<  " / ", den);
            else if (!den.empty())
                math_print(out <<  " / (", den) << ')';

            out << ')';

            return out;
        }

        /** Prints the physical quantity in a format suitable for LaTeX. 
         * This function is called indirectly from print().
         * */
        std::ostream & latexPrint(std::ostream & out, const bool & oneline = true) const {
            units_map num, den;
            splitNumeratorAndDenominator(num, den);

            detail::print_coeff<coeff_type,detail::LATEX_PRINT> print_coeff;
            out << print_coeff(coeff, out.precision());

            if (!num.empty() || !den.empty())
                out << '~'; // spacing between coeff and units

            if (!oneline && !den.empty())
                out << "\\frac{";

            // print numerator
            if (num.empty() && !den.empty())
                out << '1';
            else if (!num.empty())
                latex_print(out, num);

            if (!den.empty()) {
                // separator
                if (!oneline)
                    out << "}{";
                else
                    out << '/';

                latex_print(out, den);
            }

            if (!oneline && !den.empty())
                out << "}";

            return out;
        }

        /** Prints the quantity type using the given print mode.
         * @param out
         *      Output stream to which to write.
         * @param t
         *      Printing  mode to use for only this call to print.
         * @see PRINT_TYPE.
         * */
        inline std::ostream & print(std::ostream & out, const enum PRINT_TYPE & t) const {
            enum PRINT_TYPE old = quantity::print_type;
            quantity::print_type = t;
            print(out);
            quantity::print_type = old;
            return out;
        }

        /** Prints the quantity type using the current print mode.
         * @see PRINT_TYPE.
         * */
        inline std::ostream & print(std::ostream & out) const {
            switch(quantity::print_type) {
                case LATEX_ONELINE_PRINT:
                    latexPrint(out);
                    break;

                case LATEX_PRINT:
                    latexPrint(out,false);
                    break;

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

        /** Assignment operation from another quantity. */
        inline quantity & operator=(const quantity & q) {
            coeff = q.coeff;
            units = q.units;
            name = q.name;
            return *this;
        }

        /** Assignment operation from a coefficient (non-units) value. */
        inline quantity & operator=(const T & t) {
            coeff = t;
            units.clear();
            name.clear();
            return *this;
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
          using std::pow;
          coeff = pow(coeff, exponent);
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

        template < typename T2 >
        void getCoeff( T2 & t2 ) const {
          t2 = detail::ConvertCoeff<T2>(coeff);
        }

        template < typename T2 >
        T2 getCoeff() const {
          return detail::ConvertCoeff<T2>(coeff);
        }

        const T & getCoeff() const {
          return coeff;
        }

    };

    template <class T>
    typename quantity<T>::PRINT_TYPE quantity<T>::print_type = quantity<T>::PRETTY_PRINT;


    /* **** BEGIN QUANTITY OPERATORS **** */
    /* we define all operators here that do not need assertMatch */

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

    /** Self-multiplication operator between a quantity and a scalar. */
    template<class T>
    inline quantity<T> & operator*=(quantity<T> & q, const typename quantity<T>::coeff_type & f) {
        q.coeff *= f;
        /* There is no point in trying to keep the name now. */
        q.name.clear();
        return q;
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

    /** Self-division operator between a quantity and a scalar. */
    template<class T>
    inline quantity<T> & operator/=(quantity<T> & q, const typename quantity<T>::coeff_type & f) {
        q.coeff /= f;
        /* There is no point in trying to keep the name now. */
        q.name.clear();
        return q;
    }

    template < typename T >
    std::complex<T> fmod( const std::complex<T> & lhs,
                          const std::complex<T> & rhs ) {
      if (lhs.imag() != 0.0 || rhs.imag() != 0.0)
        throw exception(ComplexNotSupported);
      return std::fmod(lhs.real(), rhs.real());
    }

    /** Mod operator between a quantity and a quantity. */
    template<class T>
    inline quantity<T> operator%(const quantity<T> & q, const quantity<T> & d) {
      using physical::fmod;
      using std::fmod;
      return quantity<T>( fmod(q.coeff, d.coeff), q.units );
    }

    /** Mod operator between a quantity and a quantity. */
    template<class T>
    inline quantity<T> & operator%=(quantity<T> & q, const quantity<T> & d) {
      using physical::fmod;
      using std::fmod;
      q.coeff = fmod(q.coeff, d.coeff);
      return q;
    }

    /** Negation operation. */
    template < typename T >
    inline quantity<T> operator- (const quantity<T> & q) {
      return quantity<T>(-q.coeff, q.units);
    }


  }/* namespace runtime::physical */
}/* namespace runtime */

#endif // PHYSICAL_QUANTITY_H
