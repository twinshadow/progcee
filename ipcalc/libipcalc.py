from ctypes import *

libipcalc = cdll.LoadLibrary("libipcalc.so")

class Address(object):
    class _oaddr_t(Structure):
        _fields_ = [("len", c_int),
                    ("af", c_int),
                    ("addr", c_void_p),
                    ("mask", c_void_p),]

        def __str__(self):
            out = list()
            for f in self._fields_:
                out.append("%s: %s" % (f[0], getattr(self, f[0])))
            return '\n'.join(out)


    _oaddr_p = POINTER(_oaddr_t)

    def oaddr_t(ptr):
        return cast(ptr, _oaddr_p)

    def __init__(self, address):
        self.oaddr = self.oaddr_t(libipcalc.oaddr_from_str(address))
        self.address = address
        self.mask = None

    def __str__(self):
        out = create_string_buffer(128)
        libipcalc.oaddr_ntop(self.oaddr, out)
        return out.value


class Network(Address):
    def __init__(self, address, subnet=None):
        Address.__init__(self, address)

    def __contains__(self, addr):
        if isinstance(addr, str):
            v = Address(addr)
            addr = v
        if not isinstance(addr, Address):
            raise Exception("Network expects an Address object or string")
        return bool(libipcalc.in_subnet(addr, self.oaddr))
