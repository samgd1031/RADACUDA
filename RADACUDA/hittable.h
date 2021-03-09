#pragma once

#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct hit_record {
	// store some information about the ray/object intersection
	point3 p; // point of intersection
	vec3 normal; // surface normal at point p
	double t; // ray parameter at intersection
};

// define a generic class for any object that could be hit by a ray
class hittable {
public:
	// function that returns true if there is a hit and false if there isnt
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif // !HITTABLE_H
