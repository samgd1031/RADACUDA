#pragma once

#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

// Usings
using std::make_shared;
using std::shared_ptr;
using std::sqrt;

namespace radacuda {

// constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}

inline double clamp(double x, double min, double max) {
  if (x < min) return min;
  if (x > max) return max;
  return x;
}

inline double random_double() {
  // returns a random real in [0, 1)
  // TODO: add a parameter that lets the user specify a seed value
  return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
  // return random real in [min, max)
  return min + (max - min) * random_double();
}

}  // namespace radacuda

#endif  // !UTILITY_H
