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

class Scene {

public:
	Scene();
	virtual ~Scene();

	void registerMesh(MixedMesh *mesh);
	void render(void);

private:
	int triCount;
	Tri *tris;
	int quadCount;
	Quad *quads;
};

} /* namespace mroon */
#endif /* SCENE_H_ */
