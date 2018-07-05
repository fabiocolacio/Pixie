#include "pixie-layer.hpp"

using namespace Pixie;

Layer::Layer(const std::string &filename)
{
    pixbuf = Gdk::Pixbuf::create_from_file(filename);
}

Glib::RefPtr<Gdk::Pixbuf> &Layer::get_pixbuf()
{
    return pixbuf;
}

const Glib::RefPtr<Gdk::Pixbuf> &Layer::get_pixbuf() const
{
    return pixbuf;
}
