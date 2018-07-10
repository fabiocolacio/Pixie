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
    float zoom_factor = session.get_zoom_factor();
    RectF sprite_bounds = session.get_sprite_bounds();
    RectF pixel_bounds = session.get_selected_pixel_bounds();
    Coord pixel = session.get_selected_pixel_coord();
    Tip tip = session.get_tip();
    int size = session.get_size();
    Layer layer = session.get_active_layer();

    switch (tip) {
        case SquareTip: {
            
            break;
        }

        default: break;
    }
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
        case SquareTip: {
            cr->set_source_rgba(0.0, 0.0, 0.0, 1.0);
            cr->set_line_width(0.5);
            cr->rectangle(
                pixel_bounds.x() - std::floor(size / 2) * zoom_factor,
                pixel_bounds.y() - std::floor(size / 2) * zoom_factor,
                size * zoom_factor, size * zoom_factor);
            cr->stroke();
            break;
        }

        case DiamondTip: {
            cr->set_source_rgba(0.0, 0.0, 0.0, 1.0);
            cr->set_line_width(0.5);

            for (int r = 0; r < size; r++) {
                RectF rect(
                        pixel_bounds.left() - r * zoom_factor,
                        pixel_bounds.top() - (size - r - 1) * zoom_factor,
                        (1 + (r * 2)) * zoom_factor,
                        (1 + (size - r - 1) * 2) * zoom_factor);
                
                cr->move_to(rect.left(), rect.top());
                cr->rel_line_to(0, zoom_factor);
                cr->move_to(rect.left(), rect.top());
                cr->rel_line_to(zoom_factor, 0);

                cr->move_to(rect.right(), rect.top());
                cr->rel_line_to(0, zoom_factor);
                cr->move_to(rect.right(), rect.top());
                cr->rel_line_to(-zoom_factor, 0);
                
                cr->move_to(rect.left(), rect.bottom());
                cr->rel_line_to(0, -zoom_factor);
                cr->move_to(rect.left(), rect.bottom());
                cr->rel_line_to(zoom_factor, 0);

                cr->move_to(rect.right(), rect.bottom());
                cr->rel_line_to(0, -zoom_factor);
                cr->move_to(rect.right(), rect.bottom());
                cr->rel_line_to(-zoom_factor, 0);
            }

            cr->stroke();
            break;
        }

        default: break;
    }
}

