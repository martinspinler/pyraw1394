#!/usr/bin/env python

from distutils.core import setup, Extension

raw1394_module = Extension('_raw1394',
	sources=['raw1394/pyraw1394.i', 'raw1394/pyraw1394.cxx'],
	swig_opts=['-c++'],
	extra_compile_args=['-std=c++11'],
	libraries=['raw1394'],
)

setup (
	ext_modules = [raw1394_module],
    py_modules=['raw1394'],
    packages=['raw1394'],
    package_dir={'raw1394': 'raw1394'},
)
