#ifndef COLLIDER_H
#define COLLIDER_H

#include <vector>
#include <functional>
#include "hitbox.h"
#include "../game/entity.h"

class Entity;

class Collider {

	struct HitboxInfo {
		Hitbox *hitbox;
		Entity *entity;
		int type;
		const int *targets;
		int num_targets;
		std::function<void(Entity*, int)> callback;
	};

	std::vector<HitboxInfo> hitboxes;

public:

	void add_hitbox(Hitbox *hitbox, Entity *entity, int type, const int *targets, int num_targets, std::function<void(Entity*, int)> callback);
	void check_collisions();

};

#endif