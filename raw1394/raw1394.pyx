cdef extern from "pyraw1394.h":
    cdef cppclass raw1394:
        raw1394(int, int)
        object read(unsigned long long offset, size_t nbyte)
        void write(unsigned long long offset, object pydata)


cdef class Raw1394:
    cdef raw1394 *thisptr

    def __cinit__(self, int port = 0, int node = 0):
        self.thisptr = new raw1394(port, node)

    def __dealloc__(self) -> None:
        del self.thisptr

    def read(self, offset: int, nbyte: int) -> bytearray:
        return self.thisptr.read(offset, nbyte)

    def write(self, offset: int, data: bytearray) -> None:
        self.thisptr.write(offset, data)
