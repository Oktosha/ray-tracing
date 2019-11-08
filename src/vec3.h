#pragma once

#include<cmath>
#include<cstdlib>
#include<iostream>
#include <vector>

struct Vec3 {
  Vec3(): e(3, 0) {}
  Vec3(float x, float y, float z): e({x, y, z}) {}
  inline float x() const { return e[0]; }
  inline float y() const { return e[1]; }
  inline float z() const { return e[2]; }
  inline float r() const { return e[0]; }
  inline float g() const { return e[1]; }
  inline float b() const { return e[2]; }

  inline const Vec3& operator+() const { return *this; }
  inline Vec3 operator-() const { return Vec3({-e[0], -e[1], -e[2]}); }
  inline float operator[](int i) const { return e[i]; }
  inline float& operator[](int i) { return e[i]; }


  inline Vec3 operator+=(const Vec3 &v2);
  /*
  inline Vec3 operator-=(const Vec3 &v2);
  inline Vec3 operator*=(const Vec3 &v2);
  inline Vec3 operator/=(const Vec3 &v2);
  inline Vec3 operator*=(const float &v2);
  */
  inline Vec3 operator/=(float f);

  inline float length() const;
  inline float squared_length() const;
  // inline void make_unit_vector();

  static constexpr float EPS = 1e-6;
  std::vector<float> e;
};

inline std::istream& operator>>(std::istream &is, Vec3 &v) {
  is >> v[0] >> v[1] >> v[2];
  return is;
}

inline std::ostream& operator<<(std::ostream &os, const Vec3 &v) {
  os << std::fixed;
  os.precision(4);
  os << v[0] << " " << v[1] << " " << v[2];
  return os;
}

inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2) {
  return Vec3({v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]});
}

inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2) {
  return Vec3({v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]});
}

inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2) {
  return Vec3({v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]});
}

inline Vec3 operator/(const Vec3 &v1, const Vec3 &v2) {
  return Vec3({v1[0] / v2[0], v1[1] / v2[1], v1[2] / v2[2]});
}

inline Vec3 operator*(const Vec3 &v, float k) {
  return Vec3({v[0] * k, v[1] * k, v[2] * k});
}

inline Vec3 operator*(float k, const Vec3 &v) {
  return Vec3({v[0] * k, v[1] * k, v[2] * k});
}

inline Vec3 operator/(const Vec3 &v, float k) {
  return Vec3({v[0] / k, v[1] / k, v[2] / k});
}

inline Vec3 Vec3::operator+=(const Vec3 &v2) {
    *this = *this + v2;
    return *this;
}

inline Vec3 Vec3::operator/=(float f) {
    *this = *this / f;
    return *this;
}

inline float dot(const Vec3 &v1, const Vec3 &v2) {
  return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

inline Vec3 cross(const Vec3 &v1, const Vec3 &v2) {
  return Vec3({
    v1[1] * v2[2] - v1[2] * v2[1],
    v1[2] * v2[0] - v1[0] * v2[2],
    v1[0] * v2[1] - v1[1] * v2[0]
  });
}

inline Vec3 unit_vector(Vec3 v) {
  return v / v.length();
}

inline float Vec3::squared_length() const {
  return dot(*this, *this);
}

inline float Vec3::length() const {
  return sqrt(this->squared_length());
}

bool operator ==(const Vec3 &v1, const Vec3 &v2) {
  return (v1 - v2).length() < Vec3::EPS;
}

Vec3 reflect(const Vec3& v, const Vec3& n) {
  return v - 2 * dot(v, n) * n;
}
