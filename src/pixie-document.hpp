#ifndef __PIXIE_DOCUMENT_HPP__
#define __PIXIE_DOCUMENT_HPP__

#include <giomm/file.h>

#include <string>

#include "pixie-sprite.hpp"

namespace Pixie {

class Document {
public:
    Document(const std::string &filename);

    int width() const;
    int height() const;
    Coord size() const;

    std::vector<Sprite> sprites;
    Glib::RefPtr<Gio::File> file;
};

}

#endif
