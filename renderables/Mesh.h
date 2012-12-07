/*
 * Mesh.h
 *
 *  Created on: 7 Dec 2012
 *      Author: duncanm
 */

#ifndef MESH_H_
#define MESH_H_

#include "Renderable.h"

namespace mroon {

class Mesh: public mroon::Renderable {
public:
	virtual ~Mesh();
protected:
	int vertexCount;
	float vertices[];

};

} /* namespace mroon */
#endif /* MESH_H_ */
