#include<cmath>
#include<cstdlib>
#include<iostream>
#include <vector>

struct vec3 {
  vec3(): e(3, 0) {}
  vec3(float x, float y, float z): e({x, y, z}) {}
  inline float x() const { return e[0]; }
  inline float y() const { return e[1]; }
  inline float z() const { return e[2]; }
  inline float r() const { return e[0]; }
  inline float g() const { return e[1]; }
  inline float b() const { return e[2]; }

  inline const vec3& operator+() const { return *this; }
  inline vec3 operator-() const { return vec3({-e[0], -e[1], -e[2]}); }
  inline float operator[](int i) const { return e[i]; }
  inline float& operator[](int i) { return e[i]; }

  /*
  inline vec3 operator+=(const vec3 &v2);
  inline vec3 operator-=(const vec3 &v2);
  inline vec3 operator*=(const vec3 &v2);
  inline vec3 operator/=(const vec3 &v2);
  inline vec3 operator*=(const float &v2);
  inline vec3 operator/=(const float &v2);
  */

  inline float length() const;
  inline float squared_length() const;
  // inline void make_unit_vector();

  static constexpr float EPS = 1e-6;
  std::vector<float> e;
};

inline std::istream& operator>>(std::istream &is, vec3 &v) {
  is >> v[0] >> v[1] >> v[2];
  return is;
}

inline std::ostream& operator<<(std::ostream &os, const vec3 &v) {
  os << std::fixed;
  os.precision(4);
  os << v[0] << v[1] << v[2];
  return os;
}

inline vec3 operator+(const vec3 &v1, const vec3 &v2) {
  return vec3({v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]});
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2) {
  return vec3({v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]});
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2) {
  return vec3({v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]});
}

inline vec3 operator/(const vec3 &v1, const vec3 &v2) {
  return vec3({v1[0] / v2[0], v1[1] / v2[1], v1[2] / v2[2]});
}

inline vec3 operator*(const vec3 &v, float k) {
  return vec3({v[0] * k, v[1] * k, v[2] * k});
}

inline vec3 operator*(float k, const vec3 &v) {
  return vec3({v[0] * k, v[1] * k, v[2] * k});
}

inline vec3 operator/(const vec3 &v, float k) {
  return vec3({v[0] / k, v[1] / k, v[2] / k});
}

inline float dot(const vec3 &v1, const vec3 &v2) {
  return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

inline vec3 cross(const vec3 &v1, const vec3 &v2) {
  return vec3({
    v1[1] * v2[2] - v1[2] * v2[1],
    v1[2] * v2[0] - v1[0] * v2[2],
    v1[0] * v2[1] - v1[1] * v2[0]
  });
}

inline vec3 unit_vector(vec3 v) {
  return v / v.length();
}

inline float vec3::squared_length() const {
  return dot(*this, *this);
}

inline float vec3::length() const {
  return sqrt(this->squared_length());
}

bool operator ==(const vec3 &v1, const vec3 &v2) {
  return (v1 - v2).length() < vec3::EPS;
}