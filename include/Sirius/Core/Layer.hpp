
#pragma once

#include <Sirius/Core/Timestep.hpp>
#include "srspch.hpp"

#include "Sirius/Events/Event.hpp"

namespace Sirius
{
    ///////////////////////////////////////////////////////////////
    /// @brief Window layer class
    ///
    /// Provides functions to update a layer and set an event
    /// callback upon attaching and detaching the layer, triggering
    /// an event and rendering the ImGui overlays.
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
            virtual void onUpdate(Timestep dt)
            {}

            /////////////////////////////////////////////
            /// @brief Function callback on ImGui render.
            virtual void onImGuiRender() {}

            ///////////////////////////////////
            /// @brief Event function callback.
            virtual void onEvent(Event& event) {}

            //////////////////////////////
            /// @brief Get the layer name.
            inline const std::string& getName() const { return debugName; }
    };
}
