/*
 * GeneralVector.cpp
 *
 *  Created on: 8 Dec 2012
 *      Author: Mel
 */

#include "GeneralVector.hpp"
#include <math.h>
#include <sstream>


template <int N> GeneralVector<N>::GeneralVector() {
}

template <int N> GeneralVector<N>::GeneralVector(float _components[N]) {
	for(int i = 0; i < N; ++i) {
		components[i] = _components[i];
	}
}


template <int N> int GeneralVector<N>::size() {
	return N;
}

template <int N> float GeneralVector<N>::componentAt(int idx) {
	return components[idx];
}

template <int N> void GeneralVector<N>::set(int idx, float val) {
	components[idx] = val;
}
template <int N> GeneralVector<N> GeneralVector<N>::add(GeneralVector<N> vec) {
	if(size() != vec.size()) return 0; // Error case
	GeneralVector<N> ret = GeneralVector<N>();
	for(int i = 0; i < size(); ++i) {
		ret.set(i, components[i] + vec.componentAt(i));
	}
	return ret;
}

template <int N> GeneralVector<N> GeneralVector<N>::subtract(GeneralVector vec) {
	if(size() != vec.size()) return 0; // Error case
	GeneralVector<N> ret = GeneralVector<N>();
	for(int i = 0; i < size(); ++i) {
		ret.set(i, components[i] + (-1.0f * vec.componentAt(i)));
	}
	return ret;
}

template <int N> float GeneralVector<N>::dotProduct(GeneralVector vec) {
	if(size() != vec.size()) return 0; // Error case... a crap error case.
	float ret = 0;
	for(int i = 0; i < size(); ++i) {
		ret += components[i] * vec.componentAt(i);
	}
	return ret;
}

template <int N> GeneralVector<N> GeneralVector<N>::crossProduct(GeneralVector vec) {
	if(size() != vec.size()) return 0;
	GeneralVector<N> ret = GeneralVector<N>();
	for(int i = 0; i < size(); ++i) {
		ret.set(i, components[(i+1) % size()] * vec.componentAt((i+2) % size())
				- vec.componentAt((i + 1) % size()) * components[(i + 2) % size()]);
	}
	return ret;
}

template <int N> float GeneralVector<N>::length() {
	float ret = 0;
	for(int i = 0; i < size(); ++i) {
		ret += pow(components[i], 2);
	}
	ret = sqrt(ret);
	return ret;
}

template <int N> GeneralVector<N> GeneralVector<N>::scalarMultiply(float k) {
	GeneralVector<N> ret = GeneralVector<N>();
	for(int i = 0; i < size(); ++i) {
		ret.set(i, components[i] * k);
	}
	return ret;
}

template <int N> std::string GeneralVector<N>::stringRep() {
	std::string ret = "[";

	for(int i = 0; i < size(); ++i) {
		if(i != 0) ret += ", ";
		std::stringstream ss (std::stringstream::in | std::stringstream::out);
		ss << components[i];
		ret += ss.str();
	}

	ret += "]";
	return ret;
}

template <int N> GeneralVector<N>::~GeneralVector() {
	//Nothing~
}

template<int N>
inline GeneralVector<N>& GeneralVector<N>::operator =(
		const GeneralVector<N>& rhs) {
	for(int i=0; i<N; i++) {
		components[i] = rhs.components[i];
	}
	return *this;
}

template<int N>
inline float& GeneralVector<N>::operator [](size_t idx) {
	return components[idx];
}

template<int N>
inline const float GeneralVector<N>::operator [](size_t idx) const {
	return components[idx];
}


template class GeneralVector<3>;


