#ifndef __PIXIE_LAYER_HPP__
#define __PIXIE_LAYER_HPP__

#include <gdkmm/pixbuf.h>

#include "pixie-rgba.hpp"

namespace Pixie {

class Layer {
public:
    Layer(const std::string &filename);

    Glib::RefPtr<Gdk::Pixbuf> &get_pixbuf();
    const Glib::RefPtr<Gdk::Pixbuf> &get_pixbuf() const;

    RGBA get_pixel(int x, int y) const;

private:
    Glib::RefPtr<Gdk::Pixbuf> pixbuf;
};

}

#endif
