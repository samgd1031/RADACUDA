#pragma once

#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

#include "utility.h"

namespace radacuda {

class vec3 {
 public:
  //// CONSTRUCTORS ////
  vec3() : e{0, 0, 0} {}
  vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

  //// ACCESSORS ////
  double x() const;
  double y() const;
  double z() const;
  double length_squared() const;
  double length() const;

  // return true if vector is close to zero in all dimensions
  bool near_zero() const;

  // return a vector that is perpendicular to this vector which is formed by
  // subtracting the component of other which is parallel to this vector.
  // Returns the original vector if already perpendicular.
  vec3 perpendicularize(const vec3& other);

  //// GENERATORS ////
  // vector with random components in unit cube
  static vec3 random();

  // vector with random components, each component in [min, max)
  static vec3 random(double min, double max);

  // return a random vector in the unit sphere
  static vec3 random_in_unit_sphere();

  // return a random vector ON the unit sphere
  // This is used to calculate true lambertian diffusion
  static vec3 random_unit_vector();

  // return a random vector in hemisphere
  static vec3 random_in_hemisphere(const vec3& normal);

  //// UNARY OPERATOR DEFINITIONS ////
  vec3 operator-() const;
  double operator[](int i) const;
  double& operator[](int i);

  //// BINARY OPERATOR DEFINITIONS ////
  // addition
  vec3& operator+=(const vec3& other);
  vec3 operator+(const vec3& other) const;

  // subtraction
  vec3& operator-=(const vec3& other);
  vec3 operator-(const vec3& other) const;

  // elementwise multiplication
  vec3& operator*=(const vec3& other);
  vec3 operator*(const vec3& other) const;

  // scalar multiplication
  vec3& operator*=(const double t);
  vec3 operator*(const double t) const;

  // scalar division
  vec3& operator/=(const double t);
  vec3 operator/(const double t) const;

  // equality comparison
  bool operator==(const vec3& other) const;

  //// MATHEMATICAL OPERATORS ////
  // dot product
  static double dot(const vec3& u, const vec3& v);

  // cross product
  static vec3 cross(const vec3& u, const vec3& v);

  // normalize vector
  static vec3 unit_vector(vec3 v);

  // return a reflection of a vector with a surface normal
  static vec3 reflect(const vec3& v, const vec3& n);

  // return a refraction of a material given ratio of refractive indices
  // refraction calculated using Snell's law
  static vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat);

 private:
  double e[3];
};

inline vec3 operator*(const double t, const vec3& v) { return v * t; }

inline std::ostream& operator<<(std::ostream& os, const vec3& vec) {
  return os << "[" << vec.x() << ", " << vec.y() << ", " << vec.z() << "]";
}

// Type aliases for vec3
using point3 = vec3;  // 3d point
using color = vec3;   // RGB color

}  // namespace radacuda

#endif