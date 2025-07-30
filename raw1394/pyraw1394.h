#ifndef PYRAW1394_HPP
#define PYRAW1394_HPP

#include <stdint.h>
#include <memory>
#include <libraw1394/raw1394.h>
#include <libraw1394/csr.h>

#define PY_SSIZE_T_CLEAN
#include <Python.h>

class raw1394 {
	std::shared_ptr<struct raw1394_handle> m_dev;
	int m_node;

public:
	raw1394(int port = 0, int node = 0);
	virtual ~raw1394();

	PyObject* read(unsigned long long offset, size_t nbyte);
	void write(unsigned long long offset, PyObject *pydata);
};

#endif /* PYRAW1394_HPP */
