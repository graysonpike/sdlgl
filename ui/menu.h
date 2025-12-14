// SDLGL - Menu class
// A navigable menu with text options and a background

#ifndef SDLGL_MENU_H
#define SDLGL_MENU_H

#include <functional>
#include <string>
#include <vector>

#include "menu_background.h"

struct MenuItem {
    std::string label;
    std::function<void()> on_select;

    MenuItem(const std::string& label,
             std::function<void()> on_select = nullptr)
        : label(label), on_select(on_select) {}
};

class Menu {
   private:
    MenuBackground background;
    std::vector<MenuItem> items;
    int selected_index;
    std::string font_name;
    std::string selector;
    std::string title;
    int item_height;
    int padding;
    int title_spacing;  // Extra spacing between title and first item

    // Calculated dimensions
    int content_width_tiles;
    int content_height_tiles;

    void calculate_dimensions();

   public:
    Menu(const MenuBackground& background, const std::string& font_name);

    // Title
    void set_title(const std::string& title);
    const std::string& get_title() const { return title; }

    // Add menu items
    void add_item(const std::string& label,
                  std::function<void()> on_select = nullptr);
    void clear_items();

    // Navigation
    void move_up();
    void move_down();
    void select();  // Triggers the callback of the selected item

    // Handle input (returns true if an item was selected)
    bool handle_input();

    // Rendering
    void render();

    // Accessors
    int get_selected_index() const { return selected_index; }
    const std::string& get_selected_label() const;
    void set_selector(const std::string& selector) {
        this->selector = selector;
    }
    void set_item_height(int height) { item_height = height; }
    void set_padding(int padding) { this->padding = padding; }
    void set_title_spacing(int spacing) { title_spacing = spacing; }
};

#endif
