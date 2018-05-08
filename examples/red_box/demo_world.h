#ifndef DEMO_WORLD_H
#define DEMO_WORLD_H

#include "../../game/scene.h"

class DemoWorld : public Scene {

	float delta;

public:

	using Scene::Scene;
	void update(float delta);
	float get_delta();

};

#endif
