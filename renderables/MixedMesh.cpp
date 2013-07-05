#define MINIMISE_SWAPS
#include "MixedMesh.hpp"
#include <GL/glut.h>
#include <sstream>
#include <iomanip>

namespace mroon {

MixedMesh::MixedMesh() {}
MixedMesh::~MixedMesh() {}

int MixedMesh::renders = 0;
int MixedMesh::triRenders = 0;
int MixedMesh::quadRenders = 0;
int MixedMesh::modeSwitches = 0;

void MixedMesh::setPolys(std::vector<int> refs, std::vector<int> polysizes) {
	this->refs = refs;
	this->polysizes = polysizes;
}

void MixedMesh::render(void) {

	int r = 0;
	// Tricks so that, if possible, we do one long run of GL_TRIANGLES
	// or GL_QUADS, rather than constantly doing glBegin()...glEnd()
	int lastSize = 0;
	// Check to make sure we don't glEnd() on the first iteration,
	// and don't glEnd() at the end either if we had 0 iterations
	bool ended = true;
	for(size_t i=0; i<this->polysizes.size(); i++) {
		if(this->polysizes[i] == 3) {
#ifdef MINIMISE_SWAPS
			if(lastSize != 3) {
				if(!ended) glEnd();
				glBegin(GL_TRIANGLES);
				lastSize = 3;
				ended = false;
				MixedMesh::modeSwitches++;
			}
#else
			glBegin(GL_TRIANGLES);
			MixedMesh::modeSwitches++;
#endif
			MixedMesh::triRenders++;
		} else if(this->polysizes[i] == 4) {
#ifdef MINIMISE_SWAPS
			if(lastSize != 4) {
				if(!ended) glEnd();
				glBegin(GL_QUADS);
				lastSize = 4;
				ended = false;
				MixedMesh::modeSwitches++;
			}
#else
			glBegin(GL_QUADS);
			MixedMesh::modeSwitches++;
#endif
			MixedMesh::quadRenders++;
		} else {
			continue;
		}
		for(int j=0; j<this->polysizes[i]; j++) {
			int ref = this->refs[r];
			// Apparently this is faster than inlining the references?
			mroon::Vector3 *v = &(vertices[ref]);
			mroon::Vector3 *n = &(normals[r]);
			mroon::Colour *c = &(colours[r]);
			glColor4f(c->r, c->g, c->b, c->a);
			glNormal3f(n->x, n->y, n->z);
			glVertex3f(v->x, v->y, v->z);
			MixedMesh::renders++;
			r++;


//			int ref = this->refs[r];
//			glColor4f(colours[r].r, colours[r].g, colours[r].b, colours[r].a);
//			glNormal3f(normals[r].x, normals[r].y, normals[r].z);
//			glVertex3f(vertices[ref].x, vertices[ref].y, vertices[ref].z);
//			r++;
//			MixedMesh::renders++;
		}
#ifndef MINIMISE_SWAPS
		glEnd();
#endif
	}
	if(!ended) glEnd();
}

string MixedMesh::toString(void) {
	stringstream ss;
	ss << setprecision(1)
			<< vertices.size() << " vertices\t"
			<< normals.size() << " normals\t"
			<< polysizes.size() << " polys\t"
			<< refs.size() << " polypoints\t"
			<< "Centre: " << getCentre().toString()
			<< "\tScale: " << getScale().toString()
			;
	return ss.str();
}
} /* namespace mroon */
