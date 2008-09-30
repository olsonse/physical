class const:
    class ConstError(TypeError): pass
    def __setattr__(self,name,value):
        if self.__dict__.has_key(name):
            raise self.ConstError, "Can't rebind %s.%s" %(self._physname,name)
        self.__dict__[name]=value

    def __init__(self,_physname=None):
        self._physname = _physname
