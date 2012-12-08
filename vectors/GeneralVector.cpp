/*
 * GeneralVector.cpp
 *
 *  Created on: 8 Dec 2012
 *      Author: Mel
 */

#include "GeneralVector.h"
#include <math.h>
#include <sstream>

GeneralVector::GeneralVector(int _numComponents, std::vector<float> _components) {
	create(_numComponents);
	for(int i = 0; i < numComponents; ++i) {
		components[i] = _components[i];
	}
}

GeneralVector::GeneralVector(int _numComponents) {
	create(_numComponents);
}

void GeneralVector::create(int _numComponents) {
	numComponents = _numComponents;
	components = std::vector<float>(numComponents);
}

int GeneralVector::size() {
	return numComponents;
}

float GeneralVector::componentAt(int idx) {
	return components[idx];
}

void GeneralVector::set(int idx, float val) {
	components[idx] = val;
}
GeneralVector GeneralVector::add(GeneralVector vec) {
	if(size() != vec.size()) return 0; // Error case
	GeneralVector ret = GeneralVector(numComponents);
	for(int i = 0; i < size(); ++i) {
		ret.set(i, components[i] + vec.componentAt(i));
	}
	return ret;
}

GeneralVector GeneralVector::subtract(GeneralVector vec) {
	if(size() != vec.size()) return 0; // Error case
	GeneralVector ret = GeneralVector(numComponents);
	for(int i = 0; i < size(); ++i) {
		ret.set(i, components[i] + (-1.0f * vec.componentAt(i)));
	}
	return ret;
}

float GeneralVector::dotProduct(GeneralVector vec) {
	if(size() != vec.size()) return 0; // Error case... a crap error case.
	float ret = 0;
	for(int i = 0; i < size(); ++i) {
		ret += components[i] * vec.componentAt(i);
	}
	return ret;
}

GeneralVector GeneralVector::crossProduct(GeneralVector vec) {
	if(size() != vec.size()) return 0;
	GeneralVector ret = GeneralVector(size());
	for(int i = 0; i < size(); ++i) {
		ret.set(i, components[(i+1) % size()] * vec.componentAt((i+2) % size())
				- vec.componentAt((i + 1) % size()) * components[(i + 2) % size()]);
	}
	return ret;
}

float GeneralVector::length() {
	float ret = 0;
	for(int i = 0; i < size(); ++i) {
		ret += pow(components[i], 2);
	}
	ret = sqrt(ret);
	return ret;
}

GeneralVector GeneralVector::scalarMultiply(float k) {
	GeneralVector ret = GeneralVector(size());
	for(int i = 0; i < size(); ++i) {
		ret.set(i, components[i] * k);
	}
	return ret;
}

std::string GeneralVector::stringRep() {
	std::string ret = "[";

	for(int i = 0; i < size(); ++i) {
		if(i != 0) ret += ", ";
		std::stringstream ss (std::stringstream::in | std::stringstream::out);
		ss << components[i];
		ret += ss.str();
	}

	ret += "]";
	return ret;
}

GeneralVector::~GeneralVector() {
	//Nothing~
}



