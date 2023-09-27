#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <vector>

#include "fps_counter.h"
#include "resources.h"

class Graphics {
    // Width and height of the window in px
    int width, height;

    bool debug_visuals_enabled;

    FPSCounter fps_counter;
    std::shared_ptr<SDL_Window> window;
    std::shared_ptr<SDL_Renderer> renderer;
    std::shared_ptr<SDL_Surface> capture_surface;

    bool init_sdl(std::string window_title);
    void init_capture_surface();

    static Graphics* instance;
    Graphics(int width, int height, std::string window_title);

   public:
    Graphics(const Graphics&) = delete;
    Graphics& operator=(const Graphics&) = delete;
    // Static method to initialize the Graphics system, must be called before
    // get_instance().
    static void initialize(int width, int height,
                           const std::string& window_title = "SDLGL Game");
    // Static method to provide global point of access to the instance.
    static Graphics& get_instance();
    void clear_screen(SDL_Color color = (SDL_Color){0, 0, 0, 255});
    void present_renderer(float delta);
    void toggle_debug_visuals();
    void set_debug_visuals(bool enabled);
    int get_width() const;
    int get_height() const;
    bool get_debug_visuals_enabled() const;
    std::shared_ptr<SDL_Renderer> get_renderer() const;
    float get_fps() const;
    void capture_bmp(std::string filename);
    static std::shared_ptr<SDL_Texture> load_font_texture(
        const std::string& font, const std::string& text, SDL_Color text_color);
    ~Graphics();
};

#endif