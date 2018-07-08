#ifndef __PIXIE_SESSION_HPP__
#define __PIXIE_SESSION_HPP__

#include <gtkmm/box.h>
#include <gtkmm/drawingarea.h>

#include "pixie-tool.hpp"
#include "pixie-rectf.hpp"
#include "pixie-coord.hpp"
#include "pixie-document.hpp"

namespace Pixie {

enum Tip { Square, Diamond };
enum Mode { Sprite, Animation, Tile };

class Session : public Gtk::Box {
public:
    Session(const std::string &filename);
    Session(Document&& document);
    ~Session();

    std::string get_title() const;

    float get_zoom_factor() const;
    void set_zoom_factor(float factor);
    void zoom_in();
    void zoom_out();

    bool get_show_grid() const;
    void set_show_grid(bool state);
    bool toggle_show_grid();

    Tip get_tip() const;
    int get_size() const;

    Mode get_mode() const;

    RectF get_sprite_bounds() const;
    RectF get_selected_pixel_bounds() const;
    Coord get_selected_pixel_coord() const;

private:
    void init();

    void update_editor_size();
    bool editor_draw(const Cairo::RefPtr<Cairo::Context> &cr);
    bool editor_event(GdkEvent *event);

    Document document;
    std::string title = "Untitled Document";

    Tool *tool = nullptr;
    std::vector<Tool*> tools;

    Mode mode = Sprite;
    int sprite_index = 0;
    int layer_index = 0;

    Coord cursor_coord = Coord(-1, -1);
    Coord selected_pixel = Coord(-1, -1);

    Tip tip = Square;
    int size = 1;

    float zoom_factor = 10.0;
    float min_padding = 100.0;
    bool show_grid = true;

    Gtk::DrawingArea editor;
};

}

#endif
