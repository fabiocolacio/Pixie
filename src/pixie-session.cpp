#include "pixie-session.hpp"

using namespace Pixie;

Session::Session(const std::string &filename) :
    document(Document(filename)),
    sprite_editor(document.sprite)
{
    init_ui();
}

Session::Session(Document&& document) :
    document(std::move(document)),
    sprite_editor(document.sprite)
{
    init_ui();
}

void Session::init_ui()
{
    sprite_editor.show();
    pack_start(sprite_editor);

    title = document.file->get_basename();
}

std::string Session::get_title() const
{
    return title;
}

