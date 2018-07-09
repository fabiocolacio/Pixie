#include "pixie-rectf.hpp"

using namespace Pixie;

RectF::RectF(CoordF tl, CoordF br) :
    tl(tl),
    br(br)
{
}

RectF::RectF(float x, float y, float width, float height) :
    tl({x, y}),
    br({x + width, y + height})
{
}

float RectF::x() const
{
    return tl.x;
}

float RectF::y() const
{
    return tl.y;
}

float RectF::width() const
{
    return br.x - tl.x;
}

float RectF::height() const
{
    return br.y - tl.y;
}

float &RectF::top()
{
    return tl.y;
}

float &RectF::left()
{
    return tl.x;
}

float &RectF::right()
{
    return br.x;
}

float &RectF::bottom()
{
    return br.y;
}

float RectF::area() const
{
    return width() * height();
}

float RectF::perimeter() const
{
    return 2 * (width() + height());
}

bool RectF::contains(CoordF c) const
{
    return (c.x > tl.x && c.x < br.x &&
            c.y > tl.y && c.y < br.y);
}

bool RectF::contains(Coord c) const
{
    return (c.x > tl.x && c.x < br.x &&
            c.y > tl.y && c.y < br.y);
}

bool RectF::contains(RectF r) const
{
    return (contains(r.tl) && contains(r.br));
}

bool RectF::contains(Rect r) const
{
    return (contains(r.tl) && contains(r.br));
}

RectF RectF::transform(TransformF t) const
{
    return RectF( tl.transform(t), br.transform(t) );
}

RectF RectF::operator+(const CoordF &c) const
{
    return RectF( tl + c, br + c );
}

RectF RectF::operator-(const CoordF &c) const
{
    return RectF( tl - c, br - c);
}

std::ostream &Pixie::operator<<(std::ostream &stream, const RectF &coord)
{
    return stream << "[" << coord.tl << ", " << coord.br << "]";
}
