/*
 * Colour.hpp
 *
 *  Created on: 3 Jul 2013
 *      Author: duncanm
 */

#ifndef COLOUR_HPP_
#define COLOUR_HPP_

namespace mroon {
struct Colour {
	float r, g, b, a;
public:
	Colour(float r, float g, float b, float a);
	Colour(float r, float g, float b);
	Colour();
};
} /* namespace mroon */


#endif /* COLOUR_HPP_ */
