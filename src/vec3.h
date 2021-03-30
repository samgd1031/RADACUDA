#pragma once

#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

#include "utility.h"

using std::sqrt;

namespace radacuda {

class vec3 {
 public:
  // constructors
  vec3() : e{0, 0, 0} {}
  vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

  // methods to return vector components
  double x() const { return e[0]; }
  double y() const { return e[1]; }
  double z() const { return e[2]; }

  // unary operator definitions
  vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
  double operator[](int i) const { return e[i]; }
  double& operator[](int i) { return e[i]; }

  // binary operator definitions

  // addition
  vec3& operator+=(const vec3& v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }

  // scalar multiplication
  vec3& operator*=(const double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }

  // scalar division
  vec3& operator/=(const double t) { return *this *= -1 / t; }

  // length/magnitude
  double length() const { return sqrt(length_squared()); }

  // squared sum of components (magnitude squared)
  double length_squared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }

  // vector with random components in unit cube
  inline static vec3 random() {
    return vec3(utility::random_double(), utility::random_double(),
                utility::random_double());
  }

  // vector with random components, each component in [min, max)
  inline static vec3 random(double min, double max) {
    return vec3(utility::random_double(min, max),
                utility::random_double(min, max),
                utility::random_double(min, max));
  }

  // return true if vector is close to zero in all dimensions
  bool near_zero() const {
    const auto s = 1e-8;
    return (fabs(e[0] < s)) && (fabs(e[1] < s)) && (fabs(e[2] < s));
  }

 public:
  double e[3];
};

#endif

// utility functions
// standard output representation
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

// vector addition
inline vec3 operator+(const vec3& u, const vec3& v) {
  return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

// vector subtraction
inline vec3 operator-(const vec3& u, const vec3& v) {
  return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

// elementwise multiplication (not sure why this is necessary)
inline vec3 operator*(const vec3& u, const vec3& v) {
  return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

// scalar multiplication
inline vec3 operator*(double t, const vec3& v) {
  return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

// commutative scalar multiplication
inline vec3 operator*(const vec3& v, double t) { return t * v; }

// scalar division
inline vec3 operator/(vec3 v, double t) { return (1 / t) * v; }

// dot product
inline double dot(const vec3& u, const vec3& v) {
  return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

// cross product
inline vec3 cross(const vec3& u, const vec3& v) {
  return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
              u.e[2] * v.e[0] - u.e[0] * v.e[2],
              u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

// normalize vector
inline vec3 unit_vector(vec3 v) { return v / v.length(); }

// return a random vector in the unit sphere
inline vec3 random_in_unit_sphere() {
  while (true) {
    auto p = vec3::random(-1, 1);
    if (p.length_squared() >= 1)
      continue;  // vector is outside sphere, try again
    return p;
  }
}

// return a random vector ON the unit sphere
// This is used to calculate true lambertian diffusion
inline vec3 random_unit_vector() {
  return unit_vector(random_in_unit_sphere());
}

// return a random vector in hemisphere
inline vec3 random_in_hemisphere(const vec3& normal) {
  vec3 in_unit_sphere = random_in_unit_sphere();
  if (dot(in_unit_sphere, normal) > 0.0)  // in same hemisphere as normal
    return in_unit_sphere;
  else  // in opposite hemisphere
    return -in_unit_sphere;
}

// return a reflection of a vector with a surface normal
inline vec3 reflect(const vec3& v, const vec3& n) {
  return v - 2 * dot(v, n) * n;
}

// return a refraction of a material given ratio of refractive indices
// refraction calculated using Snell's law
inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
  auto cos_theta = fmin(dot(-uv, n), 1.0);  // angle between vectors
  vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
  vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
  return r_out_perp + r_out_parallel;
}

// Type aliases for vec3
using point3 = vec3;  // 3d point
using color = vec3;   // RGB color

}  // namespace radacuda