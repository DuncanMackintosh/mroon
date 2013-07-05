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

class MixedMesh: public mroon::Mesh {
public:
	MixedMesh();
	virtual ~MixedMesh();

	void setPolys(std::vector<int> refs, std::vector<int> polysizes);

	static int renders, triRenders, quadRenders, modeSwitches;

	void render(void);

	string toString(void);

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
#endif /* MIXEDMESH_HPP_ */
