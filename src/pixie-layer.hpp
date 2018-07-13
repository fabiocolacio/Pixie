#ifndef __PIXIE_LAYER_HPP__
#define __PIXIE_LAYER_HPP__

#include <gdkmm/pixbuf.h>

#include "pixie-rgba.hpp"

namespace Pixie {

class Layer {
public:
    Layer(const std::string &filename);
    Layer(Glib::RefPtr<Gdk::Pixbuf> pixbuf);

    Glib::RefPtr<Gdk::Pixbuf> &get_pixbuf();
    const Glib::RefPtr<Gdk::Pixbuf> &get_pixbuf() const;

    RGBA get_pixel(int x, int y) const;
    void set_pixel(int x, int y, RGBA color);

private:
    Glib::RefPtr<Gdk::Pixbuf> pixbuf;
};

}

#endif
