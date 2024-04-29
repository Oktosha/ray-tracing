#pragma once

#include<optional>
#include<cmath>
#include<memory>

#include "material.h"
#include "hitable.h"

class Sphere : public Hitable {
  public:
    Sphere(Vec3 center, float radius, std::unique_ptr<Material> material)
      : center(center), radius(radius), material(std::move(material)) {}
    std::optional<HitRecord>hit(
      const Ray& r, float t_min, float t_max) const override;

    Vec3 center;
    float radius;
    std::unique_ptr<Material> material;
};

std::optional<HitRecord>
  Sphere::hit(const Ray& r, float t_min, float t_max) const {

  Vec3 oc = r.origin - center;
  float a = dot(r.direction, r.direction);
  float b = 2.0 * dot(oc, r.direction);
  float c = dot(oc, oc) - radius * radius;
  float discriminant = b * b - 4 * a * c;

  if (discriminant >= 0) {
    if (float temp = (-b - sqrt(discriminant)) / (2.0 * a);
        temp < t_max && temp > t_min) {
      HitRecord record{temp,
              r.point_at_parameter(temp),
              (r.point_at_parameter(temp) - center) / radius,
              material.get()};
      return record;
    }
    if (float temp = (-b + sqrt(discriminant)) / (2.0 * a);
        temp < t_max && temp > t_min) {
      HitRecord record {temp,
              r.point_at_parameter(temp),
              (r.point_at_parameter(temp) - center) / radius,
              material.get()};
      return record;
    }
  }
  return {};
}