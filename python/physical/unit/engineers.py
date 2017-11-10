from ..const import const

class engineers(const):
    def __init__(self,prefix,unit):
        const.__init__(self,prefix + 'engineers')

        # English Units
        # length
        self.link = unit.foot
        self.links = self.link
        self.chain = 100.0*unit.feet
        self.chains = self.chain
