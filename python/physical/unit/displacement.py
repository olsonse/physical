from ..const import const

class displacement(const):
    def __init__(self,prefix,unit):
        const.__init__(self,prefix + 'displacement')

        self.ton = unit.stere
        self.tons = self.ton
        self.t = self.ton
