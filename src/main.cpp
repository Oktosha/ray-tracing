#include <iostream>
#include <optional>
#include <vector>
#include <limits>
#include <random>
#include <cmath>

#include "ray.h"
#include "hitable.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "random.h"
#include "material.h"

using namespace std;



Vec3 Color(const Ray& r, Hitable* world, int depth) {

  // if we hit anything
  if(auto hit_record = world->hit(r, 0.001, numeric_limits<float>::max())) {
    // if the recusion depth isn't too big and the ray is scattered
    if (auto scatter_record =
        hit_record->material->scatter(r, hit_record->p, hit_record->normal);
        scatter_record && (depth < 50)) {
        // return attenuation * recursively called color
        return scatter_record->attenuation
          * Color(scatter_record->scattered_ray, world, depth + 1);
    } else  {
      // else (the recursion too big or the ray is consumed) return black
      return Vec3(0, 0, 0);
    }
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

  Sphere small_sphere(Vec3(0, 0, -1), 0.5,
                      make_unique<Metal>(Vec3(0.8, 0.3, 0.5)));
  Sphere big_sphere(Vec3(0, -100.5, -1), 100,
                    make_unique<Lambertian>(Vec3(0.3, 0.8, 0.5)));
  HitableList world({&small_sphere, &big_sphere});

  for (int j = ny - 1; j >= 0; --j) {
    for (int i = 0; i < nx; ++i) {
      Vec3 result_color(0, 0, 0);
      for (int s = 0; s < ns; ++s) {
        float u = static_cast<float>(i + MyRandom()) / static_cast<float>(nx);
        float v = static_cast<float>(j + MyRandom()) / static_cast<float>(ny);

        Ray r = camera.get_ray(u, v);
        Vec3 sample_color = Color(r, &world, 0);
        result_color += sample_color;
      }

      result_color /= ns;

      // gamma2 transform (whatever that means)
      result_color = Vec3(sqrt(result_color.r()),
                                sqrt(result_color.g()),
                                sqrt(result_color.b()));

      int ir = static_cast<int>(255.99 * result_color.r());
      int ig = static_cast<int>(255.99 * result_color.g());
      int ib = static_cast<int>(255.99 * result_color.b());

      cout << ir << " " << ig << " " << ib << "\n";
    }
  }
  return 0;
}