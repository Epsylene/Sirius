
#pragma once

#include "srspch.h"
#include "Core.h"

#include "Window.h"
#include "Sirius/Events/Event.h"
#include "Sirius/Events/ApplicationEvent.h"

#include "Timestep.h"

#include "LayerStack.h"
#include "Sirius/ImGui/ImGuiLayer.h"

#include "Sirius/Renderer/Buffer.h"
#include "Sirius/Renderer/VertexArray.h"
#include "Sirius/Renderer/Shader.h"
#include "Sirius/Renderer/Renderer.h"
#include "Sirius/Renderer/RenderCommand.h"

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

            std::unique_ptr<Window> window;
            bool running = true;
            float lastFrameTime = 0.f;

            LayerStack layerStack;
            ImGuiLayer* imGuiLayer;

        public:

            /////////////////////////////////////////
            /// @brief Default constructor
            ///
            /// A single window is created, where the
            /// simulation lives.
            Application();

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
            void pushLayer(Layer* layer);

            ////////////////////////////////////
            /// @brief Push a new window overlay
            /// @see Layer class
            void pushOverlay(Layer* overlay);

            /////////////////////////////////////////////////////////
            /// @brief Is called when a WindowCloseEvent is triggered
            /// @param event The WindowCloseEvent
            /// @return True
            bool onWindowClose(WindowCloseEvent& event);

            ///////////////////////////////////////////////////////////
            /// @brief Main application loop
            /// @see onUpdate()
            void run();
    };

    Application* createSimulation();
}
