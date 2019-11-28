#ifndef RENDER_H
#define RENDER_H

#include <vector>
#include "hitable.h"

int Render(Hitable *world, int h, int w) {
  return world->hit(0, 0) * h * w;
}

#endif // RENDER_H