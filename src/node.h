#pragma once
#ifndef NODE_H
#define NODE_H

#include "vec3.h"

// a node is a subdivision of a primitive surface (section of a rectangle, sphere, etc.)
class node {
public:
	node(point3 loc) : location(loc) {}

public:
	point3 location;  // location of the node
	
};

#endif // !NODE_H
