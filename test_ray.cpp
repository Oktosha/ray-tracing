#include <iostream>
#include <cassert>

#include "ray.h"


using namespace std;

int main() {
  Ray r({0, 0, 0}, {1, 2, 3});
  cout << r.point_at_parameter(2) << endl;
  assert(r.point_at_parameter(2) == Vec3({2, 4, 6}));
  return 0;
}