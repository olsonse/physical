from physical.const import const;
from unit import unit;

class constant(const):
    def __init__(self,prefix, unit):
        const.__init__(self,prefix + 'constant')

        # speed of light
        self.c = 2.99792458e8*unit.meters/unit.second;

        # speed of sound
        self.Mach = 331.46*unit.meters/unit.second;

        # Planck constant
        self.h = 6.6260755e-34*unit.Joule*unit.seconds;
        self.h_bar = self.h/(2.0*unit.pi);

        # standard gravitational acceleration at sea level
        self.g = unit.gravity;

        # electron charge
        self.e = 1.60217733e-19*unit.Coulombs;

        #          energy
        # electron Volt
        self.eV = self.e*unit.V;
        self.keV = 1000.0*self.eV;
        self.MeV = 1000000.0*self.eV;
        self.GeV = 1000000000.0*self.eV;
        self.Rydberg = 13.6054*self.eV;
        self.Rydbergs = self.Rydberg;

        #          mass
        # electron mass
        self.m_e = 9.1093897e-31*unit.kilograms;
        # proton mass
        self.m_P = 1.6726231e-27*unit.kilograms;
        # deuteron mass
        self.m_D = 1875.61339*self.MeV/(self.c*self.c);
        # unified atomic mass unit
        self.atomic_mass_unit = 1.6605402e-27*unit.kilograms;
        self.atomic_mass_units = self.atomic_mass_unit;
        self.amu = self.atomic_mass_unit;
        self.Dalton = self.atomic_mass_unit;
        self.Daltons = self.Dalton;

        # permittivity of free space
        self.epsilon = 8.854187817e-12*unit.Farads/unit.meter;
        # permeability of free space
        self.mu = 12.566370614e-7*unit.Newtons/(unit.A*unit.A);
        # fine-structure constant
        self.alpha = 1.0/137.0359895;
        # classical electron radius
        self.r_e = 2.81794092e-15*unit.meters;
        # electron Compton wavelength
        self.lambda_bar = 3.86159323e-13*unit.meters;
        # Bohr radius
        self.a_0 = 0.529177249e-10*unit.meters;
        # wavelength of 1 eV/c particle
        self.lambda_1eV = 1.23984244e-6*unit.meters;
        # Thomson cross section
        self.sigma_0 = 0.66524616*unit.barns;
        # Bohr magnetron
        self.mu_B = 5.78838263e-11*self.MeV/unit.Tesla;
        # nuclear magnetron
        self.mu_N = 3.15245166e-14*self.MeV/unit.Tesla;
        # electron cyclotron frequency/field
        self.E_M_e = 1.75881962e11*unit.C/unit.kg*(unit.rad/(unit.s*unit.T));
        # proton cyclotron frequency/field
        self.E_M_P = 9.5788309e7*unit.C/unit.kg*(unit.rad/(unit.s*unit.T));
        # gravitational constant
        self.G = 6.67259e-11*unit.m*unit.m*unit.m/(unit.kg*unit.s*unit.s);
        # Avogadro's constant
        self.N_A = 6.0221367e23;
        # Boltzmann constant
        self.K_B = 1.380658e-23*unit.Joules/unit.Kelvin;
        # molar volume, ideal gas at standard temperature and pressure
        self.V_molar = 2.897756e-3*unit.meter*unit.Kelvins;
        # Stefan-Boltzmann constant
        self.sigma_SB = 5.67051e-8*unit.W/(unit.m*unit.m*unit.K*unit.K*unit.K*unit.K);

