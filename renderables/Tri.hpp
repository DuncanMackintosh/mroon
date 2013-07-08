/*
 * Tri.hpp
 *
 *  Created on: 8 Jul 2013
 *      Author: duncanm
 */


#ifndef TRI_HPP_
#define TRI_HPP_
#include "../vectors/Vector.hpp"
#include "Colour.hpp"

namespace mroon {

typedef struct {
	Vector3 vertices[3];
	Vector3 normals[3];
	Colour colours[3];
} Tri;

}
#endif
