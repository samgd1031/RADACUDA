#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include "utility.h"

// define a class that stores material properties and determines how rays are
// scattered upon a hit

struct hit_record;

/* this syntax is invalid, but I'm leaving it incase dupas wants to come back to
it. class material { public: virtual bool scatter( const ray& r_in, const
hit_record&rec,
        );
};
*/

#endif  // !MATERIAL_H
