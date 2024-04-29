# cython: language_level=3
# distutils: language=c++

from libcpp.memory cimport unique_ptr, make_unique
from libcpp.vector cimport vector
from libcpp.utility cimport move

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
    Sphere(Vec3 center, float radius, unique_ptr[Material] material)
    pass


cdef extern from "material.h":
  cppclass Material:
    pass

  cppclass Lambertian:
    Lambertian(const Vec3& albedo)

  cppclass Metal:
    Metal(const Vec3& albedo, float fuzz)

  cppclass Dielectric:
    Dielectric(float ref_idx)


cdef extern from "camera.h":
  cppclass Camera:
    pass


cdef extern from "render.h":
  vector[vector[vector[float]]] Render(Hitable *world, Camera *camera, int h, int w)


def render(world, camera, int h, int w):
  cdef unique_ptr[Camera] c_camera
  cdef OwningHitableList c_world

  for world_object in world:
    c_world.v.push_back(move(make_c_world_object(world_object)))

  c_camera = make_c_camera(camera)

  image = Render(&c_world, c_camera.get(), h, w)
  image = image[::-1]
  return image


cdef Vec3 make_vec3(args):
  return Vec3(args[0], args[1], args[2])

cdef unique_ptr[Camera] make_c_camera(camera):
  return move(make_unique[Camera](
    make_vec3(camera["lookfrom"]),
    make_vec3(camera["lookat"]),
    make_vec3(camera["vup"]),
    <float>camera["vfov"],
    <float>camera["aspect"],
    <float>camera["aperture"],
    <float>camera["focus_distance"]
  ))

cdef unique_ptr[Hitable] make_c_world_object(world_object):
  if world_object["type"] == "sphere":
    return unique_ptr[Hitable](new Sphere(
      make_vec3(world_object["center"]),
      <float>world_object["radius"],
      move(make_c_material(world_object["material"]))))
  raise NotImplementedError(
    "World object '{}' not implemented".format(world_object["type"]))


cdef unique_ptr[Material] make_c_material(material):
  if material["type"] == "lambertian":
    return <unique_ptr[Material]>(new Lambertian(
      make_vec3(material["albedo"])
    ))
  elif material["type"] == "dielectric":
    return <unique_ptr[Material]>(new Dielectric(
      <float>material["ref_idx"]
    ))
  elif material["type"] == "metal":
    return <unique_ptr[Material]>(new Metal(
      make_vec3(material["albedo"]),
      <float>material["fuzz"]
    ))
  else:
    raise NotImplementedError(f'Material \'{material["type"]}\' not implemented')
