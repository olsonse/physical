from physical.const import const;
import centesimal;

import sys;
class arc(const):
    def __init__(self,prefix,unit):
        const.__init__(self,prefix + 'arc')

        self.degree      = unit.pi/180.0;
        self.degrees     = self.degree;
        self.minute      = self.degree/60.0;
        self.minutes     = self.minute;
        self.min         = self.minute;
        self.second      = self.minute/60.0;
        self.seconds     = self.second;
        self.sec         = self.second;
        self.grade       = 0.9*self.degrees;
        self.grades      = self.grade;

        self.centesimal = centesimal.centesimal(prefix + "arc.",self)

        # do some trickery to get modules set to instantiated classes
        # We expect each submodule to do likewise for those not already taken
        # care of here.
        self.centesimal.__name__ = centesimal.__name__
        sys.modules[centesimal.__name__] = self.centesimal
