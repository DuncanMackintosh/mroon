/*
 * vector3.h
 *
 *  Created on: 8 Dec 2012
 *      Author: Mel
 */

#ifndef VECTOR3_H_
#define VECTOR3_H_

#include "GeneralVector.hpp"
#include <vector>

class Vector3 : public GeneralVector<3> {
public:
	Vector3() : GeneralVector<3>(){};
	Vector3(float values[3]) : GeneralVector<3>(values){};
	Vector3(float x, float y, float z);
};

#endif /* VECTOR3_H_ */
