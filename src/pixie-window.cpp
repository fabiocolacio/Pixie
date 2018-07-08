#include "pixie-window.hpp"

using namespace Pixie;

Window::Window(const std::string &filename) :
    session(filename)
{
    init();
}

Window::Window(const std::string &filename, const Glib::RefPtr<Gtk::Application> &app) :
    Gtk::ApplicationWindow(app),
    session(filename)
{
    init();
}

void Window::init()
{
    add(session);
    set_title(session.get_title());
    set_default_size(600, 600);
}

