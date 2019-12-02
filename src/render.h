#ifndef RENDER_H
#define RENDER_H

#include <vector>
#include <limits>

#include "hitable.h"
#include "camera.h"
#include "random.h"

Vec3 Color(const Ray& r, Hitable* world, int depth) {

  // if we hit anything
  if(auto hit_record = world->hit(r, 0.001, std::numeric_limits<float>::max())) {
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

std::vector<std::vector<std::vector<float>>> Render(
  Hitable *world, Camera *camera, int h, int w) {
  using namespace std;
  int ns = 10;
  vector<vector<vector<float>>> ans(h, vector<vector<float>>(w));
  for (int j = 0; j < h; ++j) {
    for (int i = 0; i < w; ++i) {
      Vec3 result_color(0, 0, 0);
      for (int s = 0; s < ns; ++s) {
        float u = static_cast<float>(i + MyRandom()) / static_cast<float>(w);
        float v = static_cast<float>(j + MyRandom()) / static_cast<float>(h);

        Ray r = camera->get_ray(u, v);
        Vec3 sample_color = Color(r, world, 0);
        result_color += sample_color;
      }
      result_color /= ns;
      ans[j][i] = result_color.e;
    }
  }
  return ans;
}

#endif // RENDER_H