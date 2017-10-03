#!/usr/bin/env python
# vim: ts=4:sw=4:tw=80:nowrap
"""
Utilities to help with interaction between the units of this package and those
from sympy.
"""

try:
    import sympy, sympy.physics
    has_sympy = True
except:
    has_sympy = False


def is_sympy(obj):
    return has_sympy and isinstance(obj, sympy.Basic)


def to_sympy(Q):
    """
    Translates the units Quantity type into a sympy expression using
    sympy.physics.units.
    """
    # first sort into pos or neg exponent (of units)
    expr = sympy.Float(Q.coeff)
    for unit, power in Q.units.iteritems():
      # the following lookup depends on the SI units being common
      # between physical package and sympy units
      expr *= getattr(sympy.physics.units,unit)**(power)

    return expr


def from_sympy(expr, zero_units=None):
    """
    Translates sympy expression into a physical.Quantity if possible.

    zero_units: if the value is equal to zero, sympy inappropriately eliminates
        the units.  If this is the case, scale the resultant zero by the given
        units.  If this is not specified, no scaling is performed.
    """
    if not expr.args:
        # this must be a simple expression, just convert via simple means
        if isinstance(expr, sympy.physics.units.Unit):
            # this is directly a simple, single unit
            return map_unit_to_Quantity(expr)

        if expr == 0:
            if zero_units is not None:
                return 0*zero_units
            print 'WARNING: returning zero with no units'
            return 0

        if isinstance(expr, sympy.Integer):
            return int(expr)

        # otherwise, we'll just try a float conversion
        return float(expr)

    if not isinstance(expr, sympy.Mul):
        raise TypeError('Do not know how to convert "{}" to physical.Quantity'
                        .format(type(expr)))

    # Each sympy expression that is a valid physical quantity must be a
    # multiplication of a coefficient and a bunch of units to optional various
    # powers
    ans = 1.0
    for arg in expr.args:
        if   isinstance(arg, sympy.Number):
            ans *= float(arg)
        elif isinstance(arg, sympy.physics.units.Unit):
            ans *= map_unit_to_Quantity(arg)
        elif isinstance(arg, sympy.Pow):
            u, p = arg.args
            if not isinstance(u, sympy.physics.units.Unit):
                raise TypeError('Expected only coefficients and units')
            ans *= map_unit_to_Quantity(u)**float(p)
        else:
            raise TypeError('Expected only coefficients and units')

    return ans


def map_unit_to_Quantity(U):
    """
    convert a single sympy.physical.units.Unit quantity to physical.Quantity.
    This should be a simple lookup, except that sympy does not capitalize units
    that are named after a person.
    """
    import physical
    name = str(U)
    if hasattr(physical.unit, name):
        return getattr(physical.unit, name)

    name = name[0].upper() + name[1:]
    return getattr(physical.unit, name)
