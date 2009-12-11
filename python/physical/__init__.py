from const import const;

import unit;
import units; # dummy module to overwrite for 'from units import' statements

import constant;
import constants;

import element;
import elements;

import sys
import Quantity

import license

"""
Released under MIT License:

Copyright (c) 2005-2009 Spencer E. Olson

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
"""
class _physical(const):
    def __init__(self):
        const.__init__(self,'physical');

        self.unit = unit.unit('physical.')
        self.units = self.unit

        self.constant = constant.constant('physical.', self.units)
        self.constants = self.constant

        self.element = element.element('physical.', self.constants, self.units)
        self.elements = self.element


        # do some trickery to get modules set to instantiated classes
        self.unit.__name__ = unit.__name__
        sys.modules[unit.__name__]=self.unit
        sys.modules[units.__name__]=self.unit

        self.constant.__name__ = constant.__name__
        sys.modules[constant.__name__]=self.constant
        sys.modules[constants.__name__]=self.constant

        self.element.__name__ = element.__name__
        sys.modules[element.__name__]=self.element
        sys.modules[elements.__name__]=self.element

        # add in the license file
        self.license = license

        # copy over the Quantity module so that the user can reference it.
        self.base = Quantity

sys.modules[__name__]=_physical()
