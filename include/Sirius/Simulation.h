
#pragma once

#include "srspch.h"
#include "GLFW/glfw3.h"
#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

namespace Sirius
{
    class Simulation
    {
        private:

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
            /// @details The onUpdate() function is called in a while
            ///     loop depending on running, which is set to true
            ///     by default and false when a WindowCloseEvent is
            ///     triggered.
            /// @see onUpdate()
            void run();
    };

    Simulation* createSimulation();
}
