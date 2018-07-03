#ifndef __PIXIE_SPRITE_HPP__
#define __PIXIE_SPRITE_HPP__

#include <string>
#include <vector>

#include "pixie-layer.hpp"

namespace Pixie {

class Sprite {
public:
    Sprite(const std::string &filename);

    std::vector<Layer> &get_layers();

private:
    std::vector<Layer> layers;
};

}

#endif
