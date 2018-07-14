#include <gtkmm/application.h>

#include <iostream>

#include "pixie-window.hpp"

#include "pixie.hpp"

namespace Pixie {

Glib::RefPtr<Gtk::Application> app =
    Gtk::Application::create("com.github.fabiocolacio.Pixie", Gio::APPLICATION_HANDLES_OPEN);

void activate()
{
    auto window = new Window(app);
    window->present();
}

void open(const Gio::Application::type_vec_files &files, const Glib::ustring &hint)
{
    for (size_t i = 0; i < files.size(); i++) {
        auto filename = files[i]->get_path();
        auto window = new Window(filename, app);
        window->present();
    }
}

}

int main(int argc, char *argv[]) {
    Pixie::app->signal_open().connect(sigc::ptr_fun(&Pixie::open));
    Pixie::app->signal_activate().connect(sigc::ptr_fun(&Pixie::activate));
    return Pixie::app->run(argc, argv);
}

