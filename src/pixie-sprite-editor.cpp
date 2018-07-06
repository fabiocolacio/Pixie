#include <gdkmm/general.h>

#include <iostream>

#include "pixie-coord.hpp"

#include "pixie-sprite-editor.hpp"

using namespace Pixie;

SpriteEditor::SpriteEditor(Sprite &sprite, bool read_only) :
    sprite(sprite),
    read_only(read_only)
{
    current_tool = &pencil;

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

RectF SpriteEditor::get_sprite_bounds() const
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

RectF SpriteEditor::get_selected_pixel_bounds() const
{
    RectF sprite_bounds = get_sprite_bounds();
    Coord pixel = get_selected_pixel_coord();

    return (pixel.x >= 0 && pixel.y >= 0)
        ? RectF(
            sprite_bounds.left() + pixel.x * zoom_factor,
            sprite_bounds.top() + pixel.y * zoom_factor,
            zoom_factor,
            zoom_factor)
        : RectF(CoordF(-1, -1), CoordF(-1, -1));
}

Coord SpriteEditor::get_selected_pixel_coord() const
{
    RectF sprite_bounds = get_sprite_bounds();
    return (sprite_bounds.contains(cursor_coord))
        ? (cursor_coord - sprite_bounds.tl) / zoom_factor
        : Coord(-1, -1);
}

Coord SpriteEditor::get_cursor_coord() const
{
    return cursor_coord;
}

bool SpriteEditor::get_read_only() const
{
    return read_only;
}

void SpriteEditor::set_read_only(bool state)
{
    read_only = state;
}

float SpriteEditor::get_zoom_factor() const
{
    return zoom_factor;
}

void SpriteEditor::set_zoom_factor(float zoom_factor)
{
    this->zoom_factor = zoom_factor;
}

bool SpriteEditor::get_show_grid() const
{
    return show_grid;
}

void SpriteEditor::set_show_grid(bool show_grid)
{
    this->show_grid = show_grid;
}

bool SpriteEditor::on_draw(const Cairo::RefPtr<Cairo::Context> &cr)
{
    RectF image_bounds = get_sprite_bounds();    
    auto layers = sprite.get_layers();

    // Render Layers //
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

    // Draw Cursor //
    if (current_tool != nullptr) {
        current_tool->draw_cursor(cr, *this);
    }

    // Render Grid //
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
            cursor_coord = Coord(
                event->motion.x,
                event->motion.y);
            
            std::cout << "Selected pixel: " << get_selected_pixel_coord() << std::endl;

            break;
        }

        default: break;
    }

    queue_draw();

    return false;
}

