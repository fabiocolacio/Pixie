#ifndef __PIXIE_HPP__
#define __PIXIE_HPP__

namespace Pixie {

extern Glib::RefPtr<Gtk::Application> app;

void open(const Gio::Application::type_vec_files &files, const Glib::ustring &hint);

}

#endif
