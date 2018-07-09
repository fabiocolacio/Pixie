#include <gdkmm/general.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/toolitem.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/separatortoolitem.h>

#include "pixie-pencil.hpp"
#include "pixie-session.hpp"

using namespace Cairo;
using namespace Pixie;

Session::Session(const std::string &filename) :
    Box(Gtk::ORIENTATION_VERTICAL),
    document(Document(filename))
{
    init();
}

Session::Session(Document&& document) :
    Box(Gtk::ORIENTATION_VERTICAL),
    document(std::move(document))
{
    init();
}

Session::~Session()
{
    for (Tool *t : tools) {
        delete t;
    }
}

void Session::init()
{
    // Tools //
    tools.push_back(new Pencil);

    // Toolbar //
    {
        Gtk::Toolbar *toolbar = Gtk::manage(new Gtk::Toolbar);
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
        spin_button->set_tooltip_text("size");
        item->add(*spin_button);
        item->show_all();
        toolbar->append(*item);

        // Tip Combobox //
        item = Gtk::manage(new Gtk::ToolItem);
        auto combo_box = Gtk::manage(new Gtk::ComboBoxText);
        combo_box->append("Square");
        combo_box->append("Diamond");
        combo_box->set_active(0);
        combo_box->set_tooltip_text("tip");
        item->add(*combo_box);
        item->show_all();
        toolbar->append(*item);
        
        item = Gtk::manage(new Gtk::SeparatorToolItem);
        item->show_all();
        toolbar->append(*item);

        // Mode ComboBox //
        item = Gtk::manage(new Gtk::ToolItem);
        combo_box = Gtk::manage(new Gtk::ComboBoxText);
        combo_box->append("Sprite Mode");
        combo_box->append("Animation Mode");
        combo_box->append("Tile Mode");
        combo_box->set_active(0);
        combo_box->set_tooltip_text("editor mode");
        item->add(*combo_box);
        item->show_all();
        toolbar->append(*item);
    
        toolbar->set_show_arrow(true);
        toolbar->show();
        pack_start(*toolbar, false, true);
    }

    // Editor //
    editor.set_can_focus(true);
    editor.set_focus_on_click(true);
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
    editor.show();

    // Scrolled Window //
    auto scroll = Gtk::manage(new Gtk::ScrolledWindow());
    scroll->add(editor);
    scroll->show();
    pack_start(*scroll);

    // Session //
    title = document.file->get_basename();
    editor.grab_focus();
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

    // Render Cursor
    if (tool != nullptr) {
        tool->draw_cursor(cr, *this);
    }

    return false;
}

bool Session::editor_event(GdkEvent *event)
{
    switch (event->type) {
        case GDK_KEY_PRESS: {
            switch (event->key.keyval) {
                default: break;
            }
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

std::string Session::get_title() const
{
    return title;
}

std::string Session::get_subtitle() const
{
    return document.file->get_parent()->get_path();
}

float Session::get_zoom_factor() const
{
    return zoom_factor;
}

void Session::set_zoom_factor(float factor)
{
    zoom_factor = factor;
    update_editor_size();
    editor.queue_draw();
}

void Session::zoom_in()
{
    zoom_factor *= 1.5;
    update_editor_size();
    editor.queue_draw();
}

// TODO: Actually make zoom to show the whole image
void Session::zoom_fit()
{
    zoom_factor = 10.0;
    update_editor_size();
    editor.queue_draw();
}

void Session::zoom_out()
{
    zoom_factor /= 1.5;
    update_editor_size();
    editor.queue_draw();
}

bool Session::get_show_grid() const
{
    return show_grid;
}

void Session::set_show_grid(bool state)
{
    show_grid = state;
    editor.queue_draw();
}

bool Session::toggle_show_grid()
{
    show_grid = !show_grid;
    editor.queue_draw();
    return show_grid;
}

Tip Session::get_tip() const
{
    return tip;
}

int Session::get_size() const
{
    return size;
}

Mode Session::get_mode() const
{
    return mode;
}


