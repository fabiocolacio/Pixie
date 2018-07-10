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
        return RGBA(0x00000000);

    int rowstride = pixbuf->get_rowstride();
    int n_channels = pixbuf->get_n_channels();
    
    guchar *pixel = pixbuf->get_pixels() +
        x * n_channels + y * rowstride;

    return RGBA(pixel[0], pixel[1], pixel[2], pixel[3]);
}

void Layer::set_pixel(int x, int y, RGBA color)
{
    if (x < 0 || x >= pixbuf->get_width() ||
        y < 0 || y >= pixbuf->get_width())
        return;

    int rowstride = pixbuf->get_rowstride();
    int n_channels = pixbuf->get_n_channels();
    
    guchar *pixel = pixbuf->get_pixels() +
        x * n_channels + y * rowstride;

    uint32_t data = color.to_uint32_t(); 
    memcpy(pixel, &data, n_channels);
}

