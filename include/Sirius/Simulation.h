
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
