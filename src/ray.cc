#include "ray.h"

namespace radacuda {

std::string ray::gnuplot_repr(double tmin, double tmax) {
  ////////////////////////////////////////////////////////////
  // THE RANGE FOR T DOES NOT APPEAR TO BE WORKING PROPERLY, range gets set
  // globally
  ////////////////////////////////////////////////////////////
  return "[" + std::to_string(tmin) + ":" + std::to_string(tmax) + "]" +
         std::to_string(orig[0]) + "+ u*" + std::to_string(dir[0]) + ", " +
         std::to_string(orig[1]) + "+ u*" + std::to_string(dir[1]) + ", " +
         std::to_string(orig[2]) + "+ u*" + std::to_string(dir[2]);
}

}  // namespace radacuda