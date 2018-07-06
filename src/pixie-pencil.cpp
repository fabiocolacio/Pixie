#include <cmath>
#include <iostream>

#include "pixie-rect.hpp"
#include "pixie-sprite-editor.hpp"

#include "pixie-pencil.hpp"

using namespace Cairo;
using namespace Pixie;

Pencil::Pencil(int size, Tip tip) :
    size(size),
    tip(tip)
{

}

void Pencil::activate(GdkEvent *event, SpriteEditor &editor)
{

}

void Pencil::draw_cursor(const RefPtr<Context> &cr, SpriteEditor &editor)
{
    float zoom_factor = editor.get_zoom_factor();
    RectF sprite_bounds = editor.get_sprite_bounds();
    RectF pixel_bounds = editor.get_selected_pixel_bounds();
    Coord pixel = editor.get_selected_pixel_coord();

    switch (tip) {
        case Square: {
            cr->set_source_rgba(0.0, 0.0, 0.0, 1.0);
            cr->set_line_width(0.5);
            cr->rectangle(pixel_bounds.x(), pixel_bounds.y(), pixel_bounds.width(), pixel_bounds.height());
            cr->stroke();
            break;
        }

        case Diamond: {
            cr->set_source_rgba(0.0, 0.0, 0.0, 1.0);
            cr->set_line_width(0.5);
            cr->rectangle(pixel_bounds.x(), pixel_bounds.y(), pixel_bounds.width(), pixel_bounds.height());
            cr->stroke();
            break;
        }

        default: break;
    }
}

Gtk::Toolbar *Pencil::get_toolbar()
{
    return nullptr;
}

int Pencil::get_size() const
{
    return size;
}

void Pencil::set_size(int size)
{
    this->size = size;
}

Pencil::Tip Pencil::get_tip() const
{
    return tip;
}

void Pencil::set_tip(Tip tip)
{
    this->tip = tip;
}

