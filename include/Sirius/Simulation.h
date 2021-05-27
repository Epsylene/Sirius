
#pragma once

#include "srspch.h"
#include "Core.h"

#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"

#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"

#include <glad/glad.h>

namespace Sirius
{
    /////////////////////////////////////////////////////////
    /// @brief Simulation class
    /// 
    /// This is the main class, where the application loop is 
    class Simulation
    {
        private:

            static Simulation* instance;

            std::unique_ptr<Window> window;
            bool running = true;
            LayerStack layerStack;

            std::shared_ptr<Shader> shader;
            std::shared_ptr<VertexBuffer> vertexBuffer;
            std::shared_ptr<IndexBuffer> indexBuffer;
            std::shared_ptr<VertexArray> vertexArray;

        public:

            /////////////////////////////////////////
            /// @brief Default constructor
            ///
            /// A single window is created, where the
            /// simulation lives.
            Simulation();

            //////////////////////////////////////////////////
            /// @brief Simulation getter
            /// 
            /// There is only one Simulation object per
            /// application, accessed with this getter.
            inline static Simulation& get() { return *instance; }

            ///////////////////////////////////////////////
            /// @brief Simulation window getter
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

    Simulation* createSimulation();
}
