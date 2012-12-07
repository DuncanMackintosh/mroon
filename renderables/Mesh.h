/*
 * Mesh.h
 *
 *  Created on: 7 Dec 2012
 *      Author: duncanm
 */

#ifndef MESH_H_
#define MESH_H_

#include "Renderable.h"
#include <vector>
#include "../vectors/Vector.h"

namespace mroon {
// TODO: Move this
typedef struct _coluor {
	float r, g, b, a;
} Colour;

class Mesh: public mroon::Renderable {
public:
	virtual ~Mesh();
	void setVertices(std::vector<Vector3> vertices);
	void setColours(std::vector<Colour> colours);
protected:
	std::vector<mroon::Vector3> vertices;
	std::vector<mroon::Colour> colours;

};

} /* namespace mroon */
#endif /* MESH_H_ */
