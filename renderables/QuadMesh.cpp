/*
 * QuadMesh.cpp
 *
 *  Created on: 7 Dec 2012
 *      Author: duncanm
 */

#include "QuadMesh.hpp"
#include <GL/glut.h>
#include <sstream>
#include <iomanip>

namespace mroon {

int QuadMesh::renders = 0;

QuadMesh::QuadMesh() {

}

QuadMesh::~QuadMesh() {

}

void QuadMesh::setQuads(int quads[], int quadCount) {
	this->quads = quads;
	this->vertexCount = quadCount * 4;
}

void QuadMesh::render(void) {

	glBegin(GL_QUADS);
		for(size_t i=0; i<vertexCount; i++) {
			mroon::Vector3 *v = &(points[quads[i]]);
			mroon::Colour *c = &(colours[quads[i]]);
			mroon::Vector3 *n = &(normals[quads[i]]);
			glColor4f(c->r, c->g, c->b, c->a);
			glNormal3f(n->x, n->y, n->z);
			glVertex3f(v->x, v->y, v->z);
		}
		QuadMesh::renders += vertexCount/4;
	glEnd();
}


} /* namespace mroon */
