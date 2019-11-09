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

OwningHitableList MakeWorld() {
  OwningHitableList world;
  Sphere floor(Vec3(0, -1000, 0), 1000, make_unique<Lambertian>(Vec3(0.5, 0.5, 0.5)));
  world.v.push_back(make_unique<Sphere>(std::move(floor)));

  for (int a = -11; a < 11; ++a) {
    for (int b = -11; b < 11; ++b) {
      float choose_mat = MyRandom();
      Vec3 center(a + 0.9 * MyRandom(), 0.2, b + 0.9 * MyRandom());
      if ((center-Vec3(4, 0.2, 0)).length() > 0.9) {
        unique_ptr<Material> material;
        if (choose_mat < 0.8) { // diffuse
          material = make_unique<Lambertian>(Vec3(MyRandom() * MyRandom(),
                                      MyRandom() * MyRandom(),
                                      MyRandom() * MyRandom()));
        } else if (choose_mat < 0.95) { // metal
          material = make_unique<Metal>(
            0.5 * Vec3(1 + MyRandom(), 1 + MyRandom(), 1 + MyRandom()),
            0.5 * MyRandom());
        } else { // glass
          material = make_unique<Dielectric>(1.5);
        }
        Sphere sphere(center, 0.2, std::move(material));
        world.v.push_back(make_unique<Sphere>(std::move(sphere)));
      }
    }
  }

  world.v.push_back(make_unique<Sphere>(Vec3(0, 1, 0), 1.0,
    make_unique<Dielectric>(1.5)));
  world.v.push_back(make_unique<Sphere>(Vec3(-4, 1, 0), 1.0,
    make_unique<Lambertian>(Vec3(0.4, 0.2, 0.1))));
  world.v.push_back(make_unique<Sphere>(Vec3(4, 1, 0), 1.0,
    make_unique<Metal>(Vec3(0.7, 0.6, 0.5), 0.0)));

  return world;
}


int main() {
  int nx = 1200;
  int ny = 800;
  int ns = 10; // number of samples per pixel

  cout << "P3\n" << nx << " " << ny << "\n255\n";

    Vec3 lookfrom(13,2,3);
    Vec3 lookat(0,0,0);
    float dist_to_focus = 10.0;
    float aperture = 0.1;

  Camera camera(lookfrom, lookat, Vec3(0, 1, 0),
    20, static_cast<float>(nx) / static_cast<float>(ny),
    aperture, dist_to_focus);


  OwningHitableList world = MakeWorld();

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