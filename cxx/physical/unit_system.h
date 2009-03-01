/** \file
 * A registry for physical::quantity types that have been initialized
 * properly.
 *
 * */

#if defined (PHYSICAL_CONVERSION_FOR_RUNTIME) || !defined(PHYSICAL_CONVERSION_H)
#  if !defined (PHYSICAL_CONVERSION_FOR_RUNTIME)
#    define PHYSICAL_CONVERSION_H
#  endif

#if !defined (PHYSICAL_CONVERSION_FOR_RUNTIME)
#  include <physical/physical.h>
#endif

#include <stdexcept>

namespace physical {

/** Calculate the conversion factor from SYS_SRC system of units to SYS_DST
 * system of units for the dimension Dim.
 *
 *  Quantity Len_cgs = CONVERT(SI,CGS,Length,10.0*physical::unit::cm);
 *  Quantity Len_cgs = 10.0*physical::unit::cm * (SI::length / CGS::length);
 *  Quantity Len_cgs = 10.0*physical::unit::cm * CONVERT_FACTOR(SI,CGS,length)
 *  Length<CGS> Len = convert<CGS>(10*physical::unit::cm);
 *  Length<CGS> Len = 10*physical::unit::cm;
 */
#define CONVERT_FACTOR(SYS_SRC,SYS_DST,Dim) \
    (/*physical::unit::system::*/SYS_SRC::Dim / /*physical::unit::system::*/SYS_DST::Dim)
#define CONVERT(SYS_SRC,SYS_DST,Dim,Value) \
    (Value * CONVERT_FACTOR(SYS_SRC,SYS_DST,Dim))

    namespace unit { namespace system {
        namespace SI {
            const Quantity force        = unit::Newton;
            const Quantity energy       = unit::Joule;
            const Quantity length       = unit::m;
            const Quantity mass         = unit::kg;
            const Quantity time         = unit::s;
            const Quantity power        = unit::Watt;
            const Quantity temperature  = unit::Kelvin;
            const Quantity velocity     = unit::m / unit::s;
            const Quantity pressure     = unit::Pa;
            const Quantity momentum     = velocity * mass;//N * s;
            const Quantity angular_momentum = momentum * length;//N * m *s;
            namespace electric {
                const Quantity k        = 1.0 / (4 * (unit::pi/unit::radian)
                                                   * constant::epsilon);
                const Quantity potential= unit::Volt;
                const Quantity field    = potential / length;
                const Quantity charge   = unit::Coulomb;
                const Quantity e        = constant::e; /*charge per electron */
                const Quantity current  = unit::Ampere;
                const Quantity resistance  = unit::Ohm;
                const Quantity conductance = unit::Siemens;
                const Quantity resistivity = resistance * length;
                const Quantity conductivity= 1./resistivity;
            }
            namespace magnetic {
                const Quantity field    = unit::Tesla;
                const Quantity flux     = unit::Weber;
            }
        }/* namespace SI */

        namespace atomic {
            const Quantity force        = constant::Hartree / constant::a_0;
            const Quantity energy       = constant::Hartree;
            const Quantity length       = constant::a_0;
            const Quantity mass         = constant::m_e;
            const Quantity time         = constant::h_bar / constant::Hartree;
            const Quantity power        = energy / time;
            const Quantity temperature  = energy / constant::K_B;
            const Quantity velocity     = length / time;
            const Quantity pressure     = force / (length*length);
            const Quantity momentum     = velocity * mass;
            const Quantity angular_momentum = momentum * length;//constant::h_bar;
            namespace electric { /* Gaussian convention */
                const Quantity k        = SI::electric::k;
                const Quantity potential= SI::electric::potential
                                        / (k * constant::e);
                const Quantity field    = potential / length;
                const Quantity charge   = constant::e;
                const Quantity e        = 1; /* charge per electron */
                const Quantity current  = charge / time;
                const Quantity resistance  = potential / current;
                const Quantity conductance = 1./ resistance;
                const Quantity resistivity = resistance * length;
                const Quantity conductivity= 1./ resistivity;
            }
            namespace magnetic { /* Gaussian convention */
                const Quantity field    = SI::magnetic::field
                                        / (electric::k * constant::e * constant::alpha);
                const Quantity flux     = field * (length * length);
            }
        }/* namespace atomic */


        namespace cgs {
            const Quantity force        = unit::dyne;
            const Quantity energy       = unit::erg;
            const Quantity length       = unit::cm;
            const Quantity mass         = unit::g;
            const Quantity time         = unit::s;
            const Quantity power        = energy / time;
            const Quantity temperature  = unit::Kelvin;
            const Quantity velocity     = length / time;
            const Quantity pressure     = unit::Barye;
            const Quantity momentum     = velocity * mass;
            const Quantity angular_momentum = momentum * length;
        }

