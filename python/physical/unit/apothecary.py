from ..const import const

class apothecary(const):
    def __init__(self,prefix,unit):
        const.__init__(self,prefix + 'apothecary')

        # weight
        self.scruple         = 20.0*unit.grains
        self.scruples        = self.scruple
        self.s               = self.scruple
        self.dram            = 3.0*self.scruples
        self.drams           = self.dram
        self.dr              = self.dram
        self.ounce           = 8.0*self.drams
        self.ounces          = self.ounce
        self.oz              = self.ounce
        self.pound           = 12.0*self.ounces
        self.pounds          = self.pound
        self.lb              = self.pound

