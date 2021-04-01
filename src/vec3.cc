#include "vec3.h"

#include <cmath>
#include <iostream>

#include "utility.h"

namespace radacuda {

double vec3::x() const { return e[0]; }
double vec3::y() const { return e[1]; }
double vec3::z() const { return e[2]; }

double vec3::length_squared() const {
  return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}
double vec3::length() const { return sqrt(length_squared()); }

bool vec3::near_zero() const {
  const auto s = 1e-8;
  return (fabs(e[0] < s)) && (fabs(e[1] < s)) && (fabs(e[2] < s));
}

vec3 vec3::perpendicularize(const vec3& other) {
  // dot product is zero if vectors are perpendicular
  double dot_val = dot(*this, other);
  if (dot_val == 0.0) {
    return other;
  }
  // find component of other parallel to this
  vec3 parallel = (dot_val / this->length_squared()) * (*this);
  // perpendicular component is vector minus parallel component
  return other - parallel;
}

vec3 vec3::random() {
  return vec3(utility::random_double(), utility::random_double(),
              utility::random_double());
}

vec3 vec3::random(double min, double max) {
  return vec3(utility::random_double(min, max),
              utility::random_double(min, max),
              utility::random_double(min, max));
}

vec3 vec3::random_in_unit_sphere() {
  while (true) {
    auto p = vec3::random(-1, 1);
    if (p.length_squared() >= 1)
      continue;  // vector is outside sphere, try again
    return p;
  }
}

vec3 vec3::random_unit_vector() { return unit_vector(random_in_unit_sphere()); }

vec3 vec3::random_in_hemisphere(const vec3& normal) {
  vec3 in_unit_sphere = random_in_unit_sphere();
  if (dot(in_unit_sphere, normal) > 0.0)  // in same hemisphere as normal
    return in_unit_sphere;
  else  // in opposite hemisphere
    return -in_unit_sphere;
}

vec3 vec3::operator-() const { return vec3(-e[0], -e[1], -e[2]); }
double vec3::operator[](int i) const { return e[i]; }
double& vec3::operator[](int i) { return e[i]; }

vec3& vec3::operator+=(const vec3& other) {
  e[0] += other.e[0];
  e[1] += other.e[1];
  e[2] += other.e[2];
  return *this;
}

vec3 vec3::operator+(const vec3& other) const {
  vec3 result = *this;
  result += other;
  return result;
}

vec3& vec3::operator-=(const vec3& other) {
  e[0] -= other.e[0];
  e[1] -= other.e[1];
  e[2] -= other.e[2];
  return *this;
}

vec3 vec3::operator-(const vec3& other) const {
  vec3 result = *this;
  result -= other;
  return result;
}

vec3& vec3::operator*=(const vec3& other) {
  e[0] *= other.e[0];
  e[1] *= other.e[1];
  e[2] *= other.e[2];
  return *this;
}

vec3 vec3::operator*(const vec3& other) const {
  vec3 result = *this;
  result *= other;
  return result;
}

vec3& vec3::operator*=(const double t) {
  e[0] *= t;
  e[1] *= t;
  e[2] *= t;
  return *this;
}

vec3 vec3::operator*(const double t) const {
  vec3 result = *this;
  result *= t;
  return result;
}

vec3& vec3::operator/=(const double t) { return *this *= 1 / t; }

vec3 vec3::operator/(const double t) const {
  vec3 result = *this;
  result /= t;
  return result;
}

bool vec3::operator==(const vec3& other) const {
  return e[0] == other.e[0] && e[1] == other.e[1] && e[2] == other.e[2];
}

double vec3::dot(const vec3& u, const vec3& v) {
  return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

vec3 vec3::cross(const vec3& u, const vec3& v) {
  return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
              u.e[2] * v.e[0] - u.e[0] * v.e[2],
              u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

vec3 vec3::unit_vector(vec3 v) { return v / v.length(); }

vec3 vec3::reflect(const vec3& v, const vec3& n) {
  return v - 2 * dot(v, n) * n;
}

vec3 vec3::refract(const vec3& uv, const vec3& n, double etai_over_etat) {
  auto cos_theta = fmin(dot(-uv, n), 1.0);  // angle between vectors
  vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
  vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
  return r_out_perp + r_out_parallel;
}
}  // namespace radacuda