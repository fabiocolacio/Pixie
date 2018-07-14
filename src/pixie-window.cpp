#include <gtkmm/builder.h>
#include <gtkmm/headerbar.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/menubutton.h>
#include <gtkmm/popover.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/aboutdialog.h>
#include <gtkmm/menubar.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/dialog.h>
#include <giomm/simpleaction.h>
#include <giomm/menumodel.h>

#include <iostream>

#include "pixie-window.hpp"

using namespace Pixie;

Window::Window(Session *session, const Glib::RefPtr<Gtk::Application> &app) :
    Gtk::ApplicationWindow(app),
    session(session)
{
    init();
    init_ui();
}

Window::Window(const Glib::RefPtr<Gtk::Application> &app) :
    Gtk::ApplicationWindow(app)
{
    init();
    init_ui();
}

Window::Window(Document &doc, const Glib::RefPtr<Gtk::Application> &app) :
    Gtk::ApplicationWindow(app),
    session(new Pixie::Session(doc))
{
    init();
    init_ui();
}

Window::Window(const std::string &filename, const Glib::RefPtr<Gtk::Application> &app) :
    Gtk::ApplicationWindow(app),
    session(new Session(filename))
{
    init();
    init_ui();
}

Window::~Window()
{
    if (session != nullptr) delete session; 
}

void Window::init_ui()
{
    auto builder = Gtk::Builder::create();

    if (use_headerbar) {
        // Header Bar //
        set_titlebar(header_box);
        builder->add_from_resource("/com/github/fabiocolacio/pixie/ui/pixie-headerbar.ui");
        builder->get_widget("header_bar", header_bar);
        header_bar->show();
        header_bar->set_show_close_button(true);
        if (session) {
            header_bar->set_title(session->get_title());
            header_bar->set_subtitle(session->get_subtitle());
        }
        else {
            header_bar->set_title("Pixie");
        }
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
    }
    else {
        // Menubar //
        builder->add_from_resource("/com/github/fabiocolacio/pixie/ui/pixie-menubar.ui");

        auto model = Glib::RefPtr<Gio::MenuModel>::cast_dynamic(
            builder->get_object("menubar"));
        auto menu_bar = Gtk::manage(new Gtk::MenuBar(model));
        menu_bar->set_visible(true);
        content_box.pack_start(*menu_bar, Gtk::PACK_SHRINK);
        
        if (session) {
            set_title(session->get_title());
        }
        else {
            set_title("Pixie");
        }
    }

    if (session) {
        session->show();
        content_box.pack_end(*session);
    }

    content_box.show();
    add(content_box);
    set_default_size(600, 600);
}

