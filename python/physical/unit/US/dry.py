from ...const import const

class dry(const):
    def __init__(self,prefix,unit):
        const.__init__(self,prefix + 'dry')

        self.pint     = 550.61047*unit.cc
        self.pints    =     self.pint
        self.pt       =     self.pint
        self.quart    = 2.0*self.pints
        self.quarts   =     self.quart
        self.qt       =     self.quart
