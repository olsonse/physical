from physical.const import const;

class metric(const):
    def __init__(self,prefix,unit):
        const.__init__(self,prefix + 'metric')

        # mass
        self.carat = unit.gram/5.0;
        self.carats = self.carat;
        self.ton = 1000.0*unit.kilograms;
        self.tons = self.ton;
        self.t = self.ton;
