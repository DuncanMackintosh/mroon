/*
 * Vector.cpp
 *
 *  Created on: 7 Dec 2012
 *      Author: Duncan
 */

#include "Vector.hpp"
#include <stdio.h>

namespace mroon {
//
//Vector::Vector() {
//	// TODO Auto-generated constructor stub
//
//}
//
//Vector::~Vector() {
//	// TODO Auto-generated destructor stub
//}
_vector::_vector(float x, float y, float z) : x(x), y(y), z(z){}
_vector::_vector() : x(0.0f), y(0.0f), z(0.0f){}
struct _vector _vector::operator-(struct _vector o) {
	return _vector(this->x - o.x, this->y - o.y, this->z - o.z);
}
struct _vector _vector::operator+(struct _vector o){}
struct _vector _vector::operator/(float divisor){
	return _vector(this->x/divisor, this->y/divisor, this->z/divisor);
}
struct _vector _vector::operator*(float multiplier){
	return _vector(this->x*multiplier, this->y*multiplier, this->z*multiplier);
}

char* _vector::toString() {
	char* out = new char[255];
	snprintf(out, 255, "[%f, %f, %f]", x, y, z);
	return out;
}

Vector3 mroon::Vector3::up = Vector3(0.0f, 1.0f, 0.0f);

} /* namespace mroon */
