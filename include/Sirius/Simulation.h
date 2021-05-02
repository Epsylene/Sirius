
#pragma once

#include "srspch.h"

#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

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
            /// There shall be only one Simulation object per
            /// application, accessed through this getter.
            inline static Simulation& get() { return *instance; }

            ///////////////////////////////////////////////
            /// @brief Simulation window getter
            /// 
            /// Each simulation shall have only one window,
            /// which is accessed through this getter.
            inline Window& getWindow() const { return *window; };

            /////////////////////////////////////////
            /// @brief Is called when an event occurs
            /// @param event The event that occured
            void onEvent(Event& event);

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
