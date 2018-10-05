#ifndef PHYSICAL_ENTITY_H
#define PHYSICAL_ENTITY_H

#include "entity.h"

class PhysicalEntity : public Entity {

protected:

	float x, y;
	int w, h;
	void wrap_bounds();
	float get_center_x();
	float get_center_y();

public:

	PhysicalEntity(float x, float y, int w, int h);

};

#endif