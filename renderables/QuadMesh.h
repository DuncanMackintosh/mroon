/*
 * QuadMesh.h
 *
 *  Created on: 7 Dec 2012
 *      Author: duncanm
 */

#ifndef QUADMESH_H_
#define QUADMESH_H_

#include "Mesh.h"

namespace mroon {

class QuadMesh: public mroon::Mesh {
public:
	QuadMesh();
	virtual ~QuadMesh();

	void setQuads(const int quads[]);
	void setQuads(int count, int *quads);


	void render(void);
protected:
	/**
	 * List of indexes into the vertices array that make up the list of quads.
	 * Must 4*n entries, where n is the number of quads defined.
	 **/
	int quads[];
	int quadCount;
};

} /* namespace mroon */
#endif /* QUADMESH_H_ */
