#ifndef __PIXIE_SPRITE_EDITOR_HPP__
#define __PIXIE_SPRITE_EDITOR_HPP__

#include <gtkmm/drawingarea.h>

#include "pixie-rectf.hpp"
#include "pixie-sprite.hpp"

namespace Pixie {

class SpriteEditor : public Gtk::DrawingArea {
public:
    SpriteEditor(Sprite &sprite, bool read_only = false);

    bool get_read_only() const;
    void set_read_only(bool state);

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;

private:
    void update_size();
    RectF get_image_bounds() const;

    Sprite &sprite;

    bool read_only;

    float zoom_factor = 10.0;
    float min_padding = 100.0;
    bool show_grid = true;
};

}

#endif
