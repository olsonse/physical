from math import log10

from exceptions import RuntimeError


UnitsMismatch = 'Units mismatch:  cannot add/subtract/compare mismatched units ({} != {})'
UnitsNotRoot  = 'Units not root:  cannot take non-even root of units ({})'
UnitsNotDimensionless = 'Units not dimensionless:  cannot create non-integer powers of unit ({})'


class pretty_print:
    def get_name(self):
      return ('pretty',{})

    def __call__(self,Q):
      # first sort into pos or neg exponent (of units)
      utuples = Q.units.items()
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

      U = ''

      # numerator first
      sep = ''
      for u,e in putuples:
          U += sep + u
          sep = ' '
          if e != 1:
              U += '^' + `e`

      # now denominator
      if nutuples != []:
          U += ' /'

      for u,e in nutuples:
          U += sep + u
          sep = ' '
          if e != -1:
              U += '^' + `-e`

      name = ''
      if Q.name is not None:
          name = ' (' + Q.name + ')'

      return Q.fmt.format(coeff=Q.coeff, units=U, name=name)


class math_print:
    def __init__(self, precision=12, omit_outside_parens=False):
        self.precision = precision
        self.omit_parens = omit_outside_parens

    def get_name(self):
        return ('math',
                {'precision':self.precision,
                 'omit_outside_parens':self.omit_parens,
                }
               )

    def __call__(self, Q):
        # first sort into pos or neg exponent (of units)
        utuples = Q.units.items()
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
                  U += '**' + `e`

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
                    U += '**' + `-e`

            if len(nutuples) > 1:
                U += ')'
        if not self.omit_parens:
          U += ')'

        return U

class latex_print:
    def __init__(self, precision=12, oneline=True):
        self.precision = precision
        self.oneline = oneline

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
            estr = '^{{{e:.{P}}}}'.format(e=abs(e),P=self.precision)
        return '\\mathrm{{{u:.{P}}}}{e}'.format(u=u,P=self.precision, e=estr)


    def print_units(self, tuples):
        return '~'.join([ self._print_unit(u,e)  for u,e in tuples ])


    def __call__(self, Q):
        # first sort into pos or neg exponent (of units)
        utuples = Q.units.items()
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
            U += self.print_units( putuples )

        if (not self.oneline) and nutuples:
            U += '}'

        return U


class ugly_print:
    def __init__(self, precision=12):
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
    fmt = '<{coeff} {units}>{name}'
    print_style = pretty_print()

    @classmethod
    def set_default_print_style(cls, *args, **kwargs):
        """
        Sets the default print style for all physical quantities that have not
        yet had their style set specifically.

        usage: set_default_print_style(style, options)
          STYLES      OPTIONS
          'pretty'
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

    def __init__(self,coeff,units,name=None):
        self.name = name
        self.coeff = 1. * coeff
        self.units = units.copy()
        for k in self.units.keys():
            if self.units[k] == 0:
                del self.units[k]

    def __repr__(self):
      return self.print_style(self)

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
                    raise RuntimeError(UnitsNotRoot.format(self.units))
            elif (int(fexp) - fexp) != 0:
                raise RuntimeError(UnitsNotDimensionless.format(self.units))
            u[k] = int(u[k] * exponent)

        c  = self.coeff ** exponent
        if u.keys() == [ ]:
            return c
        return Quantity(c, u)

    def __mod__(self, other):
        try:
          return Quantity( self.coeff % other.coeff, self.units )
        except AttributeError:
          return Quantity( self.coeff % other, self.units )

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
        def get_units(u):
          if type(u) is Quantity:
            return u.units
          else:
            return dict()

        if other.__class__ != Quantity:
            if self.units.keys() == [ ]:
                # Neither are really Quantity types, so we'll just
                # give a softer indicator than an exception
                return -1
            raise RuntimeError(msg.format(self.units, get_units(other)))

        if self.units.keys() == [ ] and other.units.keys() == [ ]:
            # Neither are really Quantity types, so we'll just
            # give a soft indicator of 'equal enough'
            return 0

        if self.units != other.units:
            raise RuntimeError(msg.format(self.units, get_units(other)))
        return 1

