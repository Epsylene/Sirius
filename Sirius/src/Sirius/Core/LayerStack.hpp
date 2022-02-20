
#pragma once

#include "srspch.hpp"
#include "Layer.hpp"

namespace Sirius
{
    ////////////////////////////////////////////////////////////////
    /// @brief Window layers and overlays system class
    ///
    /// This class provides functions to push and pop *layers*
    /// (in-window layer) and *overlays* (out of the window layers).
    /// It is not an actual stack, but one stack of overlays on top
    /// of another stack of layers.
    ///
    /// @see Layer class
    class LayerStack
    {
        private:

            // We provide both a layer and an overlay push() and
            //  pop() functions because we want a half of a stack
            //  to be comprised of layers and half of overlays. It
            //  is to handle the first half that we provide a
            //  'layerTop' iterator.
            std::vector<Ref<Layer>> layers;
            unsigned int layerTopIndex = 0;

        public:

            ///////////////////////////////
            /// @brief Push a window layer.
            /// @see Layer class
            void pushLayer(Ref<Layer> layer);

            //////////////////////////////
            /// @brief Pop a window layer.
            /// @see Layer class
            void popLayer(Ref<Layer> layer);

            ///////////////////////////////
            /// @brief Push a window layer.
            /// @see Layer class
            void pushOverlay(Ref<Layer> overlay);

            ////////////////////////////////
            /// @brief Pop a window overlay.
            /// @see Layer class
            void popOverlay(Ref<Layer> overlay);

            //Allow iterating through the Scope<Layer> vector.
            std::vector<Ref<Layer>>::iterator begin() { return layers.begin(); }
            std::vector<Ref<Layer>>::iterator end() { return layers.end(); }
    };
}
