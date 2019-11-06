#include <iostream>
#include <optional>
#include <vector>
#include <limits>
#include "ray.h"

using namespace std;

struct HitRecord {
  float t;
  Vec3 p;
  Vec3 normal;
};

class Hitable {
  public:
   virtual optional<HitRecord> hit(const Ray& r, float t_min, float t_max) const = 0;
};

class Sphere : public Hitable {
  public:
    Sphere() {}
    Sphere(Vec3 center, float radius): center(center), radius(radius) {}
    optional<HitRecord> hit(const Ray& r, float tmin, float tmax) const override;

    Vec3 center;
    float radius;
};

class HitableList : public Hitable {
  public:
    HitableList() {}
    HitableList(vector<Hitable*> v): v(v) {}
    optional<HitRecord> hit(const Ray& r, float tmin, float tmax) const override;

    vector<Hitable*> v;
};


optional<float> hit_sphere(const Vec3& center, float radius, const Ray& r) {
  Vec3 oc = r.origin() - center;
  float a = dot(r.direction(), r.direction());
  float b = 2.0 * dot(oc, r.direction());
  float c = dot(oc, oc) - radius * radius;
  float discriminant = b * b - 4 * a * c;
  if (discriminant < 0) {
    return {};
  }
  return (-b - sqrt(discriminant)) / (2.0 * a);
}

optional<HitRecord> Sphere::hit(const Ray& r, float tmin, float tmax) const {
  /*
  Vec3 oc = r.origin() - center;
  float a = dot(r.direction(), r.direction());
  float b = 2.0 * dot(oc, r.direction());
  float c = dot(oc, oc) - radius * radius;
  float discriminant = b * b - 4 * a * c;

  if (discriminant >= 0) {
    if (float temp = (-b - sqrt(discriminant)) / 2.0 * a;
        temp < tmax && temp > tmin) {
      HitRecord record{temp,
              r.point_at_parameter(temp),
              (r.point_at_parameter(temp) - center) / radius};
      return record;
    }
    if (float temp = (-b + sqrt(discriminant)) / 2.0 * a;
        temp < tmax && temp > tmin) {
      HitRecord record {temp,
              r.point_at_parameter(temp),
              (r.point_at_parameter(temp) - center) / radius};
      return record;
    }
  }
  return {};
  */

  auto t = hit_sphere(center, radius, r);
  if (!t) {
    return {};
  }
  HitRecord record{t.value(), r.point_at_parameter(t.value()),
                   unit_vector(r.point_at_parameter(t.value()) - center)};
  return record;
}

optional<HitRecord> HitableList::hit(const Ray& r, float tmin, float tmax) const {
  return {};
}


Vec3 color(const Ray& r) {

  // Normal map for the sphere
  if (auto t = hit_sphere(Vec3(0, 0, -1), 0.5, r)) {
    Vec3 N = unit_vector(r.point_at_parameter(t.value()) - Vec3(0, 0, -1));
    return 0.5 * (N + Vec3(1, 1, 1));
  }

  // Gradient in the background
  Vec3 unit_direction = unit_vector(r.direction());
  float t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
}

Vec3 color(const Ray& r, Hitable* world) {

  // If we hit anything, color according to the normal
  if(auto rec = world->hit(r, 0.0, numeric_limits<float>::max())) {
    return 0.5 * (rec.value().normal + Vec3(1, 1, 1));
  }

  // Gradient in the background
  Vec3 unit_direction = unit_vector(r.direction());
  float t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
}

int main() {
  int nx = 200;
  int ny = 100;
  cout << "P3\n" << nx << " " << ny << "\n255\n";

  Vec3 lower_left_corner(-2.0, -1.0, -1.0);
  Vec3 horizontal(4.0, 0.0, 0.0);
  Vec3 vertical(0.0, 2.0, 0.0);
  Vec3 origin(0.0, 0.0, 0.0);

  Sphere sphere(Vec3(0, 0, -1), 0.5);

  for (int j = ny - 1; j >= 0; --j) {
    for (int i = 0; i < nx; ++i) {
      float u = static_cast<float>(i) / static_cast<float>(nx);
      float v = static_cast<float>(j) / static_cast<float>(ny);

      Ray r(origin,
            lower_left_corner - origin + u * horizontal + v * vertical);
      Vec3 col = color(r, &sphere);

      int ir = static_cast<int>(255.99 * col.r());
      int ig = static_cast<int>(255.99 * col.g());
      int ib = static_cast<int>(255.99 * col.b());

      cout << ir << " " << ig << " " << ib << "\n";
    }
  }
  return 0;
}