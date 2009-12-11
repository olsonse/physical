from physical.const import const
from physical.Quantity import Quantity

class Element(const):
    """
    Elemental data currently includes:
        Atomic number
        Atomic mass
        First ionization energy
    """

    def __init__(self, prefix, name, number, mass, ionization):
        const.__init__(self, prefix + name)
        self.number = number
        self.mass = mass
        self.ionization = ionization

    def __str__(self):
        return self._physname + '{\n' + \
                '  number    :  ' + str(self.number)     + '\n' + \
                '  mass      :  ' + str(self.mass)       + '\n' + \
                '  ionization:  ' + str(self.ionization) + '\n' + \
                '}'


class ElementMaker:
    """
    Callable helper class to create element instances.
    """

    def __init__(self, target, prefix, constants, units):
        self.target = target
        self.prefix = prefix
        self.constants = constants
        self.units = units

    def __call__(self, name, sym, n, m, i):
        number = Quantity(n, {}, 'atomic number of ' + name)

        mass = m * self.constants.amu
        mass.name = 'atomic mass of ' + name

        ionization = i * self.constants.eV
        ionization.name = 'ionization energy of ' + name

        e = Element(self.prefix, name, number, mass, ionization)
        setattr(self.target, name, e)
        setattr(self.target, sym, e)

class element(const):
    """
    Periodic table information.
    See http://physics.nist.gov/PhysRefData/Elements/index.html
    """
    def __init__(self, prefix, constant, unit):
        mkElement = ElementMaker(self, prefix + 'element.', constant, unit)

        mkElement('hydrogen',       'H',   1,       1.00794,     13.5984 )
        mkElement('helium',        'He',   2,       4.002602,    24.5874 )
        mkElement('lithium',       'Li',   3,       6.941,        5.3917 )
        mkElement('beryllium',     'Be',   4,       9.012182,     9.3227 )
        mkElement('boron',          'B',   5,      10.812,        8.2980 )
        mkElement('carbon',         'C',   6,      12.0107,      11.2603 )
        mkElement('nitrogen',       'N',   7,      14.0067,      14.5341 )
        mkElement('oxygen',         'O',   8,      15.9994,      13.6181 )
        mkElement('fluorine',       'F',   9,      18.9984032,   17.4228 )
        mkElement('neon',          'Ne',  10,      20.1797,      21.5645 )
        mkElement('sodium',        'Na',  11,      22.989770,     5.1391 )
        mkElement('magnesium',     'Mg',  12,      24.3051,       7.6462 )
        mkElement('aluminium',     'Al',  13,      26.981538,     5.9858 )
        mkElement('silicon',       'Si',  14,      28.0855,       8.1517 )
        mkElement('phosphorus',     'P',  15,      30.973761,    10.4867 )
        mkElement('sulfur',         'S',  16,      32.065,       10.3600 )
        mkElement('chlorine',      'Cl',  17,      35.453,       12.9676 )
        mkElement('argon',         'Ar',  18,      39.948,       15.7596 )
        mkElement('potassium',      'K',  19,      39.0983,       4.3407 )
        mkElement('calcium',       'Ca',  20,      40.078,        6.1132 )
        mkElement('scandium',      'Sc',  21,      44.955911,     6.5615 )
        mkElement('titanium',      'Ti',  22,      47.867,        6.8281 )
        mkElement('vanadium',       'V',  23,      50.9415,       6.7462 )
        mkElement('chromium',      'Cr',  24,      51.9961,       6.7665 )
        mkElement('manganese',     'Mn',  25,      54.9380499,    7.4340 )
        mkElement('iron',          'Fe',  26,      55.845,        7.9024 )
        mkElement('cobalt',        'Co',  27,      58.9332009,    7.8810 )
        mkElement('nickel',        'Ni',  28,      58.6934,       7.6398 )
        mkElement('copper',        'Cu',  29,      63.546,        7.7264 )
        mkElement('zinc',          'Zn',  30,      65.409,        9.3942 )
        mkElement('krypton',       'Kr',  36,      83.798,       13.9996 )
        mkElement('rubidium',      'Rb',  37,      85.4678,       4.1771 )
        mkElement('xenon',         'Xe',  54,     131.293,       12.1298 )
        mkElement('cesium',        'Cs',  55,     132.90545,      3.8939 )
        mkElement('mercury',       'Hg',  80,     200.59,        10.4375 )
        mkElement('francium',      'Fr',  87,     223,            4.0727 )

        const.__init__(self, prefix + 'element')

