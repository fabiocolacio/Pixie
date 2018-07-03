#include <vector>

#include "pixie-layer.hpp"

#include "pixie-sprite.hpp"

using namespace Pixie;

Sprite::Sprite(const std::string &filename)
{
    layers.push_back(Layer(filename)); 
}

std::vector<Layer> &Sprite::get_layers()
{
    return layers;
}
