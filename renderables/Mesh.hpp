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
	void setPoints(Vector3 points[], int pointCount);
	void setPoints(vector<Vector3> points);
	void setNormals(Vector3 normals[]);
	void setNormals(vector<Vector3> normals);
	void setColours(Colour colours[]);
	void setColours(vector<Colour> colours);
	Vector3 *getPoints(void);
	Colour *getColours(void);
	Vector3 getCentre(void);
	Vector3 getScale(void);
	int getPointCount(void);
	int getVertexCount(void);
	string toString(void);
protected:
	/** Control points that make up the mesh, as Vector3s in world space. The
	 * polygons of the mesh are made up by indexing into this array for each
	 * mesh vertex (so a given control point can be a vertex for more than one
	 * polygon). */
	Vector3 *points;
	/** Normal vectors for each vertex of the mesh */
	Vector3 *normals;
	Colour *colours;
	size_t pointCount;
	size_t vertexCount;

};

} /* namespace mroon */
#endif /* MESH_H_ */
