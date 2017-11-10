from ..const import const

class bakers(const):
    def __init__(self,prefix,unit):
        const.__init__(self,prefix + 'bakers')

        self.dozen = 13.0
        self.doz = self.dozen
        self.dz = self.dozen

