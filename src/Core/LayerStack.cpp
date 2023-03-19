
#include "LayerStack.hpp"

namespace Sirius
{
    void LayerStack::pushLayer(Ref<Layer> layer)
    {
        layers.emplace(layers.begin() + layerTopIndex, layer);
        layerTopIndex++;
    }

    void LayerStack::pushOverlay(Ref<Layer> overlay)
    {
        layers.emplace_back(overlay);
    }

    void LayerStack::popLayer(Ref<Layer> layer)
    {
        auto it = std::find(layers.begin(), layers.end(), layer);

        if(it != layers.end())
        {
            layers.erase(it);
            layerTopIndex--;
        }
    }

    void LayerStack::popOverlay(Ref <Layer> overlay)
    {
        auto it = std::find(layers.begin(), layers.end(), overlay);

        if(it != layers.end())
            layers.erase(it);
    }
}
