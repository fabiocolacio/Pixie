#include "pixie-coordf.hpp"

using namespace Pixie;

CoordF::CoordF(float x, float y) : x(x), y(y) {}

CoordF CoordF::transform(TransformF t) const
{
    return {
        t.xx * x + t.xy * y + t.x0,
        t.yx * x + t.yy * y + t.y0
    };
}

CoordF CoordF::operator+(const CoordF &other) const
{
    return { x + other.x, y + other.y };
}

CoordF CoordF::operator-(const CoordF &other) const
{
    return { x - other.x, y - other.y };
}

CoordF CoordF::operator*(float scalar) const
{
    return { x * scalar, y * scalar };
}

CoordF CoordF::operator/(float scalar) const
{
    return { x / scalar, y / scalar };
}

