#include "rectangle.h"

#include <algorithm>
#include <vector>

#include "hittable.h"
#include "vec3.h"

namespace radacuda {

rectangle::rectangle(point3 orig, vec3 v1, vec3 v2, double dim1, double dim2,
                     int u_d, int v_d) {
  origin = orig;               // origin
  d1 = dim1;                   // dimension along S1 direction
  d2 = dim2;                   // dimension along S2 direction
  u_div = u_d;                 // number of nodes in S1 direction
  v_div = v_d;                 // number of nodes in S2 direction
  S1 = vec3::unit_vector(v1);  // normalize to unit vector
  // if S2 is not perpendicular to S1 it must be made perpendicular
  if (vec3::dot(S1, v2) !=
      0.0) {  // dot product is zero if vectors are perpendicular
    vec3 parallel = (vec3::dot(S1, v2) / S1.length_squared()) *
                    S1;  // find component of v2 parallel to S1
    S2 =
        v2 -
        parallel;  // perpendicular component is vector minus parallel component
    S2 = vec3::unit_vector(S2);  // normalize vector
  } else
    S2 = vec3::unit_vector(v2);  // normalize vector

  // compute normal vector (computing here so that this calculation does not
  // need to repeat every hit test)
  // the normal vector is the same across the entire rectangle
  normal =
      vec3::cross(S1, S2);  // since S1 and S2 are already orthogonal unit
                            // vectors the cross product is also a unit vector

  // assign nodes based on U/V breakdown
  // for now nodalization is "edge" nodes only
  node_list.reserve(u_div * v_div);

  for (int ii = 0; ii < u_div; ++ii) {
    for (int jj = 0; jj < v_div; ++jj) {
      point3 u_coord =
          (u_div == 1) ? S1 * d1 / 2.0 : S1 * (d1 / (u_div - 1.0)) * ii;
      point3 v_coord =
          (v_div == 1) ? S2 * d2 / 2.0 : S2 * (d2 / (v_div - 1.0)) * jj;
      node_list.push_back(node(u_coord + v_coord));
    }
  }
}

bool rectangle::hit(const ray& r, double t_min, double t_max,
                    hit_record& rec) const {
  // first, check if the ray and the rectangle normal are perpendicular
  // if they are, then the ray is parallel to the rectangle and will not hit
  // even if coplanar, the incident angle is 90degrees so never will absorb
  // (rectangle is infinitely thin) giving this a small tolerance since it is
  // unlikely to ever be exactly zero
  if (vec3::dot(r.get_direction(), normal) < 1e-6) return false;

  // if the dot product is not zero, the ray will intersect the plane that the
  // rectangle lies in find this intersection point next
  vec3 O_RP =
      origin - r.get_origin();  // vector from ray origin to plane origin
  double t_hit = vec3::dot(O_RP, normal) / vec3::dot(r.get_direction(), normal);

  // don't count as a hit if t is not between t_min and t_max
  // this will be used to filter out "backwards" rays (t_hit < 0)
  if (t_hit < t_min || t_hit > t_max) return false;

  // now that it is known the hit point is on the plane, figure out if it is
  // within the rectangle's extents
  point3 p_hit = r.at(t_hit);
  vec3 r_HO = p_hit - origin;  // vector from rectangle origin to hit point
  // decompose r_HO into components along the S1 and S2 directions of the
  // rectangle
  vec3 r_HO1 = vec3::dot(S1, r_HO) / S1.length_squared() * S1;
  vec3 r_HO2 = vec3::dot(S2, r_HO) / S2.length_squared() * S2;

  // if any component of r_HO1 is < 0 or > S1.*d1, the point is outside the
  // rectangle
  vec3 v1 = S1 * d1;
  std::vector<bool> r_HO1_pass = {r_HO1.x() < 0,      r_HO1.y() < 0,
                                  r_HO1.z() < 0,      r_HO1.x() > v1.x(),
                                  r_HO1.y() > v1.y(), r_HO1.z() > v1.z()};
  bool r_HO1_valid = std::any_of(r_HO1_pass.begin(), r_HO1_pass.end(),
                                 [](bool x) { return x; });
  if (r_HO1_valid) return false;

  // if any component of r_HO2 is < 0 or > S2.*d2, the point is outside the
  // rectangle
  vec3 v2 = S2 * d2;
  std::vector<bool> r_HO2_pass = {r_HO2.x() < 0,      r_HO2.y() < 0,
                                  r_HO2.z() < 0,      r_HO2.x() > v2.x(),
                                  r_HO2.y() > v2.y(), r_HO2.z() > v2.z()};
  bool r_HO2_valid = std::any_of(r_HO2_pass.begin(), r_HO2_pass.end(),
                                 [](bool x) { return x; });
  if (r_HO2_valid) return false;

  // point is inside the rectangle
  rec.t = t_hit;
  rec.p = p_hit;
  rec.normal = normal;
  return true;
}

std::string rectangle::gnuplot_repr() {
  std::string x_str = std::to_string(origin[0]) + " + " +
                      std::to_string((S1 * d1).x()) + "*u + " +
                      std::to_string((S2 * d2).x()) + "*v";
  std::string y_str = std::to_string(origin[1]) + " + " +
                      std::to_string((S1 * d1).y()) + "*u + " +
                      std::to_string((S2 * d2).y()) + "*v";
  std::string z_str = std::to_string(origin[2]) + " + " +
                      std::to_string((S1 * d1).z()) + "*u + " +
                      std::to_string((S2 * d2).z()) + "*v";

  return "[u=0:1] [v=0:1] " + x_str + ',' + y_str + ',' + z_str;
}

}  // namespace radacuda
