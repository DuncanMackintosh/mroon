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
			triC++;
		} else {
			quadC++;
		}
	}
	// Make enough room for both
	Tri *newT = new Tri[this->triCount + triC];
	std::copy(this->tris, this->tris + this->triCount, newT);
	delete [] this->tris;
	this->tris = newT;

	Quad *newQ = new Quad[this->quadCount + quadC];
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
			Tri *T = &(this->tris[t++]);
			for(int j = 0; j < 3; j++) {
				int ref = mesh->refs[r];
				T->vertices[j] = mesh->points[ref];
				T->normals[j] = mesh->normals[ref];
				T->colours[j] = mesh->colours[ref];
				r++;
			}
		} else {
			Quad *Q = &(this->quads[q++]);
			for(int j = 0; j < 4; j++) {
				int ref = mesh->refs[r];
				Q->vertices[j] = mesh->points[ref];
				Q->normals[j] = mesh->normals[ref];
				Q->colours[j] = mesh->colours[ref];
				r++;
			}
		}
	}

}

void Scene::render(void) {
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < this->triCount; i++) {
		Tri *t = &(this->tris[i]);
		for(int j=0; j < 3; j++) {
			Vector3 *v = &(t->vertices[j]);
			glVertex3f(v->x, v->y, v->z);
			v = &(t->normals[j]);
			glNormal3f(v->x, v->y, v->z);
			Colour *c = &(t->colours[j]);
			glColor3f(c->r, c->g, c->b);
		}
	}
	glEnd();
	glBegin(GL_QUADS);
	for(int i = 0; i < this->quadCount; i++) {
		Quad *q = &(this->quads[i]);
		for(int j=0; j < 4; j++) {
			Vector3 *v = &(q->vertices[j]);
			glVertex3f(v->x, v->y, v->z);
			v = &(q->normals[j]);
			glNormal3f(v->x, v->y, v->z);
			Colour *c = &(q->colours[j]);
			glColor3f(c->r, c->g, c->b);
		}
	}
	glEnd();
}

} /* namespace mroon */
