/*
 * Mesh.cpp
 *
 *  Created on: 7 Dec 2012
 *      Author: duncanm
 */

#include "Mesh.hpp"
#include <vector>
#include <limits>
#include <stdio.h>

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
	if (colours.size() != vertices.size()) {
		// TODO: Crash
		return;
	}
	this->colours = colours;
}

void Mesh::dbgBounds(void) {
	float maxF = std::numeric_limits<float>::max();
	float minF = std::numeric_limits<float>::min();
	Vector3 min(maxF, maxF, maxF), max(minF, minF, minF);
	for(size_t i=0; i<vertices.size(); i++) {
		if(vertices[i].x > max.x) max.x = vertices[i].x;
		if(vertices[i].y > max.y) max.y = vertices[i].y;
		if(vertices[i].z > max.z) max.z = vertices[i].z;

		if(vertices[i].x < min.x) min.x = vertices[i].x;
		if(vertices[i].y < min.y) min.y = vertices[i].y;
		if(vertices[i].z < min.z) min.z = vertices[i].z;
	}

	Vector3 centre = min + (max-min)/2;
	Vector3 scale = max-min;
	printf("Centre: %s\n", centre.toString());
	printf("Scale: %s\n", scale.toString());
}

} /* namespace mroon */

mroon::Colour::Colour(float r, float g, float b, float _a) :
		r(r), g(g), b(b), a(a) {
}

mroon::Colour::Colour(float r, float g, float b) :
		r(r), g(g), b(b), a(1.0f) {
}

mroon::Colour::Colour() :
		r(1.0f), g(1.0f), b(1.0f), a(1.0f) {
}
