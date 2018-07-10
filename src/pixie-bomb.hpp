#ifndef __PIXIE_BOMB_HPP__
#define __PIXIE_BOMB_HPP__

#include "pixie-tool.hpp"

namespace Pixie {

class Bomb : public Tool {
public:
    void activate(GdkEvent *event, Session &session) override;
    void draw_cursor(const RefPtr<Context> &cr, Session &session) override;
};

}

#endif
