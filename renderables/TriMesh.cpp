/*
 * QuadMesh.cpp
 *
 *  Created on: 7 Dec 2012
 *      Author: duncanm
 */

#include <stdio.h>
#include "TriMesh.hpp"
#include <GL/glut.h>
#include <vector>

namespace mroon {
int TriMesh::renders = 0;
TriMesh::TriMesh() {

}

TriMesh::~TriMesh() {

}

void TriMesh::setTris(std::vector<int> tris) {
	// TODO: Exception
	if(tris.size() % 3 != 0) return;
	this->tris = tris;
}

void TriMesh::render(void) {

	glBegin(GL_TRIANGLES);
		for(size_t i=0; i<this->tris.size(); i++) {
			mroon::Vector3 v = vertices[tris[i]];
			mroon::Colour c = colours[tris[i]];
			glColor4f(c.r, c.g, c.b, c.a);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(v.x, v.y, v.z);
			TriMesh::renders++;
		}
	glEnd();
}

} /* namespace mroon */
