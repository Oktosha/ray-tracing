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
    scatter(const Ray& ray_in, const Vec3& hit_point, const Vec3& hit_normal) const = 0;

    virtual ~Material() = default;
};

class Lambertian : public Material {
  public:
    Lambertian(const Vec3& albedo): albedo(albedo) {}

    std::optional<ScatterRecord>
    scatter(const Ray& ray_in, const Vec3& hit_point, const Vec3& hit_normal) const override {
      Vec3 target = hit_point + hit_normal + RandomInUnitSphere();
      ScatterRecord ans;
      ans.scattered_ray = {hit_point, target - hit_point};
      ans.attenuation = albedo;
      return ans;
    }

    Vec3 albedo;
};

class Metal : public Material {
  public:
    Metal(const Vec3& albedo, float fuzz): albedo(albedo), fuzz(fuzz) {}

    std::optional<ScatterRecord>
    scatter(const Ray& ray_in, const Vec3& hit_point, const Vec3& hit_normal) const override {
      Vec3 reflected = reflect(unit_vector(ray_in.direction), hit_normal);
      if (dot(reflected, hit_normal) <= 0) {
        return {};
      }
      ScatterRecord ans;
      ans.scattered_ray = Ray(hit_point, reflected + fuzz * RandomInUnitSphere());
      ans.attenuation = albedo;
      return ans;
    }


    Vec3 albedo;
    float fuzz;
};