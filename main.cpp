#include <iostream>
#include <optional>
#include "ray.h"

using namespace std;

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

int main() {
  int nx = 200;
  int ny = 100;
  cout << "P3\n" << nx << " " << ny << "\n255\n";

  Vec3 lower_left_corner(-2.0, -1.0, -1.0);
  Vec3 horizontal(4.0, 0.0, 0.0);
  Vec3 vertical(0.0, 2.0, 0.0);
  Vec3 origin(0.0, 0.0, 0.0);

  for (int j = ny - 1; j >= 0; --j) {
    for (int i = 0; i < nx; ++i) {
      float u = static_cast<float>(i) / static_cast<float>(nx);
      float v = static_cast<float>(j) / static_cast<float>(ny);

      Ray r(origin,
            lower_left_corner - origin + u * horizontal + v * vertical);
      Vec3 col = color(r);

      int ir = static_cast<int>(255.99 * col.r());
      int ig = static_cast<int>(255.99 * col.g());
      int ib = static_cast<int>(255.99 * col.b());

      cout << ir << " " << ig << " " << ib << "\n";
    }
  }
  return 0;
}