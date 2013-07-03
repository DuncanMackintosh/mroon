/*
 * TriMesh.h
 *
 *  Created on: 7 Dec 2012
 *      Author: duncanm
 */

#ifndef TRIMESH_H_
#define TRIMESH_H_
#include <vector>
#include "Mesh.hpp"

namespace mroon {

class TriMesh: public mroon::Mesh {
public:
	TriMesh();
	virtual ~TriMesh();

	void setTris(std::vector<int> quads);


	void render(void);

	static int renders;

protected:
	/**
	 * List of indexes into the vertices array that make up the list of quads.
	 * Must 4*n entries, where n is the number of quads defined.
	 **/
	std::vector<int> tris;
};

} /* namespace mroon */
#endif /* TRIMESH_H_ */
