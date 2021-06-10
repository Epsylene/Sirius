
#pragma once

#include "srspch.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Sirius/Core/Layer.h"
#include "Sirius/Core/Application.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Sirius
{
    class Application;

    class ImGuiLayer: public Layer
    {
        private:

            float time = 0.f;

        public:

            ImGuiLayer();

            void onAttach() override;
            void onDetach() override;
            void onUpdate(Timestep dt) override;

            void onImGuiRender() override;

            void begin();
            void end();
    };
}
