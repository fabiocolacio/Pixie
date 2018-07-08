#include <gtkmm/builder.h>
#include <gtkmm/headerbar.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/menubutton.h>
#include <gtkmm/popover.h>

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
    auto builder = Gtk::Builder::create();

    // Header Bar //
    set_titlebar(header_box);
    builder->add_from_resource("/com/github/fabiocolacio/pixie/ui/pixie-headerbar.ui");
    builder->get_widget("header_bar", header_bar);
    header_bar->show();
    header_bar->set_show_close_button(true);
    header_bar->set_title(session.get_title());
    header_bar->set_subtitle(session.get_subtitle());
    header_box.show();
    header_box.pack_start(*header_bar);

    // Open Buttons //
    Gtk::ButtonBox *button_box = nullptr;
    builder->get_widget("open_button_box", button_box);
    button_box->set_homogeneous(false);

    // Popover Menu //
    builder->add_from_resource("/com/github/fabiocolacio/pixie/ui/pixie-window-menu.ui");
    Gtk::MenuButton *menu_button = nullptr;
    builder->get_widget("menu_btn", menu_button);
    Gtk::Popover *window_menu = nullptr;
    builder->get_widget("window_menu", window_menu);
    menu_button->set_use_popover(true);
    menu_button->set_popover(*window_menu);
    menu_button->set_direction(Gtk::ARROW_DOWN);

    session.show();
    add(session);
    set_default_size(600, 600);
}

