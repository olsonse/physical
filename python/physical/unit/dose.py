from ..const import const

class dose(const):
    def __init__(self,prefix,unit):
        const.__init__(self,prefix + 'dose')

        # energy
        self.Gray = unit.Joule/unit.kilogram
        self.Grays = self.Gray
        self.Gy = self.Gray
        self.Sievert = self.Gray
        self.Sieverts = self.Sievert
        self.rad = self.Gray/100.0
        self.rads = self.rad
        self.rd = self.rad
