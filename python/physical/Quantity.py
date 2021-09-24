from math import log10, isclose

from . import sympy_util


UnitsMismatch = 'Units mismatch:  cannot add/subtract/compare mismatched units ({} != {})'
UnitsNotRoot  = 'Units not root:  cannot take non-even root of units ({})'
UnitsNotDimensionless = 'Units not dimensionless:  cannot create non-integer powers of unit ({})'


class pretty_print:
    def __init__(self, precision=15):
        self.precision = precision

    def set_precision(self, precision):
        self.precision = precision

    def get_name(self):
        return ('pretty',{'precision': self.precision})

    def __call__(self, Q):
        # first sort into pos or neg exponent (of units)
        utuples = list(Q.units.items())
        # insert marker tuple
        marker = ('--',0)
        utuples.append(marker)
        utuples.sort(key = lambda u: -u[1])

        # find marker
        mi = utuples.index(marker)

        # separate into separate tuples and then sort lexically
        putuples = utuples[:mi]
        nutuples = utuples[(mi+1):]
        putuples.sort(key = lambda u: u[0])
        nutuples.sort(key = lambda u: u[0])

        U = ''

        # numerator first
        sep = ''
        for u,e in putuples:
            U += sep + u
            sep = ' '
            if e != 1:
                U += '^' + repr(e)

        # now denominator
        if nutuples != []:
            U += ' /'

        for u,e in nutuples:
            U += sep + u
            sep = ' '
            if e != -1:
                U += '^' + repr(-e)

        name = ''
        if Q.name is not None:
            name = ' (' + Q.name + ')'

        return Q.fmt.format(coeff=Q.coeff, precision=self.precision, units=U,
                            name=name)


class math_print:
    def __init__(self, precision=12, omit_outside_parens=False):
        self.precision = precision
        self.omit_parens = omit_outside_parens

    def set_precision(self, precision):
        self.precision = precision

    def get_name(self):
        return ('math',
                {'precision':self.precision,
                 'omit_outside_parens':self.omit_parens,
                }
               )

    def __call__(self, Q):
        # first sort into pos or neg exponent (of units)
        utuples = list(Q.units.items())
        # insert marker tuple
        marker = ('--',0)
        utuples.append(marker)
        utuples.sort(key = lambda u: -u[1])

        # find marker
        mi = utuples.index(marker)

        # separate into separate tuples and then sort lexically
        putuples = utuples[:mi]
        nutuples = utuples[(mi+1):]
        putuples.sort(key = lambda u: u[0])
        nutuples.sort(key = lambda u: u[0])

        if not self.omit_parens:
          U = '('
        else:
          U = ''
        U += '{C:.{P}}'.format(C=Q.coeff,P=self.precision)

        # numerator first
        if putuples:
          U += ' * '
          sep = ''
          for u,e in putuples:
              U += sep + u
              sep = ' * '
              if e != 1:
                  U += '**' + repr(e)

        # now denominator
        if nutuples:
            if len(nutuples) > 1:
                U += ' / ('
            else:
                U += ' / '

            sep = ''
            for u,e in nutuples:
                U += sep + u
                sep = ' * '
                if e != -1:
                    U += '**' + repr(-e)

            if len(nutuples) > 1:
                U += ')'
        if not self.omit_parens:
          U += ')'

        return U

class latex_print:
    def __init__(self, precision=12, oneline=True):
        self.precision = precision
        self.oneline = oneline

    def set_precision(self, precision):
        self.precision = precision

    def get_name(self):
        return ('latex',
                {'precision':self.precision,
                 'oneline':self.oneline,
                }
               )

    def print_coeff(self, C):
        decade = int( log10( abs(C) ) )
        if ( abs(decade) >= 3):
            sig_figs = C / 10.0**decade
            return '{sf:.{P}} \\times 10^{{{D}}}' \
                   .format(sf=sig_figs,P=self.precision,D=decade)
        else:
            return '{C:.{P}}'.format(C=C, P=self.precision)


    def print_complex_coeff(self, coeff):
        if coeff.real == 0 and coeff.imag == 0:
            return '0'

        out = ''
        if coeff.real != 0:
            if coeff.imag != 0:
                out += '('
            out += self.print_coeff(coeff.real)

        if coeff.imag != 0:
            sign = {True:'-', False:'+'}[coeff.imag < 0]
            if coeff.real != 0:
                out += ' ' + sign + ' '
            elif sign == '-':
                out += '-'

            out += "i" + self.print_coeff(abs(coeff.imag))
            if coeff.real != 0:
                out += ')'
        return out

    def _print_unit(self, u, e):
        estr = ''
        if abs(e) > 1:
            # Again, NOTE that we print out positive exponents and assume
            # that the calling function puts this in the denominator
            # correctly.
            estr = '^{{{e:.{P}g}}}'.format(e=abs(e),P=self.precision)
        return '\\mathrm{{{u}}}{e}'.format(u=u, e=estr)


    def print_units(self, tuples):
        return '~'.join([ self._print_unit(u,e)  for u,e in tuples ])


    def __call__(self, Q):
        # first sort into pos or neg exponent (of units)
        utuples = list(Q.units.items())
        # insert marker tuple
        marker = ('--',0)
        utuples.append(marker)
        utuples.sort(key = lambda u: -u[1])

        # find marker
        mi = utuples.index(marker)

        # separate into separate tuples and then sort lexically
        putuples = utuples[:mi]
        nutuples = utuples[(mi+1):]
        putuples.sort(key = lambda u: u[0])
        nutuples.sort(key = lambda u: u[0])

        U = self.print_complex_coeff(Q.coeff)
        if putuples or nutuples:
            U += '~' # spacing between coeff and units

        if (not self.oneline) and nutuples:
            U += '\\frac{'

        # numerator first
        if putuples:
            U += self.print_units( putuples )
        elif nutuples:
            U += '1'

        # now denominator
        if nutuples:
            if self.oneline:
                U += '/'
            else:
                U += '}{'
            U += self.print_units( nutuples )

        if (not self.oneline) and nutuples:
            U += '}'

        return U


