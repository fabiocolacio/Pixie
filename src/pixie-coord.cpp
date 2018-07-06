#include "pixie-coord.hpp"

using namespace Pixie;

Coord::Coord(int x, int y) : x(x), y(y) { }

Coord::Coord(CoordF coord) : x((int) coord.x), y((int) coord.y) { }

Coord Coord::transform(Transform t) const
{
    return {
        t.xx * x + t.xy * y + t.x0,
        t.yx * x + t.yy * y + t.y0
    };
}

Coord Coord::operator+(const Coord &other) const
{
    return { x + other.x, y + other.y };
}

Coord Coord::operator-(const Coord &other) const
{
    return { x - other.x, y - other.y };
}

Coord Coord::operator*(int scalar) const
{
    return { x * scalar, y * scalar };
}

CoordF Coord::operator/(float scalar) const
{
    return { x / scalar, y / scalar };
}

std::ostream &Pixie::operator<<(std::ostream &stream, const Coord &coord)
{
    return stream << "(" << coord.x << ", " << coord.y << ")";
}

