
#pragma once

#include "srspch.h"

#include "Events/Event.h"

namespace Sirius
{
    ///////////////////////////////////////////////////////////////
    /// @brief Window layer class
    ///
    /// Provides functions to update a layer and set an event
    /// callback upon attaching, detaching and triggering an event.
    ///
    /// @see LayerStack
    class Layer
    {
        protected:

            std::string debugName;

        public:

            Layer(const std::string& name = "Layer");
            virtual ~Layer();

            ////////////////////////////////////
            /// @brief Attach function callback.
            virtual void onAttach() {}

            ////////////////////////////////////
            /// @brief Detach function callback.
            virtual void onDetach() {}

            ////////////////////////////
            /// @brief Update the layer.
            virtual void onUpdate() {}

            ///////////////////////////////////
            /// @brief Event function callback.
            virtual void onEvent(Event& event) {}

            //////////////////////////////
            /// @brief Get the layer name.
            inline const std::string& getName() const { return debugName; }
    };
}
