# cython: language_level=3
# distutils: language=c++

from libcpp.memory cimport unique_ptr, make_unique
from libcpp.vector cimport vector

cdef extern from "vec3.h":
  cppclass Vec3:
    Vec3(float x, float y, float z)

cdef extern from "hitable.h":
  cppclass Hitable:
    pass

cdef extern from "hitable_list.h":
  cppclass OwningHitableList(Hitable):
    OwningHitableList()
    vector[unique_ptr[Hitable]] v

cdef extern from "sphere.h":
  cppclass Sphere(Hitable):
    Sphere()

cdef extern from "material.h":
  cppclass Material:
    pass

  cppclass Lambertian:
    pass

  cppclass Metal:
    pass

  cppclass Dielectric:
    pass

cdef extern from "camera.h":
  cppclass Camera:
    Camera()

cdef extern from "render.h":
  vector[vector[vector[float]]] Render(Hitable *world, Camera camera, int h, int w)

def render():
  cdef Camera camera
  cdef OwningHitableList world
  world.v.push_back(<unique_ptr[Hitable]>make_unique[Sphere](
    Vec3(-4, 1, 0),
    2.0,
    <unique_ptr[Material]>make_unique[Lambertian](Vec3(0.4, 0.4, 0.8))
  ))
  image = Render(&world, camera, 100, 200)
  return image