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

void TriMesh::setTris(int tris[], int triCount) {
	this->tris = tris;
	this->vertexCount = triCount * 3;
}

void TriMesh::render(void) {

	glBegin(GL_TRIANGLES);
		for(size_t i=0; i<this->vertexCount; i++) {
			mroon::Vector3 v = points[tris[i]];
			mroon::Colour c = colours[tris[i]];
			glColor4f(c.r, c.g, c.b, c.a);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(v.x, v.y, v.z);
		}
		TriMesh::renders += vertexCount/3;
	glEnd();
}

} /* namespace mroon */
