#pragma once

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <algorithm>
#include <vector>

#include "hittable.h"
#include "vec3.h"

namespace radacuda {

// Rectangles are defined by an origin/corner point, two (unit) vectors to set
// the plane and two values to set the length in each dimension
class rectangle : public hittable {
 public:
  rectangle(point3 origin, vec3 v1, vec3 v2, double dim1, double dim2, int u_d,
            int v_d);
  virtual bool hit(const ray& r, double t_min, double t_max,
                   hit_record& rec) const override;
  virtual std::string gnuplot_repr() override;

  vec3 get_normal() { return normal; }

 private:
  point3 origin;
  double d1;
  double d2;
  int u_div;
  int v_div;
  vec3 S1;
  vec3 S2;
  vec3 normal;
};

}  // namespace radacuda

#endif  // !RECTANGLE_H
