# cython: language_level=3
# distutils: language=c++

from libcpp.memory cimport unique_ptr, make_unique
from libcpp.vector cimport vector

cdef extern from "vec3.h":
  cppclass Vec3:
    Vec3()
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
    pass

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
  vector[vector[vector[float]]] Render(Hitable *world, Camera *camera, int h, int w)

def render(world, camera, int h, int w):
  cdef unique_ptr[Camera] c_camera
  cdef OwningHitableList c_world

  c_camera = make_unique[Camera]()

  c_world.v.push_back(<unique_ptr[Hitable]>make_unique[Sphere](
    make_vec3(world[0]["center"]),
    2.0,
    <unique_ptr[Material]>make_unique[Lambertian](Vec3(0.5, 0.3, 0.2))
  ))
  image = Render(&c_world, c_camera.get(), h, w)
  return image

cdef Vec3 make_vec3(args):
  return Vec3(args[0], args[1], args[2])

cdef unique_ptr[Sphere] make_c_sphere(sphere):
  pass
