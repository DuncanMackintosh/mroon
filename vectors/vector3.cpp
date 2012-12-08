/*
 * vector3.cpp
 *
 *  Created on: 8 Dec 2012
 *      Author: Mel
 */

#include "vector3.h"

vector3::vector3 ()
	: GeneralVector(3) {

}

vector3::vector3(std::vector<float> components)
	: GeneralVector(3, components) {

}

