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


void Scene::registerMesh(MixedMesh *mesh) {
	int triC=0, quadC=0;
	for(size_t i=0; i<mesh->polyCount; i++) {
		if(mesh->polysizes[i] == 3) {
			triC+=3;
		} else {
			quadC+=4;
		}
	}
	// Make enough room for both
	Vertex *newT = new Vertex[this->triCount + triC];
	std::copy(this->tris, this->tris + this->triCount, newT);
	delete [] this->tris;
	this->tris = newT;

	Vertex *newQ = new Vertex[this->quadCount + quadC];
	std::copy(this->quads, this->quads + this->quadCount, newQ);
	delete [] this->quads;
	this->quads = newQ;

	int t = this->triCount, q = this->quadCount;
	this->triCount += triC;
	this->quadCount += quadC;
	// Iterator though the refs in mesh
	int r=0;

	for(size_t i=0; i<mesh->polyCount; i++) {
		if(mesh->polysizes[i] == 3) {
			for(int j = 0; j < 3; j++) {
				Vertex *T = &(this->tris[t++]);
				int ref = mesh->refs[r];
				T->location = mesh->points[ref];
				T->normal = mesh->normals[ref];
				T->colour = mesh->colours[ref];
				r++;
			}
		} else {
			for(int j = 0; j < 4; j++) {
				Vertex *T = &(this->quads[q++]);
				int ref = mesh->refs[r];
				T->location = mesh->points[ref];
				T->normal = mesh->normals[ref];
				T->colour = mesh->colours[ref];
				r++;
			}
		}
	}

}

void Scene::render(void) {
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < this->triCount; i++) {
		Vertex *v = &(this->tris[i]);
		glVertex3f(v->location.x, v->location.y, v->location.z);
		glNormal3f(v->normal.x, v->normal.y, v->normal.z);
		glColor3f(v->colour.r, v->colour.g, v->colour.b);
	}
	glEnd();
	glBegin(GL_QUADS);
	for(int i = 0; i < this->quadCount; i++) {
		Vertex *v = &(this->quads[i]);
		glVertex3f(v->location.x, v->location.y, v->location.z);
		glNormal3f(v->normal.x, v->normal.y, v->normal.z);
		glColor3f(v->colour.r, v->colour.g, v->colour.b);
	}
	glEnd();
}

} /* namespace mroon */
