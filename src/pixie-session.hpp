#ifndef __PIXIE_SESSION_HPP__
#define __PIXIE_SESSION_HPP__

#include <gtkmm/box.h>
#include <gtkmm/drawingarea.h>

#include "pixie-rectf.hpp"
#include "pixie-coord.hpp"
#include "pixie-document.hpp"

namespace Pixie {

class Session : public Gtk::Box {
public:
    enum Mode { Sprite, Animation, Tile };

    Session(const std::string &filename);
    Session(Document&& document);

    std::string get_title() const;

private:
    void init_ui();

    RectF get_sprite_bounds() const;
    RectF get_selected_pixel_bounds() const;
    Coord get_selected_pixel_coord() const;
    void update_editor_size();
    bool editor_draw(const Cairo::RefPtr<Cairo::Context> &cr);
    bool editor_event(GdkEvent *event);

    Document document;
    std::string title = "Untitled Document";

    Mode mode = Sprite;
    int sprite_index = 0;
    int layer_index = 0;

    Coord cursor_coord = Coord(-1, -1);
    Coord selected_pixel = Coord(-1, -1);

    float zoom_factor = 10.0;
    float min_padding = 100.0;
    bool show_grid = true;

    Gtk::DrawingArea editor;
};

}

#endif
