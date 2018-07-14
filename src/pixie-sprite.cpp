#include <gdkmm/pixbuf.h>

#include <vector>

#include "pixie-layer.hpp"

#include "pixie-sprite.hpp"

using namespace Pixie;

Sprite::Sprite(int width, int height, bool alpha, RGBA bg)
{
    auto pixbuf = Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB, alpha, 8, width, height);
    pixbuf->fill(bg.to_uint32_t());
    layers.push_back(Layer(pixbuf));
}

Sprite::Sprite(const std::string &filename)
{
    layers.push_back(Layer(filename)); 
}

std::size_t Sprite::n_layers() const
{
    return layers.size();
}

std::vector<Layer> &Sprite::get_layers()
{
    return layers;
}

const std::vector<Layer> &Sprite::get_layers() const
{
    return layers;
}

Layer &Sprite::operator[](std::size_t idx)
{
    return get_layers()[idx];
}

const Layer &Sprite::operator[](std::size_t idx) const
{
    return get_layers()[idx];
}

Coord Sprite::size() const
{
    return Coord( width(), height() );
}

int Sprite::width() const
{
    return layers[0].get_pixbuf()->get_width();
}

int Sprite::height() const
{
    return layers[0].get_pixbuf()->get_height();
}
