#ifndef __PIXIE_APPLICATION_HPP__
#define __PIXIE_APPLICATION_HPP__

#include <gtkmm/application.h>

namespace Pixie {

class Application : public Gtk::Application {
public:
    Application();

protected:
    void on_activate() override;

    void on_open(const Gio::Application::type_vec_files &files,
                 const Glib::ustring &hint) override;
};

}

#endif
