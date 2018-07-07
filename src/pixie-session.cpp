#include <gdkmm/general.h>

#include "pixie-session.hpp"

using namespace Cairo;
using namespace Pixie;

Session::Session(const std::string &filename) :
    document(Document(filename))
{
    init_ui();
}

Session::Session(Document&& document) :
    document(std::move(document))
{
    init_ui();
}

void Session::update_editor_size()
{
    editor.set_size_request(
        (zoom_factor * document.width()) + (2 * min_padding),
        (zoom_factor * document.height()) + (2 * min_padding));
}

RectF Session::get_sprite_bounds() const
{
    int min_width, min_height;
    get_size_request(min_width, min_height);
    int width = editor.get_allocated_width();
    int height = editor.get_allocated_height();
    float swidth = document.width() * zoom_factor;
    float sheight = document.height() * zoom_factor;
    
    float x = (width > min_width)
        ? (width - swidth) / 2
        : min_padding;
    float y = (height > min_height)
        ? (height - sheight) / 2
        : min_padding;

    return RectF(x, y, swidth, sheight);
}

RectF Session::get_selected_pixel_bounds() const
{
    RectF sprite_bounds = get_sprite_bounds();
    Coord pixel = get_selected_pixel_coord();

    return (pixel.x >= 0 && pixel.y >= 0)
        ? RectF(
            sprite_bounds.left() + pixel.x * zoom_factor,
            sprite_bounds.top() + pixel.y * zoom_factor,
            zoom_factor, zoom_factor)
        : RectF(CoordF(-1, -1), CoordF(-1, -1));
}

Coord Session::get_selected_pixel_coord() const
{
    RectF sprite_bounds = get_sprite_bounds();
    return (sprite_bounds.contains(cursor_coord))
        ? (cursor_coord - sprite_bounds.tl) / zoom_factor
        : Coord(-1, -1);
}

bool Session::editor_draw(const RefPtr<Context> &cr)
{
    RectF image_bounds = get_sprite_bounds();
    auto layers = document.sprites[sprite_index].get_layers();

    // Render Layers //
    cr->save();
    cr->scale(zoom_factor, zoom_factor);
    for (size_t i = layer_index; i < layers.size(); i++) {
        auto layer = layers[i];
        Gdk::Cairo::set_source_pixbuf(cr,
            layer.get_pixbuf(),
            image_bounds.left() / zoom_factor,
            image_bounds.top() / zoom_factor);
        auto pattern = cr->get_source();
        cairo_pattern_set_filter(pattern->cobj(), CAIRO_FILTER_NEAREST);
        cr->paint();
    }
    cr->restore();

    // Render Grid //
    if (show_grid) {
        cr->set_source_rgba(0.0, 0.0, 0.0, 1.0);
        cr->set_line_width(0.5);
        for (int x = 0; x < document.width() + 1; x++) {
            float x_scaled = image_bounds.left() + (x * zoom_factor);
            cr->move_to(x_scaled, image_bounds.top());
            cr->line_to(x_scaled, image_bounds.bottom());
        }
        for (int y = 0; y < document.height() + 1; y++) {
            float y_scaled = image_bounds.top() + (y * zoom_factor);
            cr->move_to(image_bounds.left(), y_scaled);
            cr->line_to(image_bounds.right(), y_scaled);
        }
        cr->stroke();
    }

    return false;
}

bool Session::editor_event(GdkEvent *event)
{
    switch (event->type) {
        case GDK_KEY_PRESS: {
            break;
        }

        case GDK_BUTTON_PRESS: {
            break;
        }

        case GDK_BUTTON_RELEASE: {
            break;
        }

        case GDK_MOTION_NOTIFY: {
            cursor_coord = Coord(
                event->motion.x,
                event->motion.y);
            break;
        }

        default: break;
    }

    editor.queue_draw();

    return false;
}

void Session::init_ui()
{
    update_editor_size();
    editor.add_events(
        Gdk::KEY_PRESS_MASK |
        Gdk::BUTTON_PRESS_MASK |
        Gdk::BUTTON_RELEASE_MASK |
        Gdk::POINTER_MOTION_MASK);
    editor.signal_event()
        .connect(sigc::mem_fun(*this, &Session::editor_event));
    editor.signal_draw()
        .connect(sigc::mem_fun(*this, &Session::editor_draw));
    pack_start(editor);

    title = document.file->get_basename();
}

std::string Session::get_title() const
{
    return title;
}
