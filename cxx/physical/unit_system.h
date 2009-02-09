#ifndef PHYSICAL_CONVERSION_H
#define PHYSICAL_CONVERSION_H

#include <physical/physical.h>

#warning "This set of unit system conversions is not yet complete or necessarily accurate.  Please check before using."

namespace physical {
    namespace unit_system {
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
    }/*namespace unit_system */
}

#endif // PHYSICAL_CONVERSION_H
