#pragma once
#ifndef NODE_H
#define NODE_H

#include "vec3.h"

namespace radacuda {
// a node is a subdivision of a primitive surface (section of a rectangle,
// sphere, etc.)
class node {
 public:
  node(point3 loc) : location(loc) {}

  point3 get_location() { return location; }

 private:
  point3 location;  // location of the node
};

}  // namespace radacuda

#endif  // !NODE_H
