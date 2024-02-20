
#include "hitbox.h"

#include <algorithm>

#include "../graphics/graphics.h"

// Size of rects drawn on corners by render_corners()
// Should be an even integer
#define POINT_SIZE 4
// Color of rects drawn on corners by render_corners()
#define POINT_R 255
#define POINT_G 0
#define POINT_B 0
#define POINT_A 255

// HELPER FUNCTIONS

// Rotate point around origin by a given angle
void rotate_point(int *x, int *y, float angle) {
    int old_x = *x;
    int old_y = *y;
    *x = old_x * cos(angle) - old_y * sin(angle);
    *y = old_x * sin(angle) + old_y * cos(angle);
}

Hitbox::Hitbox() {}

Hitbox::Hitbox(float x_offset, float y_offset, int w, int h) {
    this->x_offset = x_offset;
    this->y_offset = y_offset;
    this->w = w;
    this->h = h;
    radius = pow(2 * pow(std::max(w, h), 2), 0.5f);
}

// Given new coordinates and angle, update hitbox corners
void Hitbox::update_pos(float x, float y, float angle) {
    // Apply offsets
    this->x = x + x_offset;
    this->y = y + y_offset;

    // Set angle
    this->angle = angle;

    // Calculate center point
    float cx = this->x + w / 2.0f;
    float cy = this->y + h / 2.0f;

    // Method for rotating corners:
    // 1. Translate corner relative to center of rectangle (center is the
    // origin)
    // 2. Rotate about the origin
    // 3. Translate back to center of rectangle

    // Top Left Corner
    tl.x = -w / 2;
    tl.y = -h / 2;
    rotate_point(&tl.x, &tl.y, angle);
    tl.x += cx;
    tl.y += cy;

    // Top Right Corner
    tr.x = w / 2;
    tr.y = -h / 2;
    rotate_point(&tr.x, &tr.y, angle);
    tr.x += cx;
    tr.y += cy;

    // Bottom Left Corner
    bl.x = -w / 2;
    bl.y = h / 2;
    rotate_point(&bl.x, &bl.y, angle);
    bl.x += cx;
    bl.y += cy;

    // Bottom Right Corner
    br.x = w / 2;
    br.y = h / 2;
    rotate_point(&br.x, &br.y, angle);
    br.x += cx;
    br.y += cy;
}

// Debug method to draw corners
void Hitbox::render_corners() {
    const std::shared_ptr<SDL_Renderer> &renderer =
        Graphics::get_instance().get_renderer();

    // Set draw color
    SDL_SetRenderDrawColor(renderer.get(), POINT_R, POINT_G, POINT_B, POINT_A);

    // Create rectangles over each corner
    SDL_Rect tl_rect = {tl.x - POINT_SIZE / 2, tl.y - POINT_SIZE / 2,
                        POINT_SIZE, POINT_SIZE};
    SDL_Rect tr_rect = {tr.x - POINT_SIZE / 2, tr.y - POINT_SIZE / 2,
                        POINT_SIZE, POINT_SIZE};
    SDL_Rect bl_rect = {bl.x - POINT_SIZE / 2, bl.y - POINT_SIZE / 2,
                        POINT_SIZE, POINT_SIZE};
    SDL_Rect br_rect = {br.x - POINT_SIZE / 2, br.y - POINT_SIZE / 2,
                        POINT_SIZE, POINT_SIZE};

    // Draw rectangles
    SDL_RenderFillRect(renderer.get(), &tl_rect);
    SDL_RenderFillRect(renderer.get(), &tr_rect);
    SDL_RenderFillRect(renderer.get(), &bl_rect);
    SDL_RenderFillRect(renderer.get(), &br_rect);
}

int Hitbox::get_center_x() { return x + w / 2.0f; }

int Hitbox::get_center_y() { return y + h / 2.0f; }

float Hitbox::get_radius() { return radius; }

int Hitbox::get_radius_approx() { return w + h; }

bool Hitbox::check_point(SDL_Point point) {
    return (point.x >= tl.x && point.x <= tr.x) &&
           (point.y >= tl.y && point.y <= bl.y);
}

SDL_Point Hitbox::get_tl() { return tl; }

SDL_Point Hitbox::get_tr() { return tr; }

SDL_Point Hitbox::get_bl() { return bl; }

SDL_Point Hitbox::get_br() { return br; }
