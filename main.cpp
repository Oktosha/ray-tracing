#include <iostream>

using namespace std;

int main() {
  int nx = 200;
  int ny = 100;
  cout << "P3\n" << nx << " " << ny << "\n255\n";
  for (int j = ny - 1; j >= 0; --j) {
    for (int i = 0; i < nx; ++i) {
      double r = static_cast<double>(i) / static_cast<double>(nx);
      double g = static_cast<double>(j) / static_cast<double>(ny);
      double b = 0.2;
      int ir = static_cast<int>(255.99 * r);
      int ig = static_cast<int>(255.99 * g);
      int ib = static_cast<int>(255.99 * b);
      cout << ir << " " << ig << " " << ib << "\n";
    }
  }
  return 0;
}