/*
 * QuadMesh.cpp
 *
 *  Created on: 7 Dec 2012
 *      Author: duncanm
 */

#include <stdio.h>
#include "QuadMesh.h"
#include <GL/glut.h>
#include <vector>

namespace mroon {

QuadMesh::QuadMesh() {

}

QuadMesh::~QuadMesh() {

}

void QuadMesh::setQuads(std::vector<int> quads) {
	// TODO: Exception
	if(quads.size() % 4 != 0) return;
	this->quads = quads;
}

void QuadMesh::render(void) {
	glBegin(GL_QUADS);
		for(size_t i=0; i<this->quads.size(); i+=4) {
			mroon::Vector3 v = vertices[quads[i]];
			mroon::Colour c = colours[quads[i]];
			glColor4f(c.r, c.g, c.b, c.a);
			glVertex3f(v.x, v.y, v.z);
		}
	glEnd();
}

} /* namespace mroon */
