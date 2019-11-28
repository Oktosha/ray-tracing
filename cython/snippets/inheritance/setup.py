from distutils.core import setup
from Cython.Build import cythonize

setup(ext_modules = cythonize(
           "example.pyx",                 # our Cython source
           # sources=["hierarchy.h"],  # additional source file(s)
       ))
