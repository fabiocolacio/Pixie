#ifndef __PIXIE_PENCIL_HPP__
#define __PIXIE_PENCIL_HPP__

#include "pixie-tool.hpp"

namespace Pixie {

class Pencil : public Tool {
public:
    void activate(GdkEvent *event, Session &session) override;
    void draw_cursor(const RefPtr<Context> &cr, Session &session) override;
};

}

#endif
