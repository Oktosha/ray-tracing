# cython: language_level=3
# distutils: language=c++

from libcpp.memory cimport unique_ptr, make_unique

def print_hello_to(name):
  print("Hello, {}!".format(name))

def render(h, w):
  """ Renders example (h, w, 3) image"""
  image = [[[i / w, j / h, 0.2] for i in range(w)] for j in range(h)]
  return image

cdef extern from "hitable.h":
  cppclass Hitable:
    int hit(float tmin, float tmax) const

  cppclass Sphere(Hitable):
    pass

def test_sphere():
  cdef unique_ptr[Sphere] sphere
  sphere = make_unique[Sphere](5)
  value = sphere.get().hit(0, 0)
  return value