import sysconfig

from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

extra_compile_args = sysconfig.get_config_var('CFLAGS').split()
extra_compile_args += ["--std=c++17"]

extensions = [
    Extension("raytracing", ["raytracing.pyx"],
        language="c++",
        extra_compile_args=extra_compile_args)
]

setup(
    ext_modules = cythonize(extensions)
)
