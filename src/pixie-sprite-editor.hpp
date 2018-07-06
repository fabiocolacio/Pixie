#ifndef __PIXIE_SPRITE_EDITOR_HPP__
#define __PIXIE_SPRITE_EDITOR_HPP__

#include <gtkmm/drawingarea.h>

#include "pixie-tool.hpp"
#include "pixie-pencil.hpp"
#include "pixie-rectf.hpp"
#include "pixie-sprite.hpp"

namespace Pixie {

class SpriteEditor : public Gtk::DrawingArea {
public:
    SpriteEditor(Sprite &sprite, bool read_only = false);

    bool get_read_only() const;
    void set_read_only(bool state);

    float get_zoom_factor() const;
    void set_zoom_factor(float zoom_factor);

    bool get_show_grid() const;
    void set_show_grid(bool state);

    RectF get_sprite_bounds() const;
    RectF get_selected_pixel_bounds() const;
    Coord get_selected_pixel_coord() const;
    Coord get_cursor_coord() const;

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;
    bool on_event(GdkEvent *event) override;

private:
    void update_size();

    Sprite &sprite;

    Tool *current_tool;
    Pencil pencil;

    bool read_only;

    float zoom_factor = 10.0;
    float min_padding = 100.0;
    bool show_grid = false;

    Coord cursor_coord = Coord(-1, -1);
    Coord selected_pixel = Coord(-1, -1);
};

}

#endif
