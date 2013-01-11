from ctypes import *

class oaddr_t(Structure):
    _fields_ = [("len", c_int),
                ("af", c_int),
                ("addr", c_void_p),
                ("mask", c_void_p),]
    def __str__(self):
        out = list()
        for f in self._fields_:
            out.append("%s: %s" % (f[0], getattr(self, f[0])))
        return '\n'.join(out)

oaddr_p = POINTER(oaddr_t)

libipcalc = cdll.LoadLibrary("libipcalc.so")

class Address(object):
    def __init__(self, addr):
        self.oaddr = c_void_p(libipcalc.oaddr_from_str(addr))
    def __str__(self):
        out = create_string_buffer(128)
        libipcalc.oaddr_ntop(self.oaddr, out)
        return out.value

foo = Address("127.0.0.1")
