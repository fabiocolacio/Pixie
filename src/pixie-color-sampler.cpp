#include "pixie-session.hpp"

#include "pixie-color-sampler.hpp"

using namespace Cairo;
using namespace Pixie;


void ColorSampler::activate(GdkEvent *event, Session &session)
{
    Coord coord = session.get_selected_pixel_coord();
    if (session.get_lmb() && coord.x > 0 && coord.y > 0) {
        session.set_color(
            session.get_active_layer().get_pixel(coord.x, coord.y));
    }
}

void ColorSampler::draw_cursor(const RefPtr<Context> &cr, Session &session)
{

}

