#ifndef __PIXIE_SPRITE_EDITOR_HPP__
#define __PIXIE_SPRITE_EDITOR_HPP__

#include <gtkmm/drawingarea.h>

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
    Sprite &sprite;

    double zoom_factor = 10.0;
    bool read_only;
};

}

#endif
