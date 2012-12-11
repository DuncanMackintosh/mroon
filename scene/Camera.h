/*
 * Camera.h
 *
 *  Created on: 11 Dec 2012
 *      Author: duncanm
 */

#ifndef CAMERA_H_
#define CAMERA_H_

namespace mroon {

class Camera {
public:
	Camera();
	virtual ~Camera();
	virtual void apply(void);
};

} /* namespace mroon */
#endif /* CAMERA_H_ */
