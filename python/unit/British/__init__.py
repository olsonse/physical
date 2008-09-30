from physical.const import const;
import fluid;

import sys;
class British(const):
    def __init__(self,prefix,unit):
        const.__init__(self,prefix + 'British')

        #volume
        self.fluid = fluid.fluid(prefix + 'British.',unit)

        self.peck = 2.0*self.fluid.gallons;
        self.pecks = self.peck;
        self.pk = self.peck;
        self.bushel = 4.0*self.pecks;
        self.bushels = self.bushel;
        self.bu = self.bushel;
        self.barrel = 36.0*self.fluid.gallons;
        self.barrels = self.barrel;
        self.bbl = self.barrel;
        self.bl = self.barrel;

        #length
        self.cable_length = 100.0*unit.fathoms;
        self.cable_lengths = self.cable_length;

        #mass
        self.hundredweight = 112.0*unit.avoirdupois.pounds;
        self.cwt = self.hundredweight;
        self.quarter = self.hundredweight/4.0;
        self.quarters = self.quarter;
        self.qr = self.quarter;
        self.ton = 20.0*self.hundredweight;
        self.tons = self.ton;
        self.tn = self.ton;


        # do some trickery to get modules set to instantiated classes
        # We expect each submodule to do likewise for those not already taken
        # care of here.
        self.fluid.__name__ = fluid.__name__
        sys.modules[fluid.__name__] = self.fluid
