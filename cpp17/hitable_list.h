#include <vector>
#include <optional>
#include <memory>

#include "hitable.h"

template <class T>
class HitableList : public Hitable {
  public:
    HitableList() {}
    HitableList(std::vector<T> v): v(std::move(v)) {}
    std::optional<HitRecord>
      hit(const Ray& r, float t_min, float t_max) const override;

    std::vector<T> v;
};


template<class T>
std::optional<HitRecord> HitableList<T>::hit(
    const Ray& r, float t_min, float t_max) const {
  std::optional<HitRecord> ans = {};
  double closest_so_far = t_max;
  for (const auto &e : v) {
    if (auto rec = e->hit(r, t_min, closest_so_far)) {
      closest_so_far = rec->t;
      ans = rec;
    }
  }
  return ans;
}

using OwningHitableList = HitableList<std::unique_ptr<Hitable>>;
using NonOwningHitableList = HitableList<Hitable*>;