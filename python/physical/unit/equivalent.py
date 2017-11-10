from ..const import const

class equivalent(const):
    def __init__(self,prefix,unit):
        const.__init__(self,prefix + 'equivalent')

        # light intensity
        self.lux = unit.lux/unit.pi
        self.luxes = self.lux
        self.luces = self.lux
        self.lx = self.lux
        self.lumen = unit.lumen/unit.pi
        self.lumens = self.lumen
        self.lm = self.lumen
        self.phot = unit.apostilb/unit.pi
        self.phots = self.phot

        self.foot_candle     = unit.foot_candle/unit.pi
        self.foot_candles    = self.foot_candle
        self.fc              = self.foot_candle
