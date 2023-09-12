#include "physical_entity.h"

PhysicalEntity::PhysicalEntity(Scene *scene, float x, float y, int w, int h)
    : Entity(scene), x(x), y(y), w(w), h(h) {}

float PhysicalEntity::get_center_x() { return x + w / 2; }

float PhysicalEntity::get_center_y() { return y + h / 2; }

void PhysicalEntity::wrap_bounds() {
    int screen_w = scene->get_graphics()->get_width();
    int screen_h = scene->get_graphics()->get_height();

    if (this->get_center_x() < 0) {
        x = screen_w - w / 2;
    } else if (this->get_center_x() > screen_w) {
        x = 0 - w / 2;
    }
    if (this->get_center_y() < 0) {
        y = screen_h - h / 2;
    } else if (this->get_center_y() > screen_h) {
        y = 0 - h / 2;
    }
}

void PhysicalEntity::clamp() {
    int screen_w = scene->get_graphics()->get_width();
    int screen_h = scene->get_graphics()->get_height();
    if (x < 0) {
        x = 0;
    }
    if (y < 0) {
        y = 0;
    }
    if (x + w > screen_w) {
        x = screen_w - w;
    }
    if (y + h > screen_h) {
        y = screen_h - h;
    }
}

std::pair<int, int> PhysicalEntity::get_position() {
    return std::pair<int, int>(x, y);
}

std::pair<int, int> PhysicalEntity::get_size() {
    return std::pair<int, int>(x, y);
}
