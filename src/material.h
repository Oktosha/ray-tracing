#pragma once

#include <optional>

#include "vec3.h"
#include "ray.h"
#include "random.h"

struct ScatterRecord {
  Ray scattered_ray;
  Vec3 attenuation;
};

class Material {
  public:
    virtual std::optional<ScatterRecord>
    scatter(const Ray& ray_in, const Vec3& hit_point, const Vec3& hit_normal) const;

    virtual ~Material() = default;
};

class Lambertian : public Material {
  public:
    Lambertian(const Vec3& albedo): albedo(albedo) {}

    virtual std::optional<ScatterRecord>
    scatter(const Ray& ray_in, const Vec3& hit_point, const Vec3& hit_normal) const {
      ScatterRecord ans;
      Vec3 target = hit_point + hit_normal + RandomInUnitSphere();
      ans.scattered_ray = {hit_point, target - hit_point};
      ans.attenuation = albedo;
      return ans;
    }

    Vec3 albedo;
};