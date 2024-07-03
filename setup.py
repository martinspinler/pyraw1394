#!/usr/bin/env python

from distutils.core import setup, Extension

raw1394_module = Extension('_raw1394',
	sources=['pyraw1394.i', 'pyraw1394.cxx'],
	swig_opts=['-c++'],
	extra_compile_args=['-std=c++11'],
	libraries=['raw1394'],
)

setup (name = 'pyraw1394',
	version = '0.1.0',
	author      = "martin.spinler@gmail.com",
	description = """raw1394 python module""",
	ext_modules = [raw1394_module],
	py_modules = ["raw1394"],
	setup_requires = ["setuptools"],
)
