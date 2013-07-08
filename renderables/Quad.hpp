/*
 * Quad.hpp
 *
 *  Created on: 8 Jul 2013
 *      Author: duncanm
 */


#ifndef QUAD_HPP_
#define QUAD_HPP_
#include "../vectors/Vector.hpp"
#include "Colour.hpp"

namespace mroon {

typedef struct {
	Vector3 vertices[4];
	Vector3 normals[4];
	Colour colours[4];
} Quad;

}
#endif
