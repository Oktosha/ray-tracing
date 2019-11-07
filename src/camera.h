#pragma once

#include "vec3.h"
#include "ray.h"

class Camera {
  public:
    Camera(): lower_left_corner({-2, -1, -1}),
              horizontal({4, 0, 0}),
              vertical({0, 2, 0}),
              origin(0, 0, 0) {}

    Ray get_ray(float u, float v) {
      return {origin,
              lower_left_corner + u * horizontal + v * vertical - origin};
    }

    Vec3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 origin;
};
