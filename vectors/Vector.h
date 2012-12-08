/*
 * Vector.h
 *
 *  Created on: 7 Dec 2012
 *      Author: Duncan
 */

#ifndef VECTOR_H_
#define VECTOR_H_

namespace mroon {

//class Vector {
//public:
//	Vector();
//	virtual ~Vector();
//};

typedef struct _vector {
	float x, y, z;
public:
	_vector(float x, float y, float z);
	_vector();
} Vector3;

} /* namespace mroon */
#endif /* VECTOR_H_ */
