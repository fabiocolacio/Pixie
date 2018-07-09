#include <gtkmm/builder.h>
#include <gtkmm/headerbar.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/menubutton.h>
#include <gtkmm/popover.h>
#include <gtkmm/filechooserdialog.h>
#include <giomm/simpleaction.h>

#include <iostream>

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

Window::~Window()
{
    
}

void Window::init()
{
    // Actions //
    auto app = this->get_application();
    Glib::RefPtr<Gio::SimpleAction> action;
    action = Gio::SimpleAction::create("open");
    action->signal_activate().connect(
        sigc::mem_fun(*this, &Window::open_action_activated));
    if (app) app->set_accel_for_action("win.open", "<Ctrl>o");
    add_action(action);

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

void Window::open_action_activated(const Glib::VariantBase &param)
{
    auto file_chooser = Gtk::FileChooserDialog(*this, "Open a Sprite");
    file_chooser.set_select_multiple(true);
    file_chooser.get_header_bar()->set_show_close_button(false);
    file_chooser.add_button("Cancel", 0);
    file_chooser.add_button("Open", 1);
    file_chooser.set_default_response(1);

    if (file_chooser.run()) {
        auto files = file_chooser.get_filenames();
        for (auto name : files) { 
            auto window = new Window(name, get_application());
            window->show();
        }
    }
}

bool Window::on_delete_event(GdkEventAny *event)
{
    if (auto app = get_application())
        app->remove_window(*this); 
    delete this;
    return false;
}
