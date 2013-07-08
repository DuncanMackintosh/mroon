/*
 * MixedMesh.hpp
 *
 *  Created on: 3 Jul 2013
 *      Author: duncanm
 */

#ifndef MIXEDMESH_HPP_
#define MIXEDMESH_HPP_
#include <vector>
#include <string>

using namespace std;
#include "Mesh.hpp"


namespace mroon {

class MixedMesh: public mroon::Mesh{
public:
	MixedMesh();
	virtual ~MixedMesh();

	void setPolys(int refs[], int polysizes[], int polyCount);

	void setPolys(vector<int> refs, vector<int> sizes);

	static int renders, triRenders, quadRenders, modeSwitches;

	void render(void);

	string toString(void);

	friend class Scene;

	/**
	 * List of indexes into the vertices array that make up the points of each poly
	 * There are vertexCount of these. They are in the same order as polysizes,
	 * but for each entry in polysizes[] there'll be 3 or 4 entries in this
	 * array.
	 **/
	int *refs;
	/**
	 * List of size of each poly. There are polyCount of these
	 */
	int *polysizes;
	/** Number of polygons defined. */
	size_t polyCount;
};

} /* namespace mroon */
#endif /* MIXEDMESH_HPP_ */
