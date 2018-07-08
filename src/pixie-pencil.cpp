#include <gtkmm/toolitem.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/spinbutton.h>

#include <cmath>
#include <iostream>

#include "pixie-rect.hpp"
#include "pixie-session.hpp"

#include "pixie-pencil.hpp"

using namespace Cairo;
using namespace Pixie;

void Pencil::activate(GdkEvent *event, Session &session)
{

}

void Pencil::draw_cursor(const RefPtr<Context> &cr, Session &session)
{
    float zoom_factor = session.get_zoom_factor();
    RectF sprite_bounds = session.get_sprite_bounds();
    RectF pixel_bounds = session.get_selected_pixel_bounds();
    Coord pixel = session.get_selected_pixel_coord();
    Tip tip = session.get_tip();
    int size = session.get_size();

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

/*
Gtk::Toolbar *Pencil::get_toolbar()
{
    Gtk::Toolbar *toolbar = new Gtk::Toolbar;
    Gtk::ToolItem *item = nullptr;

    // Size SpinButton //
    item = Gtk::manage(new Gtk::ToolItem);
    auto adj = Gtk::Adjustment::create(
        size, // value
        1.0,  // lower bound
        50.0, // upper bound
        1.0,  // step increment
        5.0,  // page increment
        0.0); // page size
    auto spin_button = Gtk::manage(new Gtk::SpinButton(adj));
    item->set_tooltip_text("size");
    item->add(*spin_button);
    toolbar->append(*item);

    return toolbar;
}
*/

