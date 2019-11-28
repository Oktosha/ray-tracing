#ifndef HITABLE_H
#define HITABLE_H

class Hitable {
  public:
    virtual int hit(float t_min, float t_max) const = 0;
    virtual ~Hitable() = default;
};

class Sphere : public Hitable {
  public:
    Sphere(): value(0) {}
    Sphere(int value): value(value) {}
    int hit(float t_min, float t_max) const override {
      return value;
    }
    int value;
};

#endif // HITABLE_H