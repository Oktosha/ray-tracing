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

class Dielectric : public Material {
  public:

    static float schlick(float cosine, float ref_idx) {
      float r0 = (1 - ref_idx) / (1 + ref_idx);
      r0 = r0 * r0;
      return r0 + (1 - r0) * pow((1 - cosine), 5);
    }

    Dielectric(float ref_idx): ref_idx(ref_idx) {}

    std::optional<ScatterRecord>
    scatter(const Ray& ray_in, const Vec3& hit_point, const Vec3& hit_normal) const override {

      Vec3 outward_normal;
      Vec3 reflected = reflect(ray_in.direction, hit_normal);
      Vec3 refracted;
      Vec3 attenuation = Vec3(1.0, 1.0, 1.0);
      float ni_over_nt;
      float reflect_probability;
      float cosine;

      if (dot(ray_in.direction, hit_normal) > 0) {
        outward_normal = -hit_normal;
        ni_over_nt = ref_idx;
        cosine = ref_idx * dot(ray_in.direction, hit_normal) / ray_in.direction.length();
      } else {
        outward_normal = hit_normal;
        ni_over_nt = 1.0 / ref_idx;
        cosine = -dot(ray_in.direction, hit_normal) / ray_in.direction.length();
      }

      if (auto refracted_optional = refract(ray_in.direction, outward_normal, ni_over_nt)) {
        refracted = refracted_optional.value();
        reflect_probability = schlick(cosine, ref_idx);
      } else {
        reflect_probability = 1.0;
      }

      if (MyRandom() < reflect_probability) {
        return ScatterRecord{Ray(hit_point, reflected), attenuation};
      }
      return ScatterRecord{Ray(hit_point, refracted), attenuation};
    }

    float ref_idx;
};