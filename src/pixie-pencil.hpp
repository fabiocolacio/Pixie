#ifndef __PIXIE_PENCIL_HPP__
#define __PIXIE_PENCIL_HPP__

#include "pixie-tool.hpp"

namespace Pixie {

class Pencil : public Tool {
public:
    enum Tip {
        Square,
        Diamond
    };

    Pencil(int size = 1, Tip tip = Square);

    void activate(GdkEvent *event, Session &session) override;
    void draw_cursor(const RefPtr<Context> &cr, Session &session) override;
    Gtk::Toolbar *get_toolbar() override;

    int get_size() const;
    void set_size(int size);

    Tip get_tip() const;
    void set_tip(Tip tip);

private:
    int size; 
    Tip tip;
};

}

#endif
