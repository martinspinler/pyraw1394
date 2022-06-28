#include <iostream>
#include <byteswap.h>
#include <string.h>

#include <libraw1394/raw1394.h>
#include <libraw1394/csr.h>

#include "pyraw1394.h"

#define ALIGN_Q(n) ((n + 3) / 4)

raw1394::raw1394(int port, int node)
{
	int rc;
	struct raw1394_handle* h = raw1394_new_handle();
	m_dev = std::shared_ptr<struct raw1394_handle>(h, raw1394_destroy_handle);
	m_node = node;

	rc = raw1394_set_port(m_dev.get(), port);
	if (rc) {
		PyErr_SetString(PyExc_RuntimeError, "Can't set port");
	}
}

raw1394::~raw1394()
{
}

PyObject* raw1394::read(unsigned long long offset, size_t nbyte)
{
	int ret;
	quadlet_t d[ALIGN_Q(nbyte)];

	ret = raw1394_read(m_dev.get(), m_node, offset, nbyte, d);
	if (ret) {
		PyErr_SetString(PyExc_RuntimeError, "Can't read from device");
		return NULL;
	}

	for (size_t i = 0; i < ALIGN_Q(nbyte); i++) {
		d[i] = __bswap_32(d[i]);
	}
	return PyByteArray_FromStringAndSize((const char *) d, nbyte);
}

void raw1394::write(unsigned long long offset, PyObject *pydata)
{
	if (!PyByteArray_Check(pydata)) {
		return;
	}

	int ret;
	const unsigned char *data = (const unsigned char*) PyByteArray_AsString(pydata);
	size_t nbyte = (long) PyByteArray_Size(pydata);
	quadlet_t d[ALIGN_Q(nbyte)];

	memcpy(d, data, nbyte);
	for (size_t i = 0; i < ALIGN_Q(nbyte); i++) {
		d[i] = __bswap_32(d[i]);
	}

	ret = raw1394_write(m_dev.get(), m_node, offset, nbyte, d);
	if (ret) {
		PyErr_SetString(PyExc_RuntimeError, "Can't write from device");
	}
}
