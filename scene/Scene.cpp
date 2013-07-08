/*
 * Scene.cpp
 *
 *  Created on: 11 Dec 2012
 *      Author: duncanm
 */

#include "Scene.hpp"
#include <GL/glut.h>

namespace mroon {

Scene::Scene() {
	// TODO Auto-generated constructor stub

}

Scene::~Scene() {
	// TODO Auto-generated destructor stub
}

// 3 for location, 3 for normal, 3 for colour (for now)
#define FLOAT_COUNT 9

void Scene::registerMesh(MixedMesh *mesh) {
	int triC=0, quadC=0;
	for(size_t i=0; i<mesh->polyCount; i++) {
		if(mesh->polysizes[i] == 3) {
			triC+=(3*FLOAT_COUNT);
		} else {
			quadC+=(4*FLOAT_COUNT);
		}
	}
	// Make enough room for both
	float *newT = new float[this->triCount + triC];
	std::copy(this->triData, this->triData + this->triCount, newT);
	delete [] this->triData;
	this->triData = newT;

	float *newQ = new float[this->quadCount + quadC];
	std::copy(this->quadData, this->quadData + this->quadCount, newQ);
	delete [] this->quadData;
	this->quadData = newQ;

	int t = this->triCount, q = this->quadCount;
	this->triCount += triC;
	this->quadCount += quadC;
	// Iterator though the refs in mesh
	int r=0;

	for(size_t i=0; i<mesh->polyCount; i++) {
		if(mesh->polysizes[i] == 3) {
			for(int j = 0; j < 3; j++) {
				int ref = mesh->refs[r];
				this->triData[t++] = mesh->points[ref].x;
				this->triData[t++] = mesh->points[ref].y;
				this->triData[t++] = mesh->points[ref].z;
				this->triData[t++] = mesh->normals[ref].x;
				this->triData[t++] = mesh->normals[ref].y;
				this->triData[t++] = mesh->normals[ref].z;
				this->triData[t++] = mesh->colours[ref].r;
				this->triData[t++] = mesh->colours[ref].g;
				this->triData[t++] = mesh->colours[ref].b;
				r++;
			}
		} else {
			for(int j = 0; j < 4; j++) {
				int ref = mesh->refs[r];
				this->quadData[q++] = mesh->points[ref].x;
				this->quadData[q++] = mesh->points[ref].y;
				this->quadData[q++] = mesh->points[ref].z;
				this->quadData[q++] = mesh->normals[ref].x;
				this->quadData[q++] = mesh->normals[ref].y;
				this->quadData[q++] = mesh->normals[ref].z;
				this->quadData[q++] = mesh->colours[ref].r;
				this->quadData[q++] = mesh->colours[ref].g;
				this->quadData[q++] = mesh->colours[ref].b;
				r++;
			}
		}
	}

}

void Scene::render(void) {
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < this->triCount;) {
		glVertex3fv(&this->triData[i]);
		i += 3;
		glNormal3fv(&this->triData[i]);
		i += 3;
		glColor3fv(&this->triData[i]);
		i += 3;
	}
	glEnd();
	glBegin(GL_QUADS);
	for(int i = 0; i < this->quadCount;) {
		glVertex3fv(&this->quadData[i]);
		i += 3;
		glNormal3fv(&this->quadData[i]);
		i += 3;
		glColor3fv(&this->quadData[i]);
		i += 3;
	}
	glEnd();
}

} /* namespace mroon */
