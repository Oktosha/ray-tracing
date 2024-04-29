#pragma once

#include "vec3.h"

struct Ray {
  Ray(): origin(), direction() {}
  Ray(const Vec3 &origin, const Vec3 &direction):
    origin(origin), direction(direction) {}
  Vec3 point_at_parameter(float t) const {return origin + t * direction; }

  Vec3 origin;
  Vec3 direction;
};
