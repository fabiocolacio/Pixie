#include <gdkmm/general.h>

#include <iostream>

#include "pixie-sprite-editor.hpp"

using namespace Pixie;

SpriteEditor::SpriteEditor(Sprite &sprite, bool read_only) :
    sprite(sprite),
    read_only(read_only)
{
    add_events(
        Gdk::KEY_PRESS_MASK |
        Gdk::BUTTON_PRESS_MASK |
        Gdk::BUTTON_RELEASE_MASK |
        Gdk::POINTER_MOTION_MASK);
    update_size();
}

void SpriteEditor::update_size()
{
    set_size_request(
        (zoom_factor * sprite.width()) + (2 * min_padding),
        (zoom_factor * sprite.height()) + (2 * min_padding));
}

RectF SpriteEditor::get_image_bounds() const
{
    int min_width, min_height;
    int width = get_allocated_width();
    int height = get_allocated_height();
    get_size_request(min_width, min_height);
    float swidth = sprite.width() * zoom_factor;
    float sheight = sprite.height() * zoom_factor;

    float x = (width > min_width)
        ? (width - swidth) / 2
        : min_padding;
    float y = (height > min_height)
        ? (height - sheight) / 2
        : min_padding;

    return RectF(x, y, swidth, sheight);
}

bool SpriteEditor::get_read_only() const
{
    return read_only;
}

void SpriteEditor::set_read_only(bool state)
{
    read_only = state;
}

bool SpriteEditor::on_draw(const Cairo::RefPtr<Cairo::Context> &cr)
{
    RectF image_bounds = get_image_bounds();    
    auto layers = sprite.get_layers();

    // Render Layers
    cr->save();
    cr->scale(zoom_factor, zoom_factor);
    for (auto layer : layers) {
        Gdk::Cairo::set_source_pixbuf(cr, layer.get_pixbuf(),
            image_bounds.left() / zoom_factor,
            image_bounds.top() / zoom_factor);
        auto pattern = cr->get_source();
        cairo_pattern_set_filter(pattern->cobj(), CAIRO_FILTER_NEAREST);
        cr->paint();
    }
    cr->restore();

    // Render Grid
    if (show_grid) {
        cr->set_source_rgba(0.0, 0.0, 0.0, 1.0);
        cr->set_line_width(0.5);
        for (int x = 0; x < sprite.width() + 1; x++) {
            float x_scaled = image_bounds.left() + (x * zoom_factor);
            cr->move_to(x_scaled, image_bounds.top());
            cr->line_to(x_scaled, image_bounds.bottom());
        }
        for (int y = 0; y < sprite.height() + 1; y++) {
            float y_scaled = image_bounds.top() + (y * zoom_factor);
            cr->move_to(image_bounds.left(), y_scaled);
            cr->line_to(image_bounds.right(), y_scaled);
        }
        cr->stroke();
    }

    return false;
}

bool SpriteEditor::on_event(GdkEvent *event)
{
    switch (event->type) {
        case GDK_KEY_PRESS: {
            std::cout << "key press!" << std::endl;
            break;
        }

        case GDK_BUTTON_PRESS: {
            std::cout << "button press!" << std::endl;
            break;
        }

        case GDK_BUTTON_RELEASE: {
            std::cout << "button release!" << std::endl;
            break;
        }

        case GDK_MOTION_NOTIFY: {
            std::cout << "motion notify!" << std::endl;
            break;
        }

        default: break;
    }

    return false;
}