void Window::init()
{
    // Actions //
    auto app = this->get_application();
    g_assert(app);
    Glib::RefPtr<Gio::SimpleAction> action;

    action = Gio::SimpleAction::create("zoomin");
    action->signal_activate().connect( sigc::mem_fun(*this, &Window::zoomin_action_activated));
    if (session == nullptr) action->set_enabled(false);
    app->set_accel_for_action("win.zoomin", "<Ctrl>plus");
    add_action(action);

    action = Gio::SimpleAction::create("zoomfit");
    action->signal_activate().connect(
        sigc::mem_fun(*this, &Window::zoomfit_action_activated));
    if (session == nullptr) action->set_enabled(false);
    app->set_accel_for_action("win.zoomfit", "<Ctrl>equal");
    add_action(action);

    action = Gio::SimpleAction::create("zoomout");
    action->signal_activate().connect(
        sigc::mem_fun(*this, &Window::zoomout_action_activated));
    if (session == nullptr) action->set_enabled(false);
    app->set_accel_for_action("win.zoomout", "<Ctrl>minus");
    add_action(action);

    action = Gio::SimpleAction::create("open");
    action->signal_activate().connect(
        sigc::mem_fun(*this, &Window::open_action_activated));
    app->set_accel_for_action("win.open", "<Ctrl>o");
    add_action(action);

    action = Gio::SimpleAction::create("new");
    action->signal_activate().connect(
        sigc::mem_fun(*this, &Window::new_action_activated));
    app->set_accel_for_action("win.new", "<Ctrl>n");
    add_action(action);

    action = Gio::SimpleAction::create_bool("showgrid",(session) ? session->get_show_grid() : false);
    action->signal_change_state().connect(
        sigc::mem_fun(*this, &Window::showgrid_action_state_changed));
    if (session == nullptr) action->set_enabled(false);
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

void Window::set_session(Session *session)
{
    this->session = session;
    session->show();
    content_box.pack_start(*session);
    Glib::RefPtr<Gio::SimpleAction>::cast_static(lookup_action("showgrid"))->set_enabled(true);
    Glib::RefPtr<Gio::SimpleAction>::cast_static(lookup_action("zoomin"))->set_enabled(true);
    Glib::RefPtr<Gio::SimpleAction>::cast_static(lookup_action("zoomout"))->set_enabled(true);
    Glib::RefPtr<Gio::SimpleAction>::cast_static(lookup_action("zoomfit"))->set_enabled(true);
}

void Window::zoomout_action_activated(const Glib::VariantBase &param)
{
    session->zoom_out();    
}

void Window::zoomfit_action_activated(const Glib::VariantBase &param)
{
    session->zoom_fit();    
}

void Window::zoomin_action_activated(const Glib::VariantBase &param)
{
    session->zoom_in();    
}

void Window::open_action_activated(const Glib::VariantBase &param)
{
    auto file_chooser = Gtk::FileChooserDialog(*this, "Open a Sprite");
    file_chooser.set_select_multiple(true);
    if (auto bar = file_chooser.get_header_bar())
        bar->set_show_close_button(false);
    file_chooser.add_button("Cancel", 0);
    file_chooser.add_button("Open", 1);
    file_chooser.set_default_response(1);

    if (file_chooser.run()) {
        auto files = file_chooser.get_filenames();
        for (auto name : files) {
            if (session) {
                auto window = new Window(name, get_application());
                window->show();
            }
            else {
                set_session(new Session(name));
            }
        }
    }
}

void Window::new_action_activated(const Glib::VariantBase &param)
{
    Gtk::Label *label = nullptr;
    Gtk::Dialog dialog;
    auto grid = Gtk::manage(new Gtk::Grid);

    label = Gtk::manage(new Gtk::Label("Width"));
    label->set_xalign(1.0);
    auto width_entry = Gtk::manage(new Gtk::SpinButton(
        Gtk::Adjustment::create(
            20,      // value
            1.0,     // lower bound
            5000.0,  // upper bound
            1.0,     // step increment
            5.0,     // page increment
            0.0)     // page size
    ));
    grid->attach(*label, 0, 0, 1, 1);
    grid->attach_next_to(*width_entry, *label, Gtk::POS_RIGHT, 1, 1);

    label = Gtk::manage(new Gtk::Label("Height"));
    label->set_xalign(1.0);
    auto height_entry = Gtk::manage(new Gtk::SpinButton(
        Gtk::Adjustment::create(
            20,      // value
            1.0,     // lower bound
            5000.0,  // upper bound
            1.0,     // step increment
            5.0,     // page increment
            0.0)     // page size
    ));
    grid->attach(*label, 0, 1, 1, 1);
    grid->attach_next_to(*height_entry, *label, Gtk::POS_RIGHT, 1, 1);

    label = Gtk::manage(new Gtk::Label("Background Color"));
    label->set_xalign(1.0);
    auto color_button = Gtk::manage(new Gtk::ColorButton);
    grid->attach(*label, 0, 3, 1, 1);
    grid->attach_next_to(*color_button, *label, Gtk::POS_RIGHT, 1, 1);

    label = Gtk::manage(new Gtk::Label("Alpha Channel"));
    label->set_xalign(1.0);
    auto alpha_button = Gtk::manage(new Gtk::CheckButton);
    alpha_button->set_active(true);
    auto callback = [color_button, alpha_button] {
        ((Gtk::ColorButton*)color_button)->set_use_alpha(alpha_button->get_active()); };
    alpha_button->signal_toggled().connect(callback);
    callback();
    grid->attach(*label, 0, 2, 1, 1);
    grid->attach_next_to(*alpha_button, *label, Gtk::POS_RIGHT, 1, 1);

    dialog.add_button("Cancel", 0);
    dialog.add_button("Okay", 1);
    dialog.set_default_response(1);

    grid->property_row_spacing() = 6;
    grid->property_column_spacing() = 12;
    grid->set_column_homogeneous(false);

    grid->show_all();
    dialog.get_vbox()->pack_start(*grid);
    dialog.get_vbox()->set_margin_left(18);
    dialog.get_vbox()->set_margin_right(18);
    dialog.get_vbox()->set_margin_top(18);
    dialog.set_transient_for(*this);

    if (dialog.run()) {
        int width = width_entry->get_value_as_int();
        int height = width_entry->get_value_as_int();
        bool alpha = alpha_button->get_active();
        RGBA color(color_button->get_rgba());
        Sprite sprite(width, height, alpha, color);
        Document doc(sprite);
        auto session = new Session(doc);

        if (this->session) {
            auto window = new Window(session, get_application());
            window->present();
        }
        else {
            set_session(session);
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
    session->set_show_grid(value);
}

void Window::fullscreen_action_state_changed(const Glib::VariantBase &state)
{
    Glib::RefPtr<Gio::SimpleAction> action = 
        Glib::RefPtr<Gio::SimpleAction>::cast_dynamic(lookup_action("fullscreen"));
    action->set_state(state);

    bool value;
    state.store(&value);
    if (value) {
        if (use_headerbar) {
            header_box.remove(*header_bar);
            content_box.pack_start(*header_bar, false, true);
        }
        fullscreen();
    }
    else {
        if (use_headerbar) {
            content_box.remove(*header_bar);
            header_box.pack_start(*header_bar, false, true);
        }
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

