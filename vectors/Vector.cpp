/*
 * Vector.cpp
 *
 *  Created on: 7 Dec 2012
 *      Author: Duncan
 */

#include "Vector.hpp"
#include <stdio.h>
#include <sstream>
#include <iomanip>

namespace mroon {

_vector3::_vector3(float x, float y, float z) : x(x), y(y), z(z){}
_vector3::_vector3() : x(0.0f), y(0.0f), z(0.0f){}
struct _vector3 _vector3::operator-(struct _vector3 o) {
	return _vector3(this->x - o.x, this->y - o.y, this->z - o.z);
}
struct _vector3 _vector3::operator+(struct _vector3 o){
	return _vector3(x + o.x, y + o.y, z + o.z);
}
struct _vector3 _vector3::operator/(float divisor){
	return _vector3(this->x/divisor, this->y/divisor, this->z/divisor);
}
struct _vector3 _vector3::operator*(float multiplier){
	return _vector3(this->x*multiplier, this->y*multiplier, this->z*multiplier);
}

string _vector3::toString() {
	stringstream ss;
	ss << setprecision(2) << "[" << x << ", " << y << ", " << z << "]";
	return ss.str();
}

Vector3 mroon::Vector3::up = Vector3(0.0f, 1.0f, 0.0f);

} /* namespace mroon */
