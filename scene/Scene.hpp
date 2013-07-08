/*
 * Scene.h
 *
 *  Created on: 11 Dec 2012
 *      Author: duncanm
 */

#ifndef SCENE_HPP_
#define SCENE_HPP_

#include "../renderables/MixedMesh.hpp"
#include "../renderables/Quad.hpp"
#include "../renderables/Tri.hpp"

namespace mroon {

typedef struct {
	Vector3 location;
	Vector3 normal;
	Colour colour;
} Vertex;


class Scene {

public:
	Scene();
	virtual ~Scene();

	void registerMesh(MixedMesh *mesh);
	void render(void);

private:
	int triCount;
	float *triData;
	int quadCount;
	float *quadData;
};

} /* namespace mroon */
#endif /* SCENE_H_ */
