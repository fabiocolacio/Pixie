#ifndef __PIXIE_WINDOW_HPP__
#define __PIXIE_WINDOW_HPP__

#include <gtkmm/applicationwindow.h>
#include <gtkmm/application.h>
#include <gtkmm/headerbar.h>

#include <string>

#include "pixie-session.hpp"

namespace Pixie {

class Window : public Gtk::ApplicationWindow {
public:
    Window(const std::string &filename, const Glib::RefPtr<Gtk::Application> &app);
    ~Window();

private:
    void init();

    bool on_delete_event(GdkEventAny *event) override;

    void zoomin_action_activated(const Glib::VariantBase &param); // added
    void zoomfit_action_activated(const Glib::VariantBase &param); // added
    void zoomout_action_activated(const Glib::VariantBase &param); // added
    void open_action_activated(const Glib::VariantBase &param); // added
    void save_action_activated(const Glib::VariantBase &param);
    void new_action_activated(const Glib::VariantBase &param);
    void save_as_action_activated(const Glib::VariantBase &param);
    void export_action_activated(const Glib::VariantBase &param);
    void print_action_activated(const Glib::VariantBase &param);
    void showgrid_action_state_changed(const Glib::VariantBase &state); // added
    void fullscreen_action_state_changed(const Glib::VariantBase &state); // added
    void rotate_left_action_activated(const Glib::VariantBase &param);
    void rotate_right_action_activated(const Glib::VariantBase &param);
    void rotate_action_activated(const Glib::VariantBase &param);
    void scale_action_activated(const Glib::VariantBase &param);
    void custom_transform_action_activated(const Glib::VariantBase &param);
    void grayscale_action_activated(const Glib::VariantBase &param);
    void invert_action_activated(const Glib::VariantBase &param);
    void blur_action_activated(const Glib::VariantBase &param);
    void convolution_action_activated(const Glib::VariantBase &param);
    void preferences_action_activated(const Glib::VariantBase &param);
    void keyboard_shortcuts_action_activated(const Glib::VariantBase &param);
    void about_action_activated(const Glib::VariantBase &param); // added
    void quit_action_activated(const Glib::VariantBase &param);

    Session *session = nullptr;

    bool use_headerbar = false;

    Gtk::Box content_box = Gtk::Box(Gtk::ORIENTATION_VERTICAL);
    Gtk::HeaderBar *header_bar = nullptr;
    Gtk::Box header_box = Gtk::Box(Gtk::ORIENTATION_VERTICAL);
};

}

#endif
