/*
 * Mesh.h
 *
 *  Created on: 7 Dec 2012
 *      Author: duncanm
 */

#ifndef MESH_H_
#define MESH_H_

#include "Renderable.hpp"
#include <vector>
#include "../vectors/Vector.hpp"

namespace mroon {
// TODO: Move this
struct Colour {
	float r, g, b, a;
public:
	Colour(float r, float g, float b, float a);
Colour(float r, float g, float b);
	Colour();
};

class Mesh: public mroon::Renderable {
public:
	virtual ~Mesh();
	void setVertices(std::vector<Vector3> vertices);
	void setColours(std::vector<Colour> colours);
	std::vector<Vector3> getVertices(void);
	std::vector<Colour> getColours(void);
	void dbgBounds(void);
protected:
	std::vector<mroon::Vector3> vertices;
	std::vector<mroon::Colour> colours;

};

} /* namespace mroon */
#endif /* MESH_H_ */
