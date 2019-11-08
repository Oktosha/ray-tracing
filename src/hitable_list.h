#include <vector>
#include <optional>

#include "hitable.h"

class HitableList : public Hitable {
  public:
    HitableList() {}
    HitableList(std::vector<Hitable*> v): v(v) {}
    std::optional<HitRecord>
      hit(const Ray& r, float t_min, float t_max) const override;

    std::vector<Hitable*> v;
};



std::optional<HitRecord>
  HitableList::hit(const Ray& r, float t_min, float t_max) const {
  std::optional<HitRecord> ans = {};
  double closest_so_far = t_max;
  for (auto e : v) {
    if (auto rec = e->hit(r, t_min, closest_so_far)) {
      closest_so_far = rec->t;
      ans = rec;
    }
  }
  return ans;
}