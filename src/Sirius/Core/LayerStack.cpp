
#include "Sirius/Core/LayerStack.hpp"

namespace Sirius
{
    LayerStack::LayerStack()
    {}

    LayerStack::~LayerStack()
    {
        for (Layer* layer: layers)
            delete layer;
    }

    void LayerStack::pushLayer(Layer* layer)
    {
        layers.emplace(layers.begin() + layerTopIndex, layer);
        layerTopIndex++;
    }

    void LayerStack::pushOverlay(Layer* overlay)
    {
        layers.emplace_back(overlay);
    }

    void LayerStack::popLayer(Layer* layer)
    {
        auto it = std::find(layers.begin(), layers.end(), layer);

        if(it != layers.end())
        {
            layers.erase(it);
            layerTopIndex--;
        }
    }

    void LayerStack::popOverlay(Layer* overlay)
    {
        auto it = std::find(layers.begin(), layers.end(), overlay);

        if(it != layers.end())
            layers.erase(it);
    }
}
