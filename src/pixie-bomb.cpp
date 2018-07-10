#include "pixie-session.hpp"

#include "pixie-bomb.hpp"

using namespace Cairo;
using namespace Pixie;


void Bomb::activate(GdkEvent *event, Session &session)
{
    Coord coord = session.get_selected_pixel_coord();
    if (session.get_lmb() && coord.x > 0 && coord.y > 0) {
        auto pixbuf = session.get_active_layer().get_pixbuf();
        pixbuf->fill((pixbuf->get_has_alpha() ? 0xffffff00 : 0xffffffff));
    }
}

void Bomb::draw_cursor(const RefPtr<Context> &cr, Session &session)
{

}

