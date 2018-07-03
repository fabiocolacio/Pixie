#include "pixie-document.hpp"

using namespace Pixie;

Document::Document(const std::string &filename) :
    sprite(filename),
    file(Gio::File::create_for_path(filename))
{

}
