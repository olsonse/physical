from ..const import const

class statute(const):
    def __init__(self,prefix,unit):
        const.__init__(self,prefix + 'statute')

        self.mile    = 5280.0*unit.feet
        self.miles   = self.mile
        self.mi      = self.mile
        self.league  = 3.0*self.miles
        self.leagues = self.league
