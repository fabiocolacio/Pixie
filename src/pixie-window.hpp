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
    Window(const std::string &filename);
    Window(const std::string &filename, const Glib::RefPtr<Gtk::Application> &app);

private:
    void init();

    Session session;

    Gtk::HeaderBar *header_bar = nullptr;
    Gtk::Box header_box;
};

}

#endif
