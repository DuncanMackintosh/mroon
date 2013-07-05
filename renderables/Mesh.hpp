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
#include <string>
#include "../vectors/Vector.hpp"
#include "Colour.hpp"

using namespace std;

namespace mroon {

class Mesh: public mroon::Renderable {
public:
	virtual ~Mesh();
	void setVertices(std::vector<Vector3> vertices);
	void setNormals(std::vector<Vector3> normals);
	void setColours(std::vector<Colour> colours);
	vector<Vector3> getVertices(void);
	vector<Colour> getColours(void);
	Vector3 getCentre(void);
	Vector3 getScale(void);
	string toString(void);
protected:
	vector<Vector3> vertices;
	vector<Vector3> normals;
	vector<Colour> colours;

};

} /* namespace mroon */
#endif /* MESH_H_ */
