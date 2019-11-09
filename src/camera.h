#pragma once

#include <cmath>

#include "vec3.h"
#include "ray.h"

class Camera {
  public:
    Camera(): lower_left_corner({-2, -1, -1}),
              horizontal({4, 0, 0}),
              vertical({0, 2, 0}),
              origin(0, 0, 0) {}

    // vfov = vertical field of view, top to bottom in degrees
    Camera(float vfov, float aspect) {
      float theta = vfov * M_PI / 180;
      float half_height = tan(theta/2);
      float half_width = aspect * half_height;
      lower_left_corner = Vec3(-half_width, -half_height, -1.0);
      horizontal = Vec3(2 * half_width, 0.0, 0.0);
      vertical = Vec3(0.0, 2 * half_height, 0.0);
      origin = Vec3(0, 0, 0);
    }

    Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, float vfov, float aspect) {
      Vec3 u, v, w;
      float theta = vfov * M_PI / 180;
      float half_height = tan(theta/2);
      float half_width = aspect * half_height;

      origin = lookfrom;
      w = unit_vector(lookfrom - lookat);
      u = unit_vector(cross(vup, w));
      v = cross(w, u);

      lower_left_corner = origin - half_width * u - half_height * v - w;
      horizontal = 2 * half_width * u;
      vertical = 2 * half_height * v;
    }

    Ray get_ray(float u, float v) {
      return {origin,
              lower_left_corner + u * horizontal + v * vertical - origin};
    }

    Vec3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 origin;
};
