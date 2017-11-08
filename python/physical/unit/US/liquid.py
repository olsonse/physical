from physical.const import const;

class liquid(const):
    def __init__(self,prefix,unit):
        const.__init__(self,prefix + 'liquid')

        self.gallon  = 231*unit.inches**3
        self.gallons = self.gallon
        self.gal     = self.gallon
        self.quart   = self.gallon / 4.0
        self.quarts  = self.quart
        self.qt      = self.quart
        self.pint    = self.quart / 2.0
        self.pints   = self.pint
        self.pt      = self.pint
        self.gill    = self.pint / 4.0
        self.gills   = self.gill
        self.gl      = self.gill
        self.ounce   = self.pint / 16.0
        self.ounces  = self.ounce
        self.oz      = self.ounce
        self.dram    = self.ounce / 16.0
        self.drams   = self.dram
        self.dr      = self.dram
