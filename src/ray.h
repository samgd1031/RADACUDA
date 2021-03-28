#pragma once

#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include <string>

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

	// define a function that returns a valid gnuplot string that can be combined with the gnuplot commands
	// "splot" or "replot" to plot the ray
	// the ray is plotted parametrically from tmin to tmax
	std::string gnuplot_repr(double tmin, double tmax) {
		////////////////////////////////////////////////////////////
		// THE RANGE FOR T DOES NOT APPEAR TO BE WORKING PROPERLY, range gets set globally
		////////////////////////////////////////////////////////////
		return "[" + std::to_string(tmin) + ":" + std::to_string(tmax) + "]" + std::to_string(orig[0]) + "+ u*" + std::to_string(dir[0])
			+ ", " + std::to_string(orig[1]) + "+ u*" + std::to_string(dir[1])
			+ ", " + std::to_string(orig[2]) + "+ u*" + std::to_string(dir[2]);
	}

public:
	point3 orig;
	vec3 dir;
};

#endif