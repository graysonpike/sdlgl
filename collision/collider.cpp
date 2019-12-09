#include "collider.h"


// Returns the dot product of a given vector
float dot(SDL_Point a, SDL_Point b) {
	return a.x * b.x + a.y * b.y;
}

// Returns the magnitude of a given vector
float mag(float x, float y) {
	return pow(x * x + y * y, 0.5);
}

// Returns a scalar value that represents the position of a given point as
// projected along a given axis
float project_point(SDL_Point point, SDL_Point axis) {
	float multiplier = dot(point, axis) / dot(axis, axis);
	SDL_Point projected_point;
	projected_point.x = axis.x * multiplier;
	projected_point.y = axis.y * multiplier;
	return dot(axis, projected_point);
}

// Determine minimum and maxiumum scalar values from all corners
// on a given axis
void set_min_max(Hitbox* h, SDL_Point axis, float *min, float *max) {

	float smallest, biggest;

	smallest = biggest = project_point(h->get_tl(), axis);

	float n = project_point(h->get_tr(), axis);
	if(n > biggest) { biggest = n; }
	if(n < smallest) { smallest = n; }

	n = project_point(h->get_bl(), axis);
	if(n > biggest) { biggest = n; }
	if(n < smallest) { smallest = n; }

	n = project_point(h->get_br(), axis);
	if(n > biggest) { biggest = n; }
	if(n < smallest) { smallest = n; }

	*min = smallest;
	*max = biggest;

}

// Return true if two given hitboxes are overlapping as
// projected on a given axis
bool test_axis(Hitbox *h1, Hitbox *h2, SDL_Point axis) {

	float h1_min, h1_max, h2_min, h2_max;

	set_min_max(h1, axis, &h1_min, &h1_max);
	set_min_max(h2, axis, &h2_min, &h2_max);

	return (h2_min >= h1_min && h2_min <= h1_max) || (h2_max >= h1_min && h2_min <= h1_max);

}

// Returns true if two hitboxes are overlapping
bool check_hitboxes(Hitbox *h1, Hitbox *h2) {

	// Check by radius method to avoid expensive Separating Axis Method when possible
	// Calculate distance of each center
	float center_distance = pow(pow(h1->get_center_x() - h2->get_center_x(), 2.0f) + pow(h1->get_center_y() - h2->get_center_y(), 2.0f), 0.5f);
	// Add radii from both hitboxes
	float total_radii = h1->get_radius() + h2->get_radius();
	if(total_radii > center_distance) {

		// Radius method is inconclusive, measure with Separating Axis Theorem instead
		// https://www.gamedev.net/resources/_/technical/game-programming/2d-rotated-rectangle-collision-r2604
		SDL_Point axis1, axis2, axis3, axis4;

		axis1.x = h1->get_tr().x - h1->get_tl().x;
		axis1.y = h1->get_tr().y - h1->get_tl().y;
		axis2.x = h1->get_tr().x - h1->get_br().x;
		axis2.y = h1->get_tr().y - h1->get_br().y;
		axis3.x = h2->get_tl().x - h2->get_bl().x;
		axis3.y = h2->get_tl().y - h2->get_bl().y;
		axis4.x = h2->get_tl().x - h2->get_tr().x;
		axis4.y = h2->get_tl().y - h2->get_tr().y;

		if(!test_axis(h1, h2, axis1)) { return false; }
		if(!test_axis(h1, h2, axis2)) { return false; }
		if(!test_axis(h1, h2, axis3)) { return false; }
		if(!test_axis(h1, h2, axis4)) { return false; }

		return true;
	}

	return false;

}

void Collider::add_hitbox(Hitbox *hitbox, Entity *entity, int type, std::vector<int> targets, std::function<void(Entity*, int)> callback) {
	HitboxInfo info;
	info.hitbox = hitbox;
	info.entity = entity;
	info.type = type;
	info.targets = targets;
	info.callback = callback;
	hitboxes.push_back(info);
}

void Collider::check_collisions() {
	for (int i = 0; i < (int)hitboxes.size() - 1; i++) {
		for (int j = i+1; j < (int)hitboxes.size(); j++) {
			for (int k = 0; k < (int)hitboxes[i].targets.size(); k++) {
				if (hitboxes[j].type == hitboxes[i].targets[k]) {
					if (check_hitboxes(hitboxes[i].hitbox, hitboxes[j].hitbox)) {
						hitboxes[i].callback(hitboxes[j].entity, hitboxes[j].type);
						for (int l = 0; l < (int)hitboxes[j].targets.size(); l++) {
							if (hitboxes[i].type == hitboxes[j].targets[l]) {
								hitboxes[j].callback(hitboxes[i].entity, hitboxes[i].type);
							}
						}
					}
				}
			}
		}
	}
}