/*
 * vector3.h
 *
 *  Created on: 8 Dec 2012
 *      Author: Mel
 */

#ifndef VECTOR3_H_
#define VECTOR3_H_

#include "GeneralVector.h"
#include <vector>

class vector3 : public GeneralVector {
public:
	vector3 (std::vector<float> components);
	vector3();
};


#endif /* VECTOR3_H_ */
