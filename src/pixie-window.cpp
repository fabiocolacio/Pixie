#include <gtkmm/builder.h>
#include <gtkmm/headerbar.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/menubutton.h>
#include <gtkmm/popover.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/aboutdialog.h>
#include <giomm/simpleaction.h>

#include <iostream>

#include "pixie-window.hpp"

using namespace Pixie;

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
    {
        auto app = this->get_application();
        g_assert(app);
        Glib::RefPtr<Gio::SimpleAction> action;

        action = Gio::SimpleAction::create("zoomin");
        action->signal_activate().connect(
            sigc::mem_fun(*this, &Window::zoomin_action_activated));
        app->set_accel_for_action("win.zoomin", "<Ctrl>plus");
        add_action(action);

        action = Gio::SimpleAction::create("zoomfit");
        action->signal_activate().connect(
            sigc::mem_fun(*this, &Window::zoomfit_action_activated));
        app->set_accel_for_action("win.zoomfit", "<Ctrl>equal");
        add_action(action);

        action = Gio::SimpleAction::create("zoomout");
        action->signal_activate().connect(
            sigc::mem_fun(*this, &Window::zoomout_action_activated));
        app->set_accel_for_action("win.zoomout", "<Ctrl>minus");
        add_action(action);

        action = Gio::SimpleAction::create("open");
        action->signal_activate().connect(
            sigc::mem_fun(*this, &Window::open_action_activated));
        app->set_accel_for_action("win.open", "<Ctrl>o");
        add_action(action);

        action = Gio::SimpleAction::create_bool("showgrid", session.get_show_grid());
        action->signal_change_state().connect(
            sigc::mem_fun(*this, &Window::showgrid_action_state_changed));
        app->set_accel_for_action("win.showgrid", "<Ctrl>g");
        add_action(action);

        action = Gio::SimpleAction::create_bool("fullscreen", false);
        action->signal_change_state().connect(
            sigc::mem_fun(*this, &Window::fullscreen_action_state_changed));
        app->set_accel_for_action("win.fullscreen", "F11");
        add_action(action);

        action = Gio::SimpleAction::create("about");
        action->signal_activate().connect(
            sigc::mem_fun(*this, &Window::about_action_activated));
        add_action(action);
    }

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
    content_box.pack_end(session);
    content_box.show();
    add(content_box);
    set_default_size(600, 600);
}

void Window::zoomout_action_activated(const Glib::VariantBase &param)
{
    session.zoom_out();    
}

void Window::zoomfit_action_activated(const Glib::VariantBase &param)
{
    session.zoom_fit();    
}

void Window::zoomin_action_activated(const Glib::VariantBase &param)
{
    session.zoom_in();    
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

void Window::about_action_activated(const Glib::VariantBase &param)
{
    Gtk::AboutDialog dialog;
    dialog.set_program_name("Pixie");
    dialog.set_version(PIXIE_VERSION);
    dialog.set_website(PIXIE_WEBSITE);
    dialog.set_authors({ "Fabio Colacio" });
    dialog.set_transient_for(*this);
    dialog.run();
}

void Window::showgrid_action_state_changed(const Glib::VariantBase &state)
{
    Glib::RefPtr<Gio::SimpleAction> action = 
        Glib::RefPtr<Gio::SimpleAction>::cast_dynamic(lookup_action("showgrid"));
    action->set_state(state);

    bool value;
    state.store(&value);
    session.set_show_grid(value);
}

void Window::fullscreen_action_state_changed(const Glib::VariantBase &state)
{
    Glib::RefPtr<Gio::SimpleAction> action = 
        Glib::RefPtr<Gio::SimpleAction>::cast_dynamic(lookup_action("fullscreen"));
    action->set_state(state);

    bool value;
    state.store(&value);
    if (value) {
        header_box.remove(*header_bar);
        content_box.pack_start(*header_bar, false, true);
        fullscreen();
    }
    else {
        content_box.remove(*header_bar);
        header_box.pack_start(*header_bar, false, true);
        unfullscreen();
    }
}

bool Window::on_delete_event(GdkEventAny *event)
{
    if (auto app = get_application())
        app->remove_window(*this); 
    delete this;
    return false;
}

