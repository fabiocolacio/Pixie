#ifndef __PIXIE_LAYER_HPP__
#define __PIXIE_LAYER_HPP__

#include <gdkmm/pixbuf.h>

namespace Pixie {

class Layer {
public:
    Layer(const std::string &filename);

    Glib::RefPtr<Gdk::Pixbuf> &get_pixbuf();

private:
    Glib::RefPtr<Gdk::Pixbuf> pixbuf;
};

}

#endif
