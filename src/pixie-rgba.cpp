#include <cmath>

#include "pixie-rgba.hpp"

using namespace Pixie;

double byte_to_float(uint8_t b)
{
    return b / 255; 
}

uint8_t float_to_byte(double f)
{
    f = std::max(0.0, std::min(1.0, f));
    return std::floor(f >= 1.0 ? 0xff : f * 256.0);
}

RGBA::RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
    red(r), green(g), blue(b), alpha(a)
{

}

RGBA::RGBA(Gdk::RGBA color) :
    red(float_to_byte(color.get_red())),
    green(float_to_byte(color.get_green())),
    blue(float_to_byte(color.get_blue())),
    alpha(float_to_byte(color.get_alpha()))
{

}

RGBA::RGBA(uint32_t color) :
      red((color & 0xff000000) >> 24),
    green((color & 0x00ff0000) >> 16),
     blue((color & 0x0000ff00) >>  8),
    alpha((color & 0x000000ff) >>  0)
{

}

Gdk::RGBA RGBA::to_gdk_rgba() const
{
    GdkRGBA color;
    color.red = byte_to_float(red);
    color.green = byte_to_float(green);
    color.blue = byte_to_float(blue);
    color.alpha = byte_to_float(alpha);
    return Gdk::RGBA(&color);
}

uint32_t RGBA::to_uint32_t() const
{
    return 0x00000000 | red | green | blue | alpha;
}

