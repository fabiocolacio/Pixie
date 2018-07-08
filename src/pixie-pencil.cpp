#include <cmath>
#include <iostream>

#include "pixie-rect.hpp"
#include "pixie-session.hpp"

#include "pixie-pencil.hpp"

using namespace Cairo;
using namespace Pixie;

Pencil::Pencil(int size, Tip tip) :
    size(size),
    tip(tip)
{

}

void Pencil::activate(GdkEvent *event, Session &session)
{

}

void Pencil::draw_cursor(const RefPtr<Context> &cr, Session &session)
{
    float zoom_factor = session.get_zoom_factor();
    RectF sprite_bounds = session.get_sprite_bounds();
    RectF pixel_bounds = session.get_selected_pixel_bounds();
    Coord pixel = session.get_selected_pixel_coord();

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

