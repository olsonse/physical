from physical.const import const;
from unit import unit;
from physical.Quantity import Quantity;

class constant(const):
    """
    Various constants, most of which have been pulled in May 2009 from
    http://physics.nist.gov/cuu/Constants/index.html.
    """
    def __init__(self,prefix, unit):
        const.__init__(self,prefix + 'constant')

        self.pi = Quantity(unit.pi.coeff, {}, 'unitless pi constant')

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
        self.Rinfinity = 10973731.568527/unit.m;
        self.Rinfinity.name = 'Rydberg constant (R_inf)';
        self.Rydberg = self.h * self.c * self.Rinfinity;
        self.Rydberg.name = 'Rydberg energy';
        self.Rydbergs = self.Rydberg;
        self.Hartree = 2. * self.Rydberg;
        self.Hartree.name = 'Atomic energy unit';
        self.Hartrees = self.Hartree;

        #          mass
        # electron mass
        self.m_e = 9.10938215e-31*unit.kilograms;
        self.m_e.name = 'electron mass';
        # proton mass
        self.m_p = 1.672621637e-27*unit.kilograms;
        self.m_p.name = 'proton mass';
        # deuteron mass
        self.m_d = 1875.612793*self.MeV/(self.c*self.c);
        self.m_d.name = 'deuteron mass';

        # unified atomic mass unit
        self.atomic_mass_unit = 1.660538782e-27*unit.kilograms;
        self.atomic_mass_unit.name = 'unified atomic mass unit';
        self.atomic_mass_units = self.atomic_mass_unit;
        self.amu = self.atomic_mass_unit;
        self.Dalton = self.atomic_mass_unit;
        self.Daltons = self.Dalton;

        self.epsilon0 = 8.854187817e-12*unit.Farads/unit.meter;
        self.epsilon0.name = 'permittivity of free space';

        self.k_E = 1. / ( 4. * self.pi * self.epsilon0 );
        self.k_E.name = 'Coulomb constant';

        self.mu0 = 4 * self.pi * 1e-7 * unit.Newtons / unit.A**2;
        self.mu0.name = 'permeability of free space';

        self.alpha = Quantity(7.2973525376e-3,  {}, 'fine-structure constant')
        self.g_e   = Quantity(-2.0023193043622, {}, 'electron g-factor')
        self.g_d   = Quantity(0.8574382308,     {}, 'deuteron g-factor')

        self.r_e = 2.81794092e-15*unit.meters;
        self.r_e.name = 'classical electron radius';

        self.lambda_C = self.h / (self.m_e * self.c);
        self.lambda_C.name = 'Compton wavelength';

        self.lambda_C_bar = self.lambda_C / (2 *unit.pi);
        self.lambda_C_bar.name = 'Compton wavelength (over 2pi)';

        self.a_0 = self.alpha / (4*self.pi * self.Rinfinity);
        self.a_0.name = 'Bohr radius';

        self.lambda_1eV = self.h / (self.eV / self.c);
        self.lambda_1eV.name = 'wavelength of 1 eV/c particle';

        self.sigma_0 = 0.6652458558*unit.barns;
        self.sigma_0.name = 'Thomson cross section';

        self.mu_B = 5.7883818e-11*self.MeV/unit.Tesla;
        self.mu_B.name = 'Bohr magnetron';

        self.mu_N = 3.1524513e-14*self.MeV/unit.Tesla;
        self.mu_N.name = 'nuclear magnetron';

        self.e_m_e = self.e / self.m_e;
        self.e_m_e.name = 'electron cyclotron frequency/field';

        self.e_m_p = self.e / self.m_p;
        self.e_m_p.name = 'proton cyclotron frequency/field';

        self.G = 6.67428e-11* unit.m**3 /(unit.kg * unit.s**2);
        self.G.name = 'gravitational constant';

        self.N_A = Quantity(6.02214179e23, {}, "Avogadro's constant")

        self.K_B = 1.3806504e-23*unit.Joules/unit.Kelvin;
        self.K_B.name = 'Boltzmann constant';

        self.stdtemp = 273.15 * unit.Kelvin;
        self.stdtemp.name = 'standard temperature';

        self.R = self.K_B * self.N_A;
        self.R.name = 'universal gas constant';

        self.V_molar = self.R * self.stdtemp / unit.atm
        self.V_molar.name = 'molar volume, ideal gas, 273.15 K, 101.325 kPa'

        self.n_0 = self.N_A / self.V_molar
        self.n_0.name = 'Loschmidt constant, ideal gas, 273.15 K, 101.325 kPa'

        self.sigma_SB = 5.670400e-8*unit.W/(unit.m**2 * unit.K**4);
        self.sigma_SB.name = 'Stefan-Boltzmann constant';

        self.z0 = self.c * self.mu0
        self.z0.name = 'impedance of free space'
