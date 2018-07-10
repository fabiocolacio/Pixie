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

RGBA Layer::get_pixel(int x, int y) const
{
    if (x < 0 || x >= pixbuf->get_width() ||
        y < 0 || y >= pixbuf->get_width())
        return { 0, 0, 0, 0 };

    int rowstride = pixbuf->get_rowstride();
    int n_channels = pixbuf->get_n_channels();
    
    guchar *pixel = pixbuf->get_pixels() +
        x * n_channels + y * rowstride;

    RGBA color;
    memcpy(&color, pixel, n_channels);
    return color;
}

