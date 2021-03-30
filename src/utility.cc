#include "utility.h"

#include <cmath>

namespace radacuda {
namespace utility {

double degrees_to_radians(double degrees) { return degrees * pi / 180.0; }

double clamp(double x, double min, double max) {
  if (x < min) return min;
  if (x > max) return max;
  return x;
}

double random_double() {
  // returns a random real in [0, 1)
  // TODO: add a parameter that lets the user specify a seed value
  return rand() / (RAND_MAX + 1.0);
}

double random_double(double min, double max) {
  // return random real in [min, max)
  return min + (max - min) * random_double();
}

}  // namespace utility
}  // namespace radacuda