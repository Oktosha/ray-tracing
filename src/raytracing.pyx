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

  for world_object in world:
    c_world.v.push_back(make_c_world_object(world_object))

  image = Render(&c_world, c_camera.get(), h, w)
  return image


cdef Vec3 make_vec3(args):
  return Vec3(args[0], args[1], args[2])


cdef unique_ptr[Hitable] make_c_world_object(world_object):
  if world_object["type"] == "sphere":
    return <unique_ptr[Hitable]>make_unique[Sphere](
      make_vec3(world_object["center"]),
      <float>world_object["radius"],
      make_c_material(world_object["material"]))
  # TODO: nicer exception, learn to display traceback in jupyter notebook
  print("World object '{}' not implemented".format(world_object["type"]))
  raise NotImplementedError(
    "World object '{}' not implemented".format(world_object["type"]))


cdef unique_ptr[Material] make_c_material(material):
  if material["type"] == "lambertian":
    return <unique_ptr[Material]>make_unique[Lambertian](
      make_vec3(material["albedo"])
    )
  elif material["type"] == "dielectric":
    return <unique_ptr[Material]>make_unique[Dielectric](
      <float>material["ref_idx"]
    )
  elif material["type"] == "metal":
    return <unique_ptr[Material]>make_unique[Metal](
      make_vec3(material["albedo"]),
      <float>material["fuzz"]
    )
  # TODO: nicer exception, learn to display traceback in jupyter notebook
  print("Material '{}' not implemented".format(material["type"]))
  raise NotImplementedError(
    "Material '{}' not implemented".format(material["type"]))
