#ifndef __PIXIE_ERASER_HPP__
#define __PIXIE_ERASER_HPP__

#include "pixie-tool.hpp"

namespace Pixie {

class Eraser : public Tool {
public:
    void activate(GdkEvent *event, Session &session) override;
    void draw_cursor(const RefPtr<Context> &cr, Session &session) override;
    Gtk::ToolButton *get_toolbutton() override;
};

}

#endif
