
#pragma once

#include "srspch.hpp"

namespace Sirius
{
    class Application;

    class ImGuiLayer: public Layer
    {
        public:

            ImGuiLayer();

            void onAttach() override;
            void onDetach() override;

            void onEvent(Event& event) override;
            void onUpdate(Timestep dt) override;
            void onImGuiRender() override;

            void begin();
            void end();
    };
}
