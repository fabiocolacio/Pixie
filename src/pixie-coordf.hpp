#ifndef __PIXIE_COORDF_H__
#define __PIXIE_COORDF_H__

#include <ostream>

#include "pixie-transformf.hpp"

namespace Pixie {

struct CoordF {
    float x;
    float y;

    CoordF(float x, float y);

    CoordF transform(TransformF t) const;

    CoordF operator+(const CoordF &other) const;
    CoordF operator-(const CoordF &other) const;

    CoordF operator*(float scalar) const;
    CoordF operator/(float scalar) const;
};

std::ostream &operator<<(std::ostream &stream, const CoordF &coord);

}

#endif
