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

class vector3 : public GeneralVector<> {
public:
	vector3() : GeneralVector(){};
	vector3(float values[3]) : GeneralVector(values){};

};

#endif /* VECTOR3_H_ */
