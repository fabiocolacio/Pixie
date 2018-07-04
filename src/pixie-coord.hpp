#ifndef __PIXIE_COORD_H__
#define __PIXIE_COORD_H__

#include "pixie-coordf.hpp"

#include "pixie-transform.hpp"

namespace Pixie {

struct Coord {
    int x;
    int y;

    Coord(int x, int y);

    Coord transform(Transform t) const;

    Coord operator+(const Coord& other) const;
    Coord operator-(const Coord& other) const;

    Coord operator*(int scalar) const;
    CoordF operator/(float scalar) const;
};

}

#endif
