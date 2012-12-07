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
	Colour defColour = Colour({1.0f, 1.0f, 1.0f, 1.0f});
	this->colours = std::vector<Colour>(vertices.size(), defColour);
}
void Mesh::setColours(std::vector<Colour> colours) {
	if(colours.size() != vertices.size()) {
		// TODO: Crash
		return;
	}
	this->colours = colours;
}
} /* namespace mroon */
