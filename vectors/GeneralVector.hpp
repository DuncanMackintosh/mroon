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



template <int N = 3> class GeneralVector {
protected:
	float components[N];

public:
	GeneralVector();
	GeneralVector(float _components[N]);
	virtual ~GeneralVector();

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

	GeneralVector<N>& operator=(const GeneralVector<N> &rhs);
	float& operator[](size_t idx);
	const float operator[](size_t idx) const;

private:
	void create();

};


#endif /* GENERALVECTOR_H_ */
