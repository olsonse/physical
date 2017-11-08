from physical.const import const;
import fluid;

import sys;
class British(const):
    def __init__(self,prefix,unit):
        const.__init__(self,prefix + 'British')

        #volume
        self.fluid = fluid.fluid(prefix + 'British.',unit)

        self.minim   = self.fluid.drachm / 60.0
        self.minims  = self.minim
        self.peck    = self.fluid.gallons * 2.0
        self.pecks   = self.peck
        self.pk      = self.peck
        self.bushel  = self.pecks * 4.0
        self.bushels = self.bushel
        self.bu      = self.bushel
        self.barrel  = self.fluid.gallons * 36.0
        self.barrels = self.barrel
        self.bbl     = self.barrel
        self.bl      = self.barrel

        #length
        self.cable_length  = unit.fathoms * 100.0
        self.cable_lengths = self.cable_length

        #mass
        self.hundredweight = unit.avoirdupois.pounds * 112.0
        self.cwt           = self.hundredweight
        self.quarter       = self.hundredweight / 4.0
        self.quarters      = self.quarter
        self.qr            = self.quarter
        self.ton           = self.hundredweight * 20.0
        self.tons          = self.ton
        self.tn            = self.ton


        # do some trickery to get modules set to instantiated classes
        # We expect each submodule to do likewise for those not already taken
        # care of here.
        self.fluid.__name__ = fluid.__name__
        sys.modules[fluid.__name__] = self.fluid
