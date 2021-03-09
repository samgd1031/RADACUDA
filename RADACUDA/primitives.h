// this header file holds classes that define primitive shapes that have mathematically defined
// interactions with rays
// These classes are child classes of the generic "hittable" class
#pragma once

#ifndef PRIMITITVES_H
# define PRIMITIVES_H

#include "hittable.h"
#include "vec3.h"

#include <vector>
#include <algorithm>


// RECTANGLE
// Rectangles are defined by an origin/corner point, two (unit) vectors to set the plane
// and two values to set the length in each dimension
class rectangle : public hittable {
public:
	rectangle(point3 orig, vec3 v1, vec3 v2, double dim1, double dim2); // constructor
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override; //hit function

public:
	point3 origin;
	vec3 S1;
	vec3 S2;
	vec3 normal;
	double d1;
	double d2;
};

// constructor
rectangle::rectangle(point3 orig, vec3 v1, vec3 v2, double dim1, double dim2) {
	origin = orig; // origin
	d1 = dim1; // dimension along S1 direction
	d2 = dim2; // dimension along S2 direction
	S1 = unit_vector(v1); // normalize to unit vector
	// if S2 is not perpendicular to S1 it must be made perpendicular
	if (dot(S1, v2) != 0.0) { // dot product is zero if vectors are perpendicular
		vec3 parallel = (dot(S1, v2) / S1.length_squared()) * S1; // find component of v2 parallel to S1
		S2 = v2 - parallel; // perpendicular component is vector minus parallel component
		S2 = unit_vector(S2); // normalize vector
	}
	else S2 = unit_vector(v2); // normalize vector
	
	//compute normal vector (computing here so that this calculation does not need to repeat every hit test)
	// the normal vector is the same across the entire rectangle
	normal = cross(S1, S2); // since S1 and S2 are already orthogonal unit vectors the cross product is also a unit vector
}

// hit function
bool rectangle::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	// first, check if the ray and the rectangle normal are perpendicular
	// if they are, then the ray is parallel to the rectangle and will not hit
	// even if coplanar, the incident angle is 90degrees so never will absorb (rectangle is infinitely thin)
	if (dot(r.dir, normal) == 0.0) return false;

	// if the dot product is not zero, the ray will intersect the plane that the rectangle lies in
	// find this intersection point next
	vec3 O_RP = origin - r.orig;  // vector from ray origin to plane origin
	double t_hit = dot(O_RP, normal) / dot(r.dir, normal);

	// don't count as a hit if t is not between t_min and t_max
	// this will be used to filter out "backwards" rays (t_hit < 0)
	if (t_hit < t_min || t_hit > t_max) return false;

	// now that it is known the hit point is on the plane, figure out if it is within the rectangle's extents
	point3 p_hit = r.at(t_hit);
	vec3 r_HO = p_hit - origin; // vector from rectangle origin to hit point
	// decompose r_HO into components along the S1 and S2 directions of the rectangle
	vec3 r_HO1 = dot(S1, r_HO) / S1.length_squared() * S1;
	vec3 r_HO2 = dot(S2, r_HO) / S2.length_squared() * S2;

	// if any component of r_HO1 is < 0 or > S1.*d1, the point is outside the rectangle
	vec3 v1 = S1 * d1;
	std::vector<bool> r_HO1_pass = { r_HO1.e[0] < 0, r_HO1.e[1] < 0, r_HO1.e[2] < 0,
									r_HO1.e[0] > v1.e[0], r_HO1.e[1] > v1.e[1] , r_HO1.e[2] > v1.e[2] };
	bool r_HO1_valid = std::any_of(r_HO1_pass.begin(), r_HO1_pass.end(), [](bool x) { return x; });
	if (r_HO1_valid) return false;

	// if any component of r_HO2 is < 0 or > S2.*d2, the point is outside the rectangle
	vec3 v2 = S2 * d2;
	std::vector<bool> r_HO2_pass = { r_HO2.e[0] < 0, r_HO2.e[1] < 0, r_HO2.e[2] < 0,
									r_HO2.e[0] > v2.e[0], r_HO2.e[1] > v2.e[1] , r_HO2.e[2] > v2.e[2] };
	bool r_HO2_valid = std::any_of(r_HO2_pass.begin(), r_HO2_pass.end(), [](bool x) { return x; });
	if (r_HO2_valid) return false;

	// point is inside the rectangle
	rec.t = t_hit;
	rec.p = p_hit;
	rec.normal = normal;
	return true;
}

//END RECTANGLE

#endif // !PRIMITITVES_H
