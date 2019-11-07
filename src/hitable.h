#pragma once

#include <optional>

#include "vec3.h"
#include "ray.h"

struct HitRecord {
  float t;
  Vec3 p;
  Vec3 normal;
};

class Hitable {
  public:
    virtual std::optional<HitRecord>
      hit(const Ray& r, float t_min, float t_max) const = 0;
    virtual ~Hitable(){};
};
