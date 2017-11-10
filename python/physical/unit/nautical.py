from ..const import const

class nautical(const):
    def __init__(self,prefix,unit):
        const.__init__(self,prefix + 'nautical')

        self.mile      = 1852*unit.meters
        self.miles     = self.mile
        self.nm        = self.mile
        self.league    = 3.0*self.miles
        self.leagues   = self.league