class ugly_print:
    def __init__(self, precision=12):
        self.precision = precision

    def set_precision(self, precision):
        self.precision = precision

    def get_name(self):
        return ('ugly', {'precision':self.precision})

    def __call__(self, Q):
        name = ''
        if Q.name is not None:
            name = ' (' + Q.name + ')'
        return '{C:.{P}} * {U} {N}' \
               .format(C=Q.coeff, P=self.precision, U=repr(Q.units), N=name)



styles = {
    'math'   : math_print,
    'latex'  : latex_print,
    'ugly'   : ugly_print,
    'pretty' : pretty_print,
    'default': pretty_print,
}

def mkPrinter(style,*args,**kwargs):
    return styles.get( style, styles['default'] )(*args, **kwargs)


class Quantity(object):
    """
    This is the documentation for a physical Quantity.
    """
    fmt = '<{coeff:.{precision}} {units}>{name}'
    precision = 15
    print_style = pretty_print(precision=precision)

    @classmethod
    def set_default_print_style(cls, *args, **kwargs):
        """
        Sets the default print style for all physical quantities that have not
        yet had their style set specifically.

        usage: set_default_print_style(style, options)
          STYLES      OPTIONS
          'pretty'    precision [=15]
          'math'      precision [=12]
                      omit_outside_parens [=False]
          'latex'     precision [=12]
                      oneline [=True]
          'ugly'      precision [=12]
        """
        cls.print_style = mkPrinter(*args, **kwargs)

    @classmethod
    def get_default_print_style(cls):
        """
        Get the default print style for all physical quantities that have not
        yet had their style set specifically.
        """
        return cls.print_style.get_name()

    def set_print_style(self, *args, **kwargs):
        """
        Set the print style for this physical quantity specifically.
        """
        self.print_style = mkPrinter(*args, **kwargs)

    def get_print_style(self):
        """
        Get the print style for this physical quantity.
        This might return the default style or the specific style if it has been
        set for this quantity.
        """
        return self.print_style.get_name()

    @classmethod
    def set_default_precision(cls, precision):
        """
        Sets the default comparison for all coefficient comparisons.

        This function also sets the precision for the default printer.
        """
        cls.precision = precision
        cls.print_style.set_precision(precision)

    @classmethod
    def get_default_precision(cls, precision):
        """
        Gets the default comparison for all coefficient comparisons.
        """
        return cls.precision

    def set_precision(self, precision):
        """
        Sets the comparison for all coefficient comparisons for this instance.

        This function also sets the precision for the printer for this instance.
        If this instance did not previously have a specific printer, it will
        now.  This function does not modify the precision for the default
        printer.
        """
        self.precision = precision

        if id(self.__class__.print_style) == id(self.print_style):
          # make a copy of printer
          name, kwargs = self.__class__.print_style.get_name()
          self.print_style = mkPrinter(name, **kwargs)

        self.print_style.set_precision(precision)

    def get_precision(self, precision):
        """
        Gets the comparison for all coefficient comparisons for this instance.
        """
        return self.precision

    def __init__(self,coeff,units,name=None):
        self.name = name
        self.coeff = 1. * coeff
        self.units = {k:e for k,e in units.items() if e != 0}

    SERIALIZATION_NAME = 'physical.Quantity'

    @staticmethod
    def to_dict(q):
        """
        Serialization for physical.Quantity.
        """
        return dict(name=q.name, coeff=q.coeff, units=q.units,
                    __class__=Quantity.SERIALIZATION_NAME)

    @staticmethod
    def from_dict(cls_name, D):
        """
        Deserialization for physical.Quantity.
        """
        assert cls_name == Quantity.SERIALIZATION_NAME, \
          'mismatch on class name for physical.Quantity deserialization'
        return Quantity(D['coeff'], D['units'], D['name'])

    def __repr__(self):
        return self.print_style(self)

    def __add__(self,other):
        if sympy_util.is_sympy(other):
            return other.__radd__(self)

        try:
            # this is a hack to attempt supporting Quantity + other where
            # "other" is something like a numpy.ndarray object.
            assert iter(other) and other.__radd__ is not None, 'hi'
            return other.__radd__(self)
        except (TypeError, AttributeError):
            um = self.unitsMatch(other)
            if um < 0:
                return self.coeff + other
            elif um == 0:
                return self.coeff + other.coeff
            else:
                return Quantity(self.coeff + other.coeff, self.units)

    def __sub__(self,other):
        if sympy_util.is_sympy(other):
            return other.__rsub__(self)

        try:
            # this is a hack to attempt supporting Quantity + other where
            # "other" is something like a numpy.ndarray object.
            assert iter(other) and other.__rsub__ is not None, 'hi'
            return other.__rsub__(self)
        except (TypeError, AttributeError):
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

    def __hash__(self):
        return hash((self.coeff, tuple(self.units.keys()),
                                 tuple(self.units.values())))

    def __eq__(self,other):
        um = self.unitsMatch(other)
        rel_tol = 10**(-self.precision)
        if um < 0:
            return isclose(self.coeff, other, rel_tol=rel_tol)
        else:
            return isclose(self.coeff, other.coeff, rel_tol=rel_tol)

    def __lt__(self,other):
        um = self.unitsMatch(other)
        if um < 0:
            return self.coeff < other
        else:
            return self.coeff < other.coeff

    def __le__(self,other):
        um = self.unitsMatch(other)
        if um < 0:
            return self.coeff <= other
        else:
            return self.coeff <= other.coeff

    def __gt__(self,other):
        um = self.unitsMatch(other)
        if um < 0:
            return self.coeff > other
        else:
            return self.coeff > other.coeff

    def __ge__(self,other):
        um = self.unitsMatch(other)
        if um < 0:
            return self.coeff >= other
        else:
            return self.coeff >= other.coeff

    def __mul__(self,other):
        if other.__class__ == Quantity:
            c = 1. * self.coeff * other.coeff
            u = self.multUnits(other, 1)
            if not u:
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
        if not self.units:
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
        if sympy_util.is_sympy(other):
            return other.__rdiv__(self)

        try:
            c = 1. * self.coeff / other.coeff
            u = self.multUnits(other, -1)
        except AttributeError:
            try:
              # this is just a hack attempt at supporting
              # Quantity / other operations where "other" is something like a
              # numpy.ndarray object.
              assert iter(other) and other.__rdiv__ is not None, 'help!'
              return other.__rdiv__( self )
            except (TypeError, AttributeError):
              c = 1. * self.coeff / other
              u = self.units
        if not u:
            return c
        else:
            return Quantity(c, u)

    def __rdiv__(self,other):
        """ other / Quantity """
        c = other / self.coeff
        if not self.units:
            return c
        u = {k:-v for k,v in self.units.items()}
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
                    raise RuntimeError(UnitsNotRoot.format(self.units))
            elif (int(fexp) - fexp) != 0:
                raise RuntimeError(UnitsNotDimensionless.format(self.units))
            u[k] = int(u[k] * exponent)

        c  = self.coeff ** exponent
        if not u:
            return c
        return Quantity(c, u)

    def __mod__(self, other):
        try:
          return Quantity( self.coeff % other.coeff, self.units )
        except AttributeError:
          return Quantity( self.coeff % other, self.units )

    def __neg__(self):
        if not self.units:
            return -self.coeff
        return Quantity(-self.coeff, self.units)

    def __pos__(self):
        if not self.units:
            return self.coeff
        return self

    def __abs__(self):
        if not self.units:
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
        for k, e in other.units.items():
            if k in u:
                u[k] += n * e

                # we assume that we only get to zero when we add...
                if u[k] == 0:
                    del u[k]
            else:
                u[k] = n * e

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
        def get_units(u):
          if type(u) is Quantity:
            return u.units
          else:
            return dict()

        if other.__class__ != Quantity:
            if not self.units:
                # Neither are really Quantity types, so we'll just
                # give a softer indicator than an exception
                return -1
            raise RuntimeError(msg.format(self.units, get_units(other)))

        if not (self.units or other.units):
            # Neither are really Quantity types, so we'll just
            # give a soft indicator of 'equal enough'
            return 0

        if self.units != other.units:
            raise RuntimeError(msg.format(self.units, get_units(other)))
        return 1

    if sympy_util.has_sympy:
        _sympy_ = sympy_util.to_sympy
