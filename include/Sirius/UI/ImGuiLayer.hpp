
#pragma once

#include "srspch.hpp"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <filebrowser/imfilebrowser.h>

#include "Sirius/Core/Layer.hpp"
#include "Sirius/Core/Application.hpp"
#include "Sirius/Renderer/Objects/CameraController.hpp"
#include "Sirius/Renderer/Objects/Model.hpp"
#include "Sirius/UI/Scene.hpp"
#include "Sirius/UI/Panels.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

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
