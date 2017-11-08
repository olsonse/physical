from physical.const import const;

class fluid(const):
    def __init__(self,prefix,unit):
        const.__init__(self,prefix + 'fluid')

        self.gallon        = 4.54609 * unit.liters
        self.gallons       = self.gallon
        self.gal           = self.gallon
        self.quart         = self.gallon / 4.0
        self.quarts        = self.quart
        self.qt            = self.quart
        self.pint          = self.quart / 2.0
        self.pints         = self.pint
        self.pt            = self.pint
        self.gill          = self.pint / 4.0
        self.gills         = self.gill
        self.gl            = self.gill
        self.ounce         = self.pint / 20.0
        self.ounces        = self.ounce
        self.oz            = self.ounce
        self.drachm        = self.ounce / 8.0
        self.drachms       = self.drachm
        self.dr            = self.drachm
        self.reputedquart  = self.quart * (2.0/3.0)
        self.reputedquarts = self.reputedquart
        self.reputedpint   = self.reputedquart / 2.0
        self.reputedpints  = self.reputedpint
        self.magnum        = self.reputedquarts * 2.0
        self.magnums       = self.magnum
