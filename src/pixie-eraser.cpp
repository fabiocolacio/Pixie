#include "pixie-eraser.hpp"

using namespace Pixie;


void Eraser::activate(GdkEvent *event, Session &session)
{

}

void Eraser::draw_cursor(const RefPtr<Context> &cr, Session &session)
{

}

Gtk::ToolButton *Eraser::get_toolbutton()
{
    auto button = new Gtk::ToolButton;
    button->set_icon_name("pixie-eraser-symbolic");
    return button;
}

