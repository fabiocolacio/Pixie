#ifndef __PIXIE_RECTF_HPP__
#define __PIXIE_RECTF_HPP__

#include "pixie-coord.hpp"
#include "pixie-rect.hpp"
#include "pixie-coordf.hpp"
#include "pixie-transformf.hpp"

namespace Pixie {

struct RectF {
    CoordF tl;
    CoordF br;

    RectF(CoordF tl, CoordF br);
    RectF(float x, float y, float width, float height);

    float &top();
    float &left();
    float &right();
    float &bottom();

    float x() const;
    float y() const;
    float width() const;
    float height() const;

    float area() const;
    float perimeter() const;

    bool contains(CoordF c) const;
    bool contains(Coord c) const;
    bool contains(RectF r) const;
    bool contains(Rect r) const;

    RectF transform(TransformF t) const;

    RectF operator+(const CoordF &c) const;
    RectF operator-(const CoordF &c) const;
};

}

#endif
