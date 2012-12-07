/*
 * Renderable.h
 *
 *  Created on: 7 Dec 2012
 *      Author: duncanm
 */

#ifndef RENDERABLE_H_
#define RENDERABLE_H_

namespace mroon {

class Renderable {
public:
	virtual ~Renderable() = 0;
	virtual void render(void) = 0;

};

} /* namespace mroon */
#endif /* RENDERABLE_H_ */
