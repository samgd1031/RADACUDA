#pragma once

#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
public:
	//constructor
	// a ray is defined by a point (the origin) and a vector (the direction the ray propagates from)
	ray() {}
	ray(const point3& origin, const vec3& direction)
		: orig(origin), dir(direction)
	{}

	// any point on the array can be described by introducing a parameter "t" (point = origin + t*direction)
	// this function returns a point on the ray given the value of t
	point3 at(double t) const {
		return orig + t * dir;
	}

public:
	point3 orig;
	vec3 dir;
};

#endif