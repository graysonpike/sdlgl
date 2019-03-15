#include "hitbox.h"

Hitbox::Hitbox(Point pos, int width, int height) :
	pos(pos), width(width), height(height) {}

Point Hitbox::get_pos() {
	return pos;
}

int Hitbox::get_width() {
	return width;
}

int Hitbox::get_height() {
	return height;
}
