#include <gtkmm/application.h>

#include <iostream>

#include "pixie-window.hpp"

Glib::RefPtr<Gtk::Application> app =
    Gtk::Application::create("com.github.fabiocolacio.Pixie", Gio::APPLICATION_HANDLES_OPEN);

void open(const Gio::Application::type_vec_files &files, const Glib::ustring &hint)
{
    for (size_t i = 0; i < files.size(); i++) {
        auto filename = files[i]->get_path();

        std::cout << "Opening file: '" << filename << "'\n";

        auto window = new Pixie::Window(filename, app);
        window->show();
    }
}

int main(int argc, char *argv[]) {
    app->signal_open().connect(sigc::ptr_fun(&open));

    return app->run(argc, argv);
}

