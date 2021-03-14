#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include "utility.h"

//define a class that stores material properties and determines how rays are scattered upon a hit

struct hit_record;

class material {
public:
	virtual bool scatter(
		const ray& r_in, const hit_record&rec, 
	)
};

#endif // !MATERIAL_H
