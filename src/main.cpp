#include <iostream>
#include <optional>
#include <vector>
#include <limits>
#include <random>

#include "ray.h"
#include "hitable.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"

using namespace std;

float MyRandom() {
  static random_device rd;
  static mt19937 gen(rd());
  static uniform_real_distribution<float> dis(0.0, 1.0);
  return dis(gen);
}

Vec3 Color(const Ray& r, Hitable* world) {

  // If we hit anything, color according to the normal
  if(auto rec = world->hit(r, 0.0, numeric_limits<float>::max())) {
    return 0.5 * (rec.value().normal + Vec3(1, 1, 1));
  }

  // Gradient in the background
  Vec3 unit_direction = unit_vector(r.direction);
  float t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
}

int main() {
  int nx = 200;
  int ny = 100;
  int ns = 100; // number of samples per pixel (antialiasing)

  cout << "P3\n" << nx << " " << ny << "\n255\n";

  Camera camera;

  Sphere small_sphere(Vec3(0, 0, -1), 0.5);
  Sphere big_sphere(Vec3(0, -100.5, -1), 100);
  HitableList world({&small_sphere, &big_sphere});

  for (int j = ny - 1; j >= 0; --j) {
    for (int i = 0; i < nx; ++i) {
      Vec3 result_color(0, 0, 0);
      for (int s = 0; s < ns; ++s) {
        float u = static_cast<float>(i + MyRandom()) / static_cast<float>(nx);
        float v = static_cast<float>(j + MyRandom()) / static_cast<float>(ny);

        Ray r = camera.get_ray(u, v);
        Vec3 sample_color = Color(r, &world);
        result_color += sample_color;
      }

      result_color /= ns;

      int ir = static_cast<int>(255.99 * result_color.r());
      int ig = static_cast<int>(255.99 * result_color.g());
      int ib = static_cast<int>(255.99 * result_color.b());

      cout << ir << " " << ig << " " << ib << "\n";
    }
  }
  return 0;
}