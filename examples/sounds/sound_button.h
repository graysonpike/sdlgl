#include <sdlgl/audio/sound.h>
#include <sdlgl/game/physical_entity.h>
#include <sdlgl/game/scene.h>

class SoundButton : public PhysicalEntity {
    SDL_Color color;
    SDL_Color active_color;
    Sound sound;
    static SDL_Color get_lighter_color(SDL_Color color);

   public:
    SoundButton(const std::shared_ptr<Scene>& scene, int x, int y, int width,
                int height, SDL_Color color, const std::string& filename);
    void render();
    void update();
};