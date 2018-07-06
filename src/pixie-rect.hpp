#ifndef __PIXIE_RECT_HPP__
#define __PIXIE_RECT_HPP__

#include "pixie-coord.hpp"
#include "pixie-transform.hpp"

namespace Pixie {

struct Rect {
    Coord tl;
    Coord br;

    Rect(Coord tl, Coord br);
    Rect(CoordF tl, CoordF br);
    Rect(int x, int y, int width, int height);
    Rect(float x, float y, float widht, float height);

    int &top();
    int &left();
    int &right();
    int &bottom();

    int x() const;
    int y() const;
    int width() const;
    int height() const;

    int area() const;
    int perimeter() const;

    bool contains(Coord c) const;
    bool contains(Rect r) const;

    Rect transform(Transform t) const;

    Rect operator+(const Coord &c) const;
    Rect operator-(const Coord &c) const;
};

}

#endif
