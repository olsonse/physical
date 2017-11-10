from ...const import const
from . import liquid
from . import dry

import sys
class US(const):
    def __init__(self,prefix,unit):
        const.__init__(self,prefix + 'US')

        #length
        self.cable_length = 120.0*unit.fathoms
        self.cable_lengths = self.cable_length

        #mass
        # short
        self.hundredweight = 100.0*unit.avoirdupois.pounds
        self.cwt = self.hundredweight
        self.quarter = self.hundredweight/4.0
        self.quarters = self.quarter
        self.qr = self.quarter
        self.ton = 20.0*self.hundredweight
        self.tons = self.ton
        self.tn = self.ton
        self.deadweight = self.ton

        #volume
        self.liquid = liquid.liquid(prefix + 'US.', unit)
        self.fluid = self.liquid

        self.dry = dry.dry(prefix + 'US.', unit)

        self.minim        = self.fluid.dram/60.
        self.minims       = self.minim
        self.peck         = 8.0*self.dry.quarts
        self.pecks        = self.peck
        self.pk           = self.peck
        self.bushel       = 4.0*self.pecks
        self.bushels      = self.bushel
        self.bu           = self.bushel
        self.barrel       = 31.5*self.liquid.gallons
        self.barrels      = self.barrel
        self.bbl          = self.barrel
        self.bl           = self.barrel


        # do some trickery to get modules set to instantiated classes
        # We expect each submodule to do likewise for those not already taken
        # care of here.
        self.liquid.__name__ = liquid.__name__
        sys.modules[liquid.__name__] = self.liquid
        sys.modules[liquid.__name__.replace('.liquid', '.fluid')] = self.liquid

        self.dry.__name__ = dry.__name__
        sys.modules[dry.__name__] = self.dry
