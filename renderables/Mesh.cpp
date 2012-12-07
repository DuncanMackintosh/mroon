/*
 * Mesh.cpp
 *
 *  Created on: 7 Dec 2012
 *      Author: duncanm
 */

#include "Mesh.h"
#include <vector>

namespace mroon {

Mesh::~Mesh() {

}

void Mesh::setVertices(std::vector<Vector3> vertices) {
	this->vertices = vertices;
	Colour defColour = Colour(1.0f, 1.0f, 1.0f, 1.0f);
	this->colours = std::vector<Colour>(vertices.size(), defColour);
}
std::vector<Vector3> Mesh::getVertices(void) {
	return this->vertices;
}

std::vector<Colour> Mesh::getColours(void) {
	return this->colours;
}
void Mesh::setColours(std::vector<Colour> colours) {
	if(colours.size() != vertices.size()) {
		// TODO: Crash
		return;
	}
	this->colours = colours;
}
} /* namespace mroon */

mroon::Colour::Colour(float r, float g, float b, float _a) : r(r), g(g), b(b), a(a) {
}

mroon::Colour::Colour(float r, float g, float b) : r(r), g(g), b(b), a(1.0f)  {
}

mroon::Colour::Colour() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {
}
