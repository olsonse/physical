from physical.const import const;

class Hefner(const):
    def __init__(self,prefix,unit):
        const.__init__(self,prefix + 'Hefner')

        self.candle  = 0.9*unit.candles;
        self.candles = self.candle;
