
#pragma once

#include "srspch.h"
#include "GLFW/glfw3.h"
#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

namespace Sirius
{
    /////////////////////////////////////////
    /// @brief Application class
    /// 
    class Simulation
    {
        private:

            static Simulation* instance;

            std::unique_ptr<Window> window;
            bool running = true;

        public:

            //////////////////////////////
            /// @brief Default constructor
            Simulation();

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
