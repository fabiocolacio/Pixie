#ifndef __PIXIE_TOOL_HPP__
#define __PIXIE_TOOL_HPP__

#include <cairomm/context.h>
#include <gtkmm/toolbutton.h>

using namespace Cairo;

namespace Pixie {

class Session;

class Tool {
public:
    virtual ~Tool() {};
    virtual void activate(GdkEvent *event, Session &session) = 0;
    virtual void draw_cursor(const RefPtr<Context> &cr, Session &session) = 0;
    virtual Gtk::ToolButton *get_toolbutton() = 0;
};

}

#endif
