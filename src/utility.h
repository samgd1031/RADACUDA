#pragma once

#ifndef UTILITY_H
#define UTILITY_H

#include <limits>

namespace radacuda {
namespace utility {

constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

double degrees_to_radians(double degrees);
double random_double();
double random_double(double min, double max);

}  // namespace utility
}  // namespace radacuda

#endif  // !UTILITY_H
