#ifndef __PIXIE_COORD_H__
#define __PIXIE_COORD_H__

#include <ostream>

#include "pixie-coordf.hpp"

#include "pixie-transform.hpp"

namespace Pixie {

struct Coord {
    int x;
    int y;

    Coord(int x, int y);
    Coord(CoordF coord);

    Coord transform(Transform t) const;
    
    Coord operator+(const Coord& other) const;
    Coord operator-(const Coord& other) const;

    Coord operator*(int scalar) const;
    CoordF operator/(float scalar) const;

};

std::ostream &operator<<(std::ostream &stream, const Coord &coord);

}

#endif
