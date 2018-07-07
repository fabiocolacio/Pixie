#include "pixie-document.hpp"

using namespace Pixie;

Document::Document(const std::string &filename) :
    file(Gio::File::create_for_path(filename))
{
    sprites.push_back(Sprite(filename));
}

int Document::width() const
{
    return sprites[0].width();
}

int Document::height() const
{
    return sprites[0].height();
}

Coord Document::size() const
{
    return sprites[0].size();
}
