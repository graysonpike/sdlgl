// SDLGL - Menu class implementation

#include "menu.h"

#include "../graphics/graphics.h"
#include "../graphics/text.h"
#include "../input/inputs.h"

Menu::Menu(const MenuBackground& background, const std::string& font_name)
    : background(background),
      selected_index(0),
      font_name(font_name),
      selector("> "),
      title(""),
      item_height(40),
      padding(32),
      title_spacing(24),
      content_width_tiles(5),
      content_height_tiles(3) {}

void Menu::set_title(const std::string& new_title) {
    title = new_title;
    calculate_dimensions();
}

void Menu::add_item(const std::string& label, std::function<void()> on_select) {
    items.emplace_back(label, on_select);
    calculate_dimensions();
}

void Menu::clear_items() {
    items.clear();
    selected_index = 0;
    calculate_dimensions();
}

void Menu::calculate_dimensions() {
    // Calculate the height needed based on number of items
    // Each item needs item_height pixels, plus padding top and bottom
    int total_content_height = (items.size() * item_height) + (padding * 2);

    // Add space for title if present
    if (!title.empty()) {
        total_content_height += item_height + title_spacing;
    }

    // Tile size is 64 (from the tileset dst_scale)
    int tile_size = 64;

    // Calculate tiles needed (round up)
    content_height_tiles = (total_content_height + tile_size - 1) / tile_size;
    if (content_height_tiles < 2) content_height_tiles = 2;

    // Width: use a reasonable default that fits menu text
    content_width_tiles = 6;
}

void Menu::move_up() {
    if (selected_index > 0) {
        selected_index--;
    } else {
        // Wrap to bottom
        selected_index = items.size() - 1;
    }
}

void Menu::move_down() {
    if (selected_index < static_cast<int>(items.size()) - 1) {
        selected_index++;
    } else {
        // Wrap to top
        selected_index = 0;
    }
}

void Menu::select() {
    if (selected_index >= 0 &&
        selected_index < static_cast<int>(items.size())) {
        if (items[selected_index].on_select) {
            items[selected_index].on_select();
        }
    }
}

bool Menu::handle_input() {
    Inputs& inputs = Inputs::get_instance();

    if (inputs.is_key_down_event(SDL_SCANCODE_UP) ||
        inputs.is_key_down_event(SDL_SCANCODE_W)) {
        move_up();
    }

    if (inputs.is_key_down_event(SDL_SCANCODE_DOWN) ||
        inputs.is_key_down_event(SDL_SCANCODE_S)) {
        move_down();
    }

    if (inputs.is_key_down_event(SDL_SCANCODE_RETURN) ||
        inputs.is_key_down_event(SDL_SCANCODE_SPACE)) {
        select();
        return true;
    }

    return false;
}

void Menu::render() {
    // Get screen dimensions for centering
    int screen_width = Graphics::get_instance().get_width();
    int screen_height = Graphics::get_instance().get_height();
    int tile_size = 64;

    // Calculate total size including borders
    int total_width = (content_width_tiles + 2) * tile_size;
    int total_height = (content_height_tiles + 2) * tile_size;

    // Calculate position to center on screen
    // The draw_background x,y is where the inner content starts (after border)
    int bg_x = (screen_width - total_width) / 2 + tile_size;
    int bg_y = (screen_height - total_height) / 2 + tile_size;

    // Draw the background
    background.draw_background(bg_x, bg_y, content_width_tiles,
                               content_height_tiles);

    // Calculate content area for text
    int content_y = bg_y + padding;
    int center_x = bg_x + (content_width_tiles * tile_size) / 2;

    // Draw title if present
    SDL_Color title_color = {30, 30, 80, 255};
    if (!title.empty()) {
        Text::draw_text_center_justified(center_x, content_y, title, font_name,
                                         title_color);
        content_y += item_height + title_spacing;
    }

    // Draw menu items
    SDL_Color text_color = {0, 0, 0, 255};
    SDL_Color selected_color = {50, 50, 150, 255};

    for (size_t i = 0; i < items.size(); i++) {
        int item_y = content_y + (i * item_height);

        std::string display_text;
        SDL_Color color;

        if (static_cast<int>(i) == selected_index) {
            display_text = selector + items[i].label;
            color = selected_color;
        } else {
            // Add spacing to align with selected items
            display_text = "  " + items[i].label;
            color = text_color;
        }

        // Center the text horizontally within the menu
        Text::draw_text_center_justified(center_x, item_y, display_text,
                                         font_name, color);
    }
}

const std::string& Menu::get_selected_label() const {
    static const std::string empty;
    if (selected_index >= 0 &&
        selected_index < static_cast<int>(items.size())) {
        return items[selected_index].label;
    }
    return empty;
}
