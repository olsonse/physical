from ..const import const

class avoirdupois(const):
    def __init__(self,prefix,unit):
        const.__init__(self,prefix + 'avoirdupois')

        # weight
        self.pound   = 7000.0*unit.grains
        self.pounds  = self.pound
        self.lb      = self.pound
        self.ounce   = self.pound/16.0
        self.ounces  = self.ounce
        self.oz      = self.ounce
        self.dram    = self.ounce/16.0
        self.drams   = self.dram
        self.dr      = self.dram
