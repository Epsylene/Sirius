
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

            Simulation();
            virtual ~Simulation();

            void onEvent(Event& event);
            bool onWindowClose(WindowCloseEvent& event);
            void run();
    };

    Simulation* createSimulation();
}
