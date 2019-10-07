#include <iostream>
#include "vec3.h"

using namespace std;

int main() {
  int nx = 200;
  int ny = 100;
  cout << "P3\n" << nx << " " << ny << "\n255\n";
  for (int j = ny - 1; j >= 0; --j) {
    for (int i = 0; i < nx; ++i) {
      Vec3 color(
        static_cast<float>(i) / static_cast<float>(nx),
        static_cast<float>(j) / static_cast<float>(ny),
        0.2
      );
      int ir = static_cast<int>(255.99 * color.r());
      int ig = static_cast<int>(255.99 * color.g());
      int ib = static_cast<int>(255.99 * color.b());
      cout << ir << " " << ig << " " << ib << "\n";
    }
  }
  return 0;
}