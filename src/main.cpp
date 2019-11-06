#include <iostream>
#include <optional>
#include <vector>
#include <limits>
#include "ray.h"
#include "hitable.h"

using namespace std;

class Sphere : public Hitable {
  public:
    Sphere() {}
    Sphere(Vec3 center, float radius): center(center), radius(radius) {}
    optional<HitRecord> hit(const Ray& r, float t_min, float t_max) const override;

    Vec3 center;
    float radius;
};

class HitableList : public Hitable {
  public:
    HitableList() {}
    HitableList(vector<Hitable*> v): v(v) {}
    optional<HitRecord> hit(const Ray& r, float t_min, float t_max) const override;

    vector<Hitable*> v;
};

optional<HitRecord> Sphere::hit(const Ray& r, float t_min, float t_max) const {
  Vec3 oc = r.origin() - center;
  float a = dot(r.direction(), r.direction());
  float b = 2.0 * dot(oc, r.direction());
  float c = dot(oc, oc) - radius * radius;
  float discriminant = b * b - 4 * a * c;

  if (discriminant >= 0) {
    if (float temp = (-b - sqrt(discriminant)) / (2.0 * a);
        temp < t_max && temp > t_min) {
      HitRecord record{temp,
              r.point_at_parameter(temp),
              (r.point_at_parameter(temp) - center) / radius};
      return record;
    }
    if (float temp = (-b + sqrt(discriminant)) / (2.0 * a);
        temp < t_max && temp > t_min) {
      HitRecord record {temp,
              r.point_at_parameter(temp),
              (r.point_at_parameter(temp) - center) / radius};
      return record;
    }
  }
  return {};
}

optional<HitRecord> HitableList::hit(const Ray& r, float t_min, float t_max) const {
  optional<HitRecord> ans = {};
  double closest_so_far = t_max;
  for (auto e : v) {
    if (auto rec = e->hit(r, t_min, closest_so_far)) {
      closest_so_far = rec.value().t;
      ans = rec;
    }
  }
  return ans;
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

  Sphere small_sphere(Vec3(0, 0, -1), 0.5);
  Sphere big_sphere(Vec3(0, -100.5, -1), 100);
  HitableList world({&small_sphere, &big_sphere});

  for (int j = ny - 1; j >= 0; --j) {
    for (int i = 0; i < nx; ++i) {
      float u = static_cast<float>(i) / static_cast<float>(nx);
      float v = static_cast<float>(j) / static_cast<float>(ny);

      Ray r(origin,
            lower_left_corner - origin + u * horizontal + v * vertical);
      Vec3 col = color(r, &world);

      int ir = static_cast<int>(255.99 * col.r());
      int ig = static_cast<int>(255.99 * col.g());
      int ib = static_cast<int>(255.99 * col.b());

      cout << ir << " " << ig << " " << ib << "\n";
    }
  }
  return 0;
}