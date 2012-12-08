/*
 * GeneralVector.h
 *
 *  Created on: 8 Dec 2012
 *      Author: Mel
 */

#ifndef GENERALVECTOR_H_
#define GENERALVECTOR_H_

#include <vector>
#include <string>

class GeneralVector {
	int numComponents;
	std::vector<float> components;

public:
	GeneralVector(int _numComponents, std::vector<float> _components);
	GeneralVector(int _numComponents);
	~GeneralVector();

	int size();
	void set(int idx, float val);
	float componentAt(int idx);
	GeneralVector add(GeneralVector vec);
	GeneralVector subtract(GeneralVector vec);
	float dotProduct(GeneralVector vec);
	GeneralVector crossProduct(GeneralVector vec);
	float length();
	GeneralVector scalarMultiply(float k);
	std::string stringRep();

private:
	void create(int _numComponents);

};


#endif /* GENERALVECTOR_H_ */
