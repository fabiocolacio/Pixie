#include <gdkmm/general.h>

#include <iostream>

#include "pixie-sprite-editor.hpp"

using namespace Pixie;

SpriteEditor::SpriteEditor(Sprite &sprite, bool read_only) :
    sprite(sprite),
    read_only(read_only)
{
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

    cr->save();
    cr->scale(zoom_factor, zoom_factor);

    for (auto layer : layers) {
        Gdk::Cairo::set_source_pixbuf(cr, layer.get_pixbuf(),
            image_bounds.left() / zoom_factor,
            image_bounds.top() / zoom_factor);
        auto pattern = cr->get_source();
        cairo_pattern_set_filter(pattern->cobj(), CAIRO_FILTER_NEAREST);
        cr->paint();

        std::cout << "Drew a thing!" << std::endl;
    }

    cr->restore();

    return false;
}
