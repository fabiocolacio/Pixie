#include <gtkmm/applicationwindow.h>

#include <iostream>

#include "pixie-sprite.hpp"
#include "pixie-sprite-editor.hpp"
#include "pixie-session.hpp"

#include "pixie-application.hpp"

using namespace Pixie;

Application::Application() :
    Gtk::Application(
        "com.github.fabiocolacio.Pixie",
        Gio::APPLICATION_HANDLES_OPEN)
{

}

void Application::on_activate()
{
    auto window = new Gtk::Window;
    window->set_title("Pixie");
    window->set_default_size(500, 500);
    window->show_all();
    add_window(*window);

    std::cout << "Activated!" << std::endl;
}

void Application::on_open(const Gio::Application::type_vec_files &files,
                          const Glib::ustring &hint)
{
    for (size_t i = 0; i < files.size(); i++) {
        auto filename = files[i]->get_path();

        std::cout << "Opening file: '" << filename << "'\n";

        auto window = new Gtk::ApplicationWindow;
        auto session = new Session(filename);
        session->show_all();
        window->add(*session);
        window->set_title(session->get_title());
        window->show_all();

        add_window(*window);
    }
}
