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
#include <iostream>
#include <memory>

namespace mroon {

Mesh::~Mesh() {

}

void Mesh::setPoints(vector<Vector3> points) {
	Vector3 *cpy = new Vector3[points.size()];
	std::copy(points.begin(), points.end(), cpy);
	this->setPoints(cpy, points.size());
}

void Mesh::setPoints(Vector3 points[], int pointCount) {
	this->points = points;
	this->pointCount = pointCount;
}

void Mesh::setNormals(vector<Vector3> normals) {
	Vector3 *cpy = new Vector3[normals.size()];
	std::copy(normals.begin(), normals.end(), cpy);
	this->setNormals(cpy);
}

void Mesh::setNormals(Vector3 normals[]) {
	this->normals = normals;
}

Vector3 *Mesh::getPoints(void) {
	return this->points;
}

Colour *Mesh::getColours(void) {
	return this->colours;
}

void Mesh::setColours(vector<Colour> colours) {
	Colour *cpy = new Colour[colours.size()];
	std::copy(colours.begin(), colours.end(), cpy);
	this->setColours(cpy);
}


void Mesh::setColours(Colour colours[]) {
	this->colours = colours;
}

Vector3 Mesh::getScale(void) {
	float maxF = std::numeric_limits<float>::max();
	float minF = std::numeric_limits<float>::min();
	Vector3 min(maxF, maxF, maxF), max(minF, minF, minF);
	for(size_t i=0; i<pointCount; i++) {
		if(points[i].x > max.x) max.x = points[i].x;
		if(points[i].y > max.y) max.y = points[i].y;
		if(points[i].z > max.z) max.z = points[i].z;

		if(points[i].x < min.x) min.x = points[i].x;
		if(points[i].y < min.y) min.y = points[i].y;
		if(points[i].z < min.z) min.z = points[i].z;
	}
	return max-min;
}

Vector3 Mesh::getCentre(void) {
	float maxF = std::numeric_limits<float>::max();
	float minF = std::numeric_limits<float>::min();
	Vector3 min(maxF, maxF, maxF), max(minF, minF, minF);
	for(size_t i=0; i<pointCount; i++) {
		if(points[i].x > max.x) max.x = points[i].x;
		if(points[i].y > max.y) max.y = points[i].y;
		if(points[i].z > max.z) max.z = points[i].z;

		if(points[i].x < min.x) min.x = points[i].x;
		if(points[i].y < min.y) min.y = points[i].y;
		if(points[i].z < min.z) min.z = points[i].z;
	}
	return min + (max-min)/2;
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
