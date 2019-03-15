#define HITBOX_H
#ifndef HITBOX_H

struct Point {
	float x;
	float y;
};

class Hitbox {

	Point pos;
	int width, height;

public:

	Hitbox()=default;
	Hitbox(Point pos, int width, int height);
	Point get_pos();
	int get_width();
	int get_height();

};

#endif