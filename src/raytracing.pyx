# cython: language_level=3
# distutils: language=c++

from libcpp.memory cimport unique_ptr, make_unique
from libcpp.vector cimport vector

cdef extern from "hitable.h":
  cppclass Hitable:
    pass

cdef extern from "sphere.h":
  cppclass Sphere(Hitable):
    Sphere()

cdef extern from "material.h":
  cppclass Material:
    pass

cdef extern from "camera.h":
  cppclass Camera:
    Camera()

cdef extern from "render.h":
  vector[vector[vector[float]]] Render(Hitable *world, Camera camera, int h, int w)

def render():
  cdef Camera camera
  cdef Sphere sphere
  image = Render(&sphere, camera, 100, 200)
  return image