#pragma once

#include <random>
#include "vec3.h"

// Returns random float from [0, 1)
float MyRandom() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_real_distribution<float> dis(0.0, 1.0);
  return dis(gen);
}

Vec3 RandomInUnitSphere() {
  Vec3 p;
  do {
    p = 2.0 * Vec3(MyRandom(), MyRandom(), MyRandom()) - Vec3(1, 1, 1);
  } while (p.squared_length() >= 1.0);
  return p;
}