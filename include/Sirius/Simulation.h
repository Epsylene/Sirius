
#pragma once

#include "srspch.h"
#include "GLFW/glfw3.h"
#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

namespace Sirius
{
    /////////////////////////////////////////
    /// @brief Simulation class
    /// 
    /// This is the main class, where the application loop is 
    class Simulation
    {
        private:

            static Simulation* instance;

            std::unique_ptr<Window> window;
            bool running = true;

        public:

            /////////////////////////////////////////
            /// @brief Default constructor
            ///
            /// A single window is created, where the
            /// simulation lives.
            Simulation();

            inline static Simulation& get() { return *instance; }
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
