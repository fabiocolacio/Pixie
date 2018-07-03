#include "pixie-sprite-editor.hpp"

using namespace Pixie;

SpriteEditor::SpriteEditor(Sprite &sprite, bool read_only) :
    sprite(sprite),
    read_only(read_only)
{

}

bool SpriteEditor::get_read_only() const
{
    return read_only;
}

void SpriteEditor::set_read_only(bool state)
{
    read_only = state;
}

bool SpriteEditor::on_draw(const Cairo::RefPtr<Cairo::Context> &cr)
{
    return false;
}
