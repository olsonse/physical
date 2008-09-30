from physical.const import const;
from unit import unit;
from physical.Quantity import Quantity;

class constant(const):
    def __init__(self,prefix, unit):
        const.__init__(self,prefix + 'constant')

        self.c = 2.99792458e8*unit.meters/unit.second;
        self.c.name = 'speed of light';

        self.Mach = 331.46*unit.meters/unit.second;
        self.Mach.name = 'speed of sound';

        self.h = 6.6260755e-34*unit.Joule*unit.seconds;
        self.h.name = 'Planck constant';

        self.h_bar = self.h/(2.0*unit.pi);
        self.h_bar.name = 'Planck constant';

        self.g = unit.gravity;
        self.g.name = 'standard gravitational acceleration at sea level';

        self.e = 1.60217733e-19*unit.Coulombs;
        self.e.name =  'electron charge';

        #          energy
        # electron Volt
        self.eV = self.e*unit.V;
        self.eV.name = 'electron Volt';
        self.keV = 1000.0*self.eV;
        self.keV.name = 'kilo-electron Volt';
        self.MeV = 1000000.0*self.eV;
        self.MeV.name = 'Mega-electron Volt';
        self.GeV = 1000000000.0*self.eV;
        self.GeV.name = 'Giga-electron Volt';
        self.Rydberg = 13.6054*self.eV;
        self.Rydberg.name = 'Rydberg energy';
        self.Rydbergs = self.Rydberg;

        #          mass
        # electron mass
        self.m_e = 9.1093897e-31*unit.kilograms;
        self.m_e.name = 'electron mass';
        # proton mass
        self.m_P = 1.6726231e-27*unit.kilograms;
        self.m_P.name = 'proton mass';
        # deuteron mass
        self.m_D = 1875.61339*self.MeV/(self.c*self.c);
        self.m_D.name = 'deuteron mass';

        # unified atomic mass unit
        self.atomic_mass_unit = 1.6605402e-27*unit.kilograms;
        self.atomic_mass_unit.name = 'unified atomic mass unit';
        self.atomic_mass_units = self.atomic_mass_unit;
        self.amu = self.atomic_mass_unit;
        self.Dalton = self.atomic_mass_unit;
        self.Daltons = self.Dalton;

        self.epsilon = 8.854187817e-12*unit.Farads/unit.meter;
        self.epsilon.name = 'permittivity of free space';

        self.mu = 12.566370614e-7*unit.Newtons/(unit.A*unit.A);
        self.mu.name = 'permeability of free space';

        self.alpha = Quantity(1.0/137.0359895,{});
        self.alpha.name = 'fine-structure constant';

        self.r_e = 2.81794092e-15*unit.meters;
        self.r_e.name = 'classical electron radius';

        self.lambda_bar = 3.86159323e-13*unit.meters;
        self.lambda_bar.name = 'electron Compton wavelength';

        self.a_0 = 0.529177249e-10*unit.meters;
        self.a_0.name = 'Bohr radius';

        self.lambda_1eV = 1.23984244e-6*unit.meters;
        self.lambda_1eV.name = 'wavelength of 1 eV/c particle';

        self.sigma_0 = 0.66524616*unit.barns;
        self.sigma_0.name = 'Thomson cross section';

        self.mu_B = 5.78838263e-11*self.MeV/unit.Tesla;
        self.mu_B.name = 'Bohr magnetron';

        self.mu_N = 3.15245166e-14*self.MeV/unit.Tesla;
        self.mu_N.name = 'nuclear magnetron';

        self.E_M_e = 1.75881962e11*unit.C/unit.kg*(unit.rad/(unit.s*unit.T));
        self.E_M_e.name = 'electron cyclotron frequency/field';

        self.E_M_P = 9.5788309e7*unit.C/unit.kg*(unit.rad/(unit.s*unit.T));
        self.E_M_P.name = 'proton cyclotron frequency/field';

        self.G = 6.67259e-11*unit.m*unit.m*unit.m/(unit.kg*unit.s*unit.s);
        self.G.name = 'gravitational constant';

        self.N_A = Quantity(6.0221367e23,{});
        self.N_A.name = 'Avogadro\'s constant';

        self.K_B = 1.380658e-23*unit.Joules/unit.Kelvin;
        self.K_B.name = 'Boltzmann constant';

        self.V_molar = 2.897756e-3*unit.meter*unit.Kelvins;
        self.V_molar.name = 'molar volume, ideal gas at standard temperature and pressure';

        self.sigma_SB = 5.67051e-8*unit.W/(unit.m*unit.m*unit.K*unit.K*unit.K*unit.K);
        self.sigma_SB.name = 'Stefan-Boltzmann constant';

