/*
 * QuadMesh.h
 *
 *  Created on: 7 Dec 2012
 *      Author: duncanm
 */

#ifndef QUADMESH_H_
#define QUADMESH_H_
#include <vector>
#include <string>

using namespace std;
#include "Mesh.hpp"


namespace mroon {

class QuadMesh: public mroon::Mesh {
public:
	QuadMesh();
	virtual ~QuadMesh();

	void setQuads(std::vector<int> quads);


	void render(void);

	static int renders;
protected:
	/**
	 * List of indexes into the vertices array that make up the list of quads.
	 * Must 4*n entries, where n is the number of quads defined.
	 **/
	std::vector<int> quads;
};


} /* namespace mroon */
#endif /* QUADMESH_H_ */
