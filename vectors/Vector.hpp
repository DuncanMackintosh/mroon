/*
 * Vector.h
 *
 *  Created on: 7 Dec 2012
 *      Author: Duncan
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <string>
using namespace std;

namespace mroon {

typedef struct _vector3 {
	float x, y, z;
public:
	_vector3(float x, float y, float z);
	_vector3();
	struct _vector3 operator-(struct _vector3 o);
	struct _vector3 operator+(struct _vector3 o);
	struct _vector3 operator/(float divisor);
	struct _vector3 operator*(float multiplier);
	string toString();

	static struct _vector3 up;
} Vector3;



} /* namespace mroon */
#endif /* VECTOR_H_ */
