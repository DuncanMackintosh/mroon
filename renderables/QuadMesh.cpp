/*
 * QuadMesh.cpp
 *
 *  Created on: 7 Dec 2012
 *      Author: duncanm
 */

#include <stdio.h>
#include "QuadMesh.h"
#include <GL/glut.h>

namespace mroon {

QuadMesh::QuadMesh() {
	// TODO Auto-generated constructor stub

}

QuadMesh::~QuadMesh() {
	// TODO Auto-generated destructor stub
}

void QuadMesh::setQuads(int count, int *quads) {
	printf("Asked to store %d quads\n", count);
	delete this->quads;
	this->quads = quads;
	this->quadCount = count;
}

void QuadMesh::render(void) {
	glBegin(GL_QUADS);
		for(int i=0; i<quadCount; i+=4)
	glEnd();
}

} /* namespace mroon */
