from ...const import const

class centesimal(const):
    def __init__(self,prefix,arc):
        const.__init__(self,prefix + 'centesimal')

        self.minute = arc.grade/100.0
        self.minutes = self.minute
        self.min = self.minute
        self.second = arc.grade/10000.0
        self.seconds = self.second
        self.sec = self.second

