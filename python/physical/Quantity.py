from exceptions import RuntimeError


UnitsMismatch = 'Units mismatch:  cannot add/subtract/compare mismatched units'
UnitsNotRoot  = 'Units not root:  cannot take non-even root of units'
UnitsNotDimensionless = 'Units not dimensionless:  cannot create non-even powers of unit'


class Quantity(object):
    """
    This is the documentation for a physical Quantity.
    """

    def __init__(self,coeff,units,name=None):
        self.name = name
        self.coeff = 1. * coeff
        self.units = units.copy()
        for k in self.units.keys():
            if self.units[k] == 0:
                del self.units[k]

    def __repr__(self):
        # first sort into pos or neg exponent (of units)
        utuples = self.units.items()
        # insert marker tuple
        marker = ('--',0)
        utuples.append(marker)
        utuples.sort(lambda (k1,v1),(k2,v2): cmp(v2,0))

        # find marker
        mi = utuples.index(marker)

        # separate into separate tuples and then sort lexically
        putuples = utuples[:mi]
        nutuples = utuples[(mi+1):]
        putuples.sort(lambda (k1,v1),(k2,v2): cmp(k1,k2))
        nutuples.sort(lambda (k1,v1),(k2,v2): cmp(k1,k2))

        str = '<%g' % self.coeff

        # numerator first
        for u,e in putuples:
            str = str + ' ' + u
            if e != 1:
                str = str + '^' + `e`

        # now denominator
        if nutuples != []:
            str = str + ' /'

        for u,e in nutuples:
            str = str + ' ' + u
            if e != -1:
                str = str + '^' + `-e`

        str = str + '>'

        if self.name is not None:
            str = str + ' (' + self.name + ')'

        return str

    def __add__(self,other):
        um = self.unitsMatch(other)
        if um < 0:
            return self.coeff + other
        elif um == 0:
            return self.coeff + other.coeff
        else:
            return Quantity(self.coeff + other.coeff, self.units)

    def __sub__(self,other):
        um = self.unitsMatch(other)
        if um < 0:
            return self.coeff - other
        elif um == 0:
            return self.coeff - other.coeff
        else:
            return Quantity(self.coeff - other.coeff, self.units)

    def __cmp__(self,other):
        um = self.unitsMatch(other)
        if um < 0:
            return cmp(self.coeff, other)
        elif um == 0:
            return cmp(self.coeff, other.coeff)
        else:
            return cmp(self.coeff, other.coeff)

    def __mul__(self,other):
        if other.__class__ == Quantity:
            c = 1. * self.coeff * other.coeff
            u = self.multUnits(other, 1)
            if u.keys() == [ ]:
                return c
            return Quantity(c, u)
        else:
            # implicitly call either other.__mul__ or self.__rmul__
            # other.__mul__ should be automatically called for more complex
            # types, such as numpy.ndarray.  For basic types (int,float,...),
            # self.__rmul__ should be called. 
            return other * self

    def __rmul__(self,other):
        # we are assuming that if __rmul__ was called, other must be a
        # fundamental numeric type.  Otherwise, other.__mul__ should have been
        # called (which might in turn call Quantity.__rmul__).  This works for
        # instance if we do (Quantity)*(numpy.ndarray).
        if self.units.keys() == [ ]:
            # so, self is not actually a unit... flatten
            return other * self.coeff
        return Quantity(other * self.coeff, self.units)

    # assume that the type in coeff supports truediv
    def __truediv__(self,other):
        return self.__div__(other)

    # assume that the type in coeff supports truediv
    def __rtruediv__(self,other):
        return self.__rdiv__(other)

    def __div__(self,other):
        """ Quantity / other """
        try:
            c = 1. * self.coeff / other.coeff
            u = self.multUnits(other, -1)
        except AttributeError:
            c = 1. * self.coeff / other
            u = self.units
        if u.keys() == [ ]:
            return c
        else:
            return Quantity(c, u)

    def __rdiv__(self,other):
        """ other / Quantity """
        c = other / self.coeff
        u = self.units.copy()
        for k in u.keys():
            u[k] = -u[k]
        if u.keys() == [ ]:
            return c
        return Quantity(c, u)

    def __pow__(self,exponent):
        # now loop through each of the units and try to divide/multiply the
        # power by the 'exponent'.  Throw an exception of this is not
        # possible. 
        if exponent == 0:
            return 1

        u = self.units.copy()
        fexp = float(abs(exponent))
        for k in u.keys():
            if fexp < 1:
                if ((float(u[k]) % (1.0/fexp)) != 0):
                    raise RuntimeError(UnitsNotRoot)
            elif (int(fexp) - fexp) != 0:
                raise RuntimeError(UnitsNotDimensionless)
            u[k] = int(u[k] * exponent)

        c  = self.coeff ** exponent
        if u.keys() == [ ]:
            return c
        return Quantity(c, u)

    def __neg__(self):
        if self.units.keys() == [ ]:
            return -self.coeff
        return Quantity(-self.coeff, self.units)

    def __abs__(self):
        if self.units.keys() == [ ]:
            return abs(self.coeff)
        return Quantity(abs(self.coeff), self.units)

    def __complex__(self):
        return complex(self.coeff)

    def __float__(self):
        return float(self.coeff)

    def __int__(self):
        return int(self.coeff)

    def __long__(self):
        return long(self.coeff)

    def multUnits(self,other,n):
        u = self.units.copy()
        for k in u.keys():
            if k in other.units.keys():
                u[k] = u[k] + n * other.units[k]
        for k in other.units.keys():
            if k not in u.keys():
                u[k] = n * other.units[k]
        for k in u.keys():
            if u[k] == 0:
                del u[k]
        return u

    def unitsMatch(self,other,msg=UnitsMismatch):
        """
        Compares units of two quantities to see if they match.
        If both items are of type Quantity and they match return 1
        If only one is a unit then:
            1. raise an exception if this Quantity has non-null units
            or
            2. return -1 if this Quantity has null units.
        If both are of type Quantity, and...
            1. both are of an empty type, return 0
            2. only one is an empty type, raise an exception
        """
        if other.__class__ != Quantity:
            if self.units.keys() == [ ]:
                # Neither are really Quantity types, so we'll just
                # give a softer indicator than an exception
                return -1
            raise RuntimeError(msg)

        if self.units.keys() == [ ] and other.units.keys() == [ ]:
            # Neither are really Quantity types, so we'll just
            # give a soft indicator of 'equal enough'
            return 0

        if self.units != other.units:
            raise RuntimeError(msg)
        return 1

