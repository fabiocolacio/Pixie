#ifndef __PIXIE_COLOR_SAMPLER_HPP__
#define __PIXIE_COLOR_SAMPLER_HPP__

#include "pixie-tool.hpp"

namespace Pixie {

class ColorSampler : public Tool {
public:
    void activate(GdkEvent *event, Session &session) override;
    void draw_cursor(const RefPtr<Context> &cr, Session &session) override;
};

}

#endif
