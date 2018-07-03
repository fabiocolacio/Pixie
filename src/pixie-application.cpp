#include <gtkmm/applicationwindow.h>

#include <iostream>

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
    window->reference();
    add_window(*window);

    std::cout << "Activated!" << std::endl;
}

void Application::on_open(const Gio::Application::type_vec_files &files,
                          const Glib::ustring &hint)
{
    for (int i = 0; i < files.size(); i++) {
        std::cout << "Opening file: '" << files[i]->get_basename() << "'\n";
    }
}
