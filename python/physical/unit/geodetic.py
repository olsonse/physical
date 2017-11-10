from ..const import const

class geodetic(const):
    def __init__(self,prefix,unit):
        const.__init__(self,prefix + 'geodetic')

        self.foot = (1200.0/3937.0)*unit.meters
        self.feet = self.foot
        self.ft = self.foot
