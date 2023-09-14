#ifndef PLAYER_H
#define PLAYER_H

#include "../../game/physical_entity.h"
#include "../../game/scene.h"
#include "../../graphics/sprite.h"
#include "../../graphics/texture.h"

class Player : public PhysicalEntity {
    enum { UP, DOWN, LEFT, RIGHT, STANDING } dir;
    Sprite sprites[4];
    Texture standing_texture;

   public:
    Player(const std::shared_ptr<Scene>& scene, float x, float y);
    void update() override;
    void render() override;
};

#endif