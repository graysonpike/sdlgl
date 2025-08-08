#ifndef PLAYER_H
#define PLAYER_H

#include <sdlgl/game/physical_entity.h>
#include <sdlgl/graphics/character.h>

class Player : public PhysicalEntity {
   private:
    Character character;
    enum Direction { UP, DOWN, LEFT, RIGHT, STANDING } current_direction;
    bool is_moving;
    float speed;

    void handle_input();
    void update_facing();
    void update_animation();

   public:
    Player(const std::shared_ptr<Scene>& scene, int x, int y);
    void update() override;
    void render() override;
};

#endif