        namespace electrostatic {
            using namespace cgs; /* import basic cgs units */
            namespace electric { /* gaussian convention */
                const Quantity k        = 1.0;
                const Quantity potential= unit::statVolt;
                const Quantity field    = potential / length;
                const Quantity charge   = unit::statCoulomb;
                const Quantity e        = constant::e / charge; /* charge per electron */
                const Quantity current  = unit::statAmpere;
                const Quantity resistance  = potential / current;
                const Quantity conductance = 1./ resistance;
                const Quantity resistivity = resistance * length;
                const Quantity conductivity= 1./ resistivity;
            }
            namespace magnetic { /* gaussian convention */
                const Quantity field    = unit::Gauss;
                const Quantity flux     = unit::Maxwell;
            }
        }
        namespace esu = electrostatic;

        namespace electromagnetic {
            using namespace cgs; /* import basic cgs units */
            namespace electric {
            }
            namespace magnetic {
            }
        }
        namespace emu = electromagnetic;

        namespace gaussian {
            using namespace cgs; /* import basic cgs units */
            namespace electric {
            }
            namespace magnetic {
            }
        }

        namespace heaviside_lorentz {
            using namespace cgs; /* import basic cgs units */
            namespace electric {
            }
            namespace magnetic {
            }
        }
    }}/*namespace unit::system */


#define PHYSICAL_UNIT_SYS_EXPOSE(SYS,Dim) \
    inline static const Quantity & Dim() { \
        return physical::unit::system::SYS::Dim; \
    }

/** Defines a structure of a unit system so that we can template on the unit
 * system. */
#define PHYSICAL_UNITS_SYS(SYS) \
    namespace unit { \
        struct SYS { \
            PHYSICAL_UNIT_SYS_EXPOSE(SYS,force) \
            PHYSICAL_UNIT_SYS_EXPOSE(SYS,energy) \
            PHYSICAL_UNIT_SYS_EXPOSE(SYS,length) \
            PHYSICAL_UNIT_SYS_EXPOSE(SYS,mass) \
            PHYSICAL_UNIT_SYS_EXPOSE(SYS,time) \
            PHYSICAL_UNIT_SYS_EXPOSE(SYS,power) \
            PHYSICAL_UNIT_SYS_EXPOSE(SYS,temperature) \
            PHYSICAL_UNIT_SYS_EXPOSE(SYS,velocity) \
            PHYSICAL_UNIT_SYS_EXPOSE(SYS,pressure) \
            PHYSICAL_UNIT_SYS_EXPOSE(SYS,momentum) \
            PHYSICAL_UNIT_SYS_EXPOSE(SYS,angular_momentum) \
            struct electric { \
                PHYSICAL_UNIT_SYS_EXPOSE(SYS::electric,k) \
                PHYSICAL_UNIT_SYS_EXPOSE(SYS::electric,potential) \
                PHYSICAL_UNIT_SYS_EXPOSE(SYS::electric,field) \
                PHYSICAL_UNIT_SYS_EXPOSE(SYS::electric,charge) \
                PHYSICAL_UNIT_SYS_EXPOSE(SYS::electric,e) \
                PHYSICAL_UNIT_SYS_EXPOSE(SYS::electric,current) \
                PHYSICAL_UNIT_SYS_EXPOSE(SYS::electric,resistance) \
                PHYSICAL_UNIT_SYS_EXPOSE(SYS::electric,conductance) \
                PHYSICAL_UNIT_SYS_EXPOSE(SYS::electric,resistivity) \
                PHYSICAL_UNIT_SYS_EXPOSE(SYS::electric,conductivity) \
            }; /* electric */ \
            struct magnetic { \
                PHYSICAL_UNIT_SYS_EXPOSE(SYS::magnetic,field) \
                PHYSICAL_UNIT_SYS_EXPOSE(SYS::magnetic,flux) \
            }; /* magnetic */ \
        }; /* sys struct */ \
    }/*namespace unit::system */


    /* create structures for all unit systems that are complete. */
    PHYSICAL_UNITS_SYS(SI);
    PHYSICAL_UNITS_SYS(atomic);
    PHYSICAL_UNITS_SYS(electrostatic);
    PHYSICAL_UNITS_SYS(esu);


    /* FIXME:  uncomment when these systems are finished. */
    //PHYSICAL_UNITS_SYS(emu);
    //PHYSICAL_UNITS_SYS(electromagnetic);
    //PHYSICAL_UNITS_SYS(gaussian);
    //PHYSICAL_UNITS_SYS(heaviside_lorentz);



