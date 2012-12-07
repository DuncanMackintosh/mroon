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

void QuadMesh::setQuads(const int quads[]) {
	printf("Asked to store %d quads\n", sizeof(quads)/sizeof(int));
}

void QuadMesh::render(void) {

}

} /* namespace mroon */
