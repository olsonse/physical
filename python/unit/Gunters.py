from physical.const import const;

class Gunters(const):
    def __init__(self,prefix,unit):
        const.__init__(self,prefix + 'Gunters')
        # English Units
        # length

        self.chain = unit.chain;
        self.chains = self.chain;