    namespace unit {
        /** System ids of unit::systems that can be specified during runtime
         * as output sytem of a unit conversion. */
        namespace system_id {
            enum SYSTEMS {
                SI,
                ESU,
//              EMU,
                ATOMIC,
//              GAUSSIAN,
//              HEAVISIDE_LORENTZ
            };
        };

#define PHYSICAL_UNIT_SYS_CONVERT(SUBSYS,Dim) \
    inline static Quantity Dim(const Quantity & q) { \
        return q * CONVERT_FACTOR(src ## SUBSYS,dst ## SUBSYS,Dim()); \
    } \
    inline static Quantity Dim( \
                        const Quantity & q, \
                        const enum system_id::SYSTEMS dst_id) { \
        switch (dst_id) { \
            case system_id::SI: \
                return q * CONVERT_FACTOR(src ## SUBSYS,physical::units::SI ## SUBSYS,Dim()); \
            case system_id::ESU: \
                return q * CONVERT_FACTOR(src ## SUBSYS,physical::units::esu ## SUBSYS,Dim()); \
/*          case system_id::EMU: \
                return q * CONVERT_FACTOR(src ## SUBSYS,physical::units::emu ## SUBSYS,Dim()); \
*/          case system_id::ATOMIC: \
                return q * CONVERT_FACTOR(src ## SUBSYS,physical::units::atomic ## SUBSYS,Dim()); \
/*          case system_id::GAUSSIAN: \
                return q * CONVERT_FACTOR(src ## SUBSYS,physical::units::gaussian ## SUBSYS,Dim()); \
            case system_id::HEAVISIDE_LORENTZ: \
                return q * CONVERT_FACTOR(src ## SUBSYS,physical::units::heaviside_lorentz ## SUBSYS,Dim()); \
*/          default: \
                throw std::runtime_error("unknown output units on conversion"); \
        } \
    }


        /** A simple templated converter for all of the dimension types that are
         * defined in the unit::system(s).
         * As, an example, one can convert a quantity in SI units (as
         * physical::unit::* units are implicitly in) into electrostatic units by: <br>
            <code>const Quantity aaa = convert<units::SI,units::esu>::length(physical::unit::cm);</code>
         *
         * For each quantity conversion, the target unit sytem can also be
         * specified at runtime as the second parameter of each overloaded
         * quantity conversion: <br>
            <code>const Quantity aaa = convert<units::SI>::length(physical::unit::cm,system_id::ESU);</code>
         *
         * As stated above, the purpose of the templated converter and system
         * structs is to allow a function/class to be templated on a unit::system.
         *
         * */
        template<typename src, typename dst = units::SI>
        struct convert {
            typedef src src;
            typedef dst dst;
            PHYSICAL_UNIT_SYS_CONVERT(,force)
            PHYSICAL_UNIT_SYS_CONVERT(,energy)
            PHYSICAL_UNIT_SYS_CONVERT(,length)
            PHYSICAL_UNIT_SYS_CONVERT(,mass)
            PHYSICAL_UNIT_SYS_CONVERT(,time)
            PHYSICAL_UNIT_SYS_CONVERT(,power)
            PHYSICAL_UNIT_SYS_CONVERT(,temperature)
            PHYSICAL_UNIT_SYS_CONVERT(,velocity)
            PHYSICAL_UNIT_SYS_CONVERT(,pressure)
            PHYSICAL_UNIT_SYS_CONVERT(,momentum)
            PHYSICAL_UNIT_SYS_CONVERT(,angular_momentum)
            struct electric {
                PHYSICAL_UNIT_SYS_CONVERT(::electric,k)
                PHYSICAL_UNIT_SYS_CONVERT(::electric,potential)
                PHYSICAL_UNIT_SYS_CONVERT(::electric,field)
                PHYSICAL_UNIT_SYS_CONVERT(::electric,charge)
                PHYSICAL_UNIT_SYS_CONVERT(::electric,e)
                PHYSICAL_UNIT_SYS_CONVERT(::electric,current)
                PHYSICAL_UNIT_SYS_CONVERT(::electric,resistance)
                PHYSICAL_UNIT_SYS_CONVERT(::electric,conductance)
                PHYSICAL_UNIT_SYS_CONVERT(::electric,resistivity)
                PHYSICAL_UNIT_SYS_CONVERT(::electric,conductivity)
            }; /* electric */
            struct magnetic {
                PHYSICAL_UNIT_SYS_CONVERT(::magnetic,field)
                PHYSICAL_UNIT_SYS_CONVERT(::magnetic,flux)
            }; /* magnetic */
        }; /* convert struct */
    } /* namespace unit */

#undef PHYSICAL_UNIT_SYS_CONVERT
}/* namespace physical */

#endif // PHYSICAL_CONVERSION_H
