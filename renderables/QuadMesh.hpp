/*
 * QuadMesh.h
 *
 *  Created on: 7 Dec 2012
 *      Author: duncanm
 */

#ifndef QUADMESH_H_
#define QUADMESH_H_
#include <vector>
#include "Mesh.hpp"

namespace mroon {

class QuadMesh: public mroon::Mesh {
public:
	QuadMesh();
	virtual ~QuadMesh();

	void setQuads(std::vector<int> quads);


	void render(void);
protected:
	/**
	 * List of indexes into the vertices array that make up the list of quads.
	 * Must 4*n entries, where n is the number of quads defined.
	 **/
	std::vector<int> quads;
};

class MixedMesh: public mroon::Mesh {
public:
	MixedMesh();
	virtual ~MixedMesh();

	void setPolys(std::vector<int> refs, std::vector<int> polysizes);


	void render(void);
protected:
	/**
	 * List of indexes into the vertices array that make up the points of each poly
	 **/
	std::vector<int> refs;
	/**
	 * List of size of each poly
	 */
	std::vector<int> polysizes;
};

} /* namespace mroon */
#endif /* QUADMESH_H_ */
