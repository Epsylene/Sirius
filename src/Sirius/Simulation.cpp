
#include "Sirius/Simulation.h"

namespace Sirius
{
    Simulation* Simulation::instance = nullptr;

    Simulation::Simulation()
    {
        instance = this;

        window = std::unique_ptr<Window>(Window::create());
        window->setEventCallback([this](Event& event) { onEvent(event); });
    }

    void Simulation::onEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowCloseEvent>([this](WindowCloseEvent& event) { return onWindowClose(event); });

        std::cout << event << "\n";
    }

    bool Simulation::onWindowClose(WindowCloseEvent& event)
    {
        running = false;
        return true;
    }

    void Simulation::run()
    {
        while(running)
        {
            glClearColor(0.28, 0.15, 0.4, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            window->onUpdate();
        }
    }
}


