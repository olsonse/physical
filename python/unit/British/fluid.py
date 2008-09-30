from physical.const import const;

class fluid(const):
    def __init__(self,prefix,unit):
        const.__init__(self,prefix + 'fluid')

            #volume
        self.drachm = 60.0*unit.minims;
        self.drachms = self.drachm;
        self.dr = self.drachm;
        self.ounce = 8.0*self.drachms;
        self.ounces = self.ounce;
        self.oz = self.ounce;
        self.gill = 5.0*self.ounces;
        self.gills = self.gill;
        self.gi = self.gill;
        self.pint = 4.0*self.gills;
        self.pints = self.pint;
        self.pt = self.pint;
        self.quart = 2.0*self.pints;
        self.quarts = self.quart;
        self.qt = self.quart;
        self.gallon = 4.0*self.quarts;
        self.gallons = self.gallon;
        self.gal = self.gallon;

