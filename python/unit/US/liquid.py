from physical.const import const;

class liquid(const):
    def __init__(self,prefix,unit):
        const.__init__(self,prefix + 'liquid')

        self.dram       = 60.0*unit.minims;
        self.drams      =     self.dram;
        self.dr         =     self.dram;
        self.ounce      = 8.0*self.drams;
        self.ounces     =     self.ounce;
        self.oz         =     self.ounce;
        self.gill       = 4.0*self.ounces;
        self.gills      =     self.gill;
        self.gl         =     self.gill;
        self.pint       = 4.0*self.gills;
        self.pints      =     self.pint;
        self.pt         =     self.pint;
        self.quart      = 2.0*self.pints;
        self.quarts     =     self.quart;
        self.qt         =     self.quart;
        self.magnum     = 2.0*self.quarts;
        self.magnums    =     self.magnum;
        self.gallon     = 4.0*self.quarts;
        self.gallons    =     self.gallon;
        self.gal        =     self.gallon;
