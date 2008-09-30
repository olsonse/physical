from physical.const import const;

class admiralty(const):
    def __init__(self,prefix,unit):
        const.__init__(self,prefix + 'admiralty')

        #speed
        self.knot = 6980.0*unit.feet/unit.hour;
        self.knots = self.knot;
