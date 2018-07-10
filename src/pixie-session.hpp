#ifndef __PIXIE_SESSION_HPP__
#define __PIXIE_SESSION_HPP__

#include <gtkmm/box.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/comboboxtext.h>

#include "pixie-tool.hpp"
#include "pixie-rectf.hpp"
#include "pixie-coord.hpp"
#include "pixie-document.hpp"
#include "pixie-layer.hpp"
#include "pixie-sprite.hpp"

namespace Pixie {

enum Tip { SquareTip, DiamondTip, CircleTip, NTips };
enum Mode { SpriteMode, AnimationMode, TileMode };

class Session : public Gtk::Box {
public:
    Session(const std::string &filename);
    Session(Document&& document);
    ~Session();

    std::string get_title() const;
    std::string get_subtitle() const;

    float get_zoom_factor() const;
    void set_zoom_factor(float factor);
    void zoom_in();
    void zoom_fit();
    void zoom_out();

    bool get_show_grid() const;
    void set_show_grid(bool state);
    bool toggle_show_grid();

    Tip get_tip() const;
    void set_tip(Tip tip);

    int get_size() const;
    void set_size(int size);

    Mode get_mode() const;

    RectF get_sprite_bounds() const;
    RectF get_selected_pixel_bounds() const;
    Coord get_selected_pixel_coord() const;

    Pixie::Sprite &get_active_sprite();
    Pixie::Layer &get_active_layer();

private:
    void init();

    void update_editor_size();
    bool editor_draw(const Cairo::RefPtr<Cairo::Context> &cr);
    bool editor_event(GdkEvent *event);

    void size_value_changed();
    void tip_combo_box_changed();

    Document document;
    std::string title = "Untitled Document";

    Tool *tool = nullptr;
    std::vector<Tool*> tools;

    Gtk::SpinButton *size_spin_button = nullptr;
    Gtk::ComboBoxText *tip_combo_box = nullptr;

    Mode mode = SpriteMode;
    int sprite_index = 0;
    int layer_index = 0;

    Coord cursor_coord = Coord(-1, -1);
    Coord selected_pixel = Coord(-1, -1);

    Tip tip = SquareTip;
    int size = 1;

    float zoom_factor = 10.0;
    float min_padding = 100.0;
    bool show_grid = false;

    Gtk::DrawingArea editor;
};

std::string tip_as_string(Tip tip);

}

#endif
