#ifndef __PIXIE_DOCUMENT_HPP__
#define __PIXIE_DOCUMENT_HPP__

#include <giomm/file.h>

#include <string>

#include "pixie-sprite.hpp"

namespace Pixie {

class Document {
public:
    Document(const std::string &filename);

private:
    Sprite sprite;
    Glib::RefPtr<Gio::File> file;
};

}

#endif
