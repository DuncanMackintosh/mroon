/*
 * QuadMesh.cpp
 *
 *  Created on: 7 Dec 2012
 *      Author: duncanm
 */

#include <stdio.h>
#include "QuadMesh.hpp"
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
		for(size_t i=0; i<this->quads.size(); i++) {
			mroon::Vector3 v = vertices[quads[i]];
			mroon::Colour c = colours[quads[i]];
			glColor4f(c.r, c.g, c.b, c.a);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(v.x, v.y, v.z);
		}
	glEnd();
}

MixedMesh::MixedMesh() {}
MixedMesh::~MixedMesh() {}

void MixedMesh::setPolys(std::vector<int> refs, std::vector<int> polysizes) {
	this->refs = refs;
	this->polysizes = polysizes;
}

void MixedMesh::render(void) {
	size_t r = 0;
	for(size_t i=0; i<this->polysizes.size(); i++) {
		if(this->polysizes[i] == 3) {
			glBegin(GL_TRIANGLES);
		} else if(this->polysizes[i] == 4) {
			glBegin(GL_QUADS);
		} else {
			continue;
		}
		for(size_t j=0; j<this->polysizes[i]; j++) {
			mroon::Vector3 v = vertices[this->refs[i]];
			mroon::Colour c = colours[this->refs[i]];
			glColor4f(c.r, c.g, c.b, c.a);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(v.x, v.y, v.z);
		}
		glEnd();
	}
}

} /* namespace mroon */
