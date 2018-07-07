#ifndef __PIXIE_SESSION_HPP__
#define __PIXIE_SESSION_HPP__

#include <gtkmm/box.h>

#include "pixie-document.hpp"

namespace Pixie {

class Session : public Gtk::Box {
public:
    Session(const std::string &filename);
    Session(Document&& document);

    std::string get_title() const;

private:
    void init_ui();

    Document document;
    SpriteEditor sprite_editor;

    std::string title = "Untitled Document";
};

}

#endif
