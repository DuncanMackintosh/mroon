#include "MixedMesh.hpp"
#include <GL/glut.h>
#include <sstream>
#include <iomanip>

namespace mroon {

MixedMesh::MixedMesh() {}
MixedMesh::~MixedMesh() {}

int MixedMesh::renders = 0;

void MixedMesh::setPolys(std::vector<int> refs, std::vector<int> polysizes) {
	this->refs = refs;
	this->polysizes = polysizes;
}

void MixedMesh::render(void) {

	int r = 0;
	for(size_t i=0; i<this->polysizes.size(); i++) {
		if(this->polysizes[i] == 3) {
			glBegin(GL_TRIANGLES);
		} else if(this->polysizes[i] == 4) {
			glBegin(GL_QUADS);
		} else {
			continue;
		}
		for(int j=0; j<this->polysizes[i]; j++) {
			int ref = r++;
			mroon::Vector3 *v = &(vertices[this->refs[ref]]);
			mroon::Colour *c = &(colours[this->refs[ref]]);
			mroon::Vector3 *n = &(normals[this->refs[ref]]);
			glColor4f(c->r, c->g, c->b, c->a);
			glNormal3f(n->x, n->y, n->z);
			glVertex3f(v->x, v->y, v->z);
			MixedMesh::renders++;
		}
		glEnd();
	}
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
