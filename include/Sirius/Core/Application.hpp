
#pragma once

#include "srspch.hpp"
#include "Core.hpp"

#include "Window.hpp"
#include "Sirius/Events/Event.hpp"
#include "Sirius/Events/ApplicationEvent.hpp"

#include "Timestep.hpp"

#include "LayerStack.hpp"
#include "Sirius/UI/ImGuiLayer.hpp"

#include "Sirius/Renderer/Utils/Buffer.hpp"
#include "Sirius/Renderer/Utils/VertexArray.hpp"
#include "Sirius/Renderer/Utils/Shader.hpp"
#include "Sirius/Renderer/Renderer.hpp"
#include "Sirius/Renderer/RenderCommand.hpp"

#include <glad/glad.h>

namespace Sirius
{
    class ImGuiLayer;

    //////////////////////////////////////////////////////////////////
    /// @brief Application class
    /// 
    /// This is the main class, where the application loop is located.
    class Application
    {
        private:

            static Application* instance;

            Scope<Window> window;
            bool running = true, minimized = false;
            float lastFrameTime = 0.f;

            LayerStack layerStack;
            Ref<ImGuiLayer> imGuiLayer;

        public:

            static fs::path appPath;

            /////////////////////////////////////////
            /// @brief Default constructor
            ///
            /// A single window is created, where the
            /// simulation lives.
            Application(const fs::path& path);

            //////////////////////////////////////////////////
            /// @brief Application getter
            /// 
            /// There is only one Application object per
            /// application, accessed with this getter.
            inline static Application& get() { return *instance; }

            ///////////////////////////////////////////////
            /// @brief Application window getter
            /// 
            /// Each simulation has a single window,
            /// which is accessed with this getter.
            ///
            /// @see Window class
            inline Window& getWindow() const { return *window; };

            /////////////////////////////////////////
            /// @brief Is called when an event occurs
            /// @see Event class
            void onEvent(Event& event);

            ///////////////////////////////////
            /// @brief Push a new window layer
            /// @see Layer class
            void pushLayer(const Ref<Layer>& layer);

            ////////////////////////////////////
            /// @brief Push a new window overlay
            /// @see Layer class
            void pushOverlay(const Ref<Layer>& overlay);

            //////////////////////////////////////////////
            /// @brief Is called when the window is closed
            /// @return True
            bool onWindowClose(WindowCloseEvent& event);

            ///////////////////////////////////////////////
            /// @brief Is called when the window is resized
            /// @return False
            bool onWindowResize(WindowResizeEvent& event);

            ///////////////////////////////////////////////////////////
            /// @brief Main application loop
            /// @see onUpdate()
            void run();
    };

    Scope<Sirius::Application> createApplication();
}
