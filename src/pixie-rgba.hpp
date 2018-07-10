#ifndef __PIXIE_RGBA_HPP__
#define __PIXIE_RGBA_HPP__

#include <gdkmm/rgba.h>

namespace Pixie {

struct RGBA {
    RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    RGBA(Gdk::RGBA color);
    RGBA(uint32_t color);

    Gdk::RGBA to_gdk_rgba() const;
    uint32_t to_uint32_t() const;

    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
};

}

#endif
