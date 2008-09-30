from physical.const import const;

class geographical(const):
    def __init__(self,prefix,unit):
        const.__init__(self,prefix + 'geographical')

        self.mile = unit.nautical.mile;
        self.miles = self.mile;
        self.mi = self.mile;
