from const import const;

import unit;
import units; # dummy module to overwrite for 'from units import' statements

import constant;
import constants;

import sys
import Quantity

class _physical(const):
    def __init__(self):
        const.__init__(self,'physical');

        self.unit = unit.unit('physical.')
        self.units = self.unit

        self.constant = constant.constant('physical.', self.units)
        self.constants = self.constant


        # do some trickery to get modules set to instantiated classes
        self.unit.__name__ = unit.__name__
        sys.modules[unit.__name__]=self.unit
        sys.modules[units.__name__]=self.unit

        self.constant.__name__ = constant.__name__
        sys.modules[constant.__name__]=self.constant
        sys.modules[constants.__name__]=self.constant

        # copy over the Quantity module so that the user can reference it.
        self.base = Quantity

sys.modules[__name__]=_physical()
