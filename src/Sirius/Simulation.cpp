
#include "Sirius/Simulation.h"

namespace Sirius
{
#define BIND_EVENT_FN(x) std::bind(&Simulation::x, this, std::placeholders::_1)

    Simulation::Simulation()
    {
        window = std::unique_ptr<Window>(Window::create());
        window->setEventCallback(BIND_EVENT_FN(onEvent));
    }

    Simulation::~Simulation()
    {}

    void Simulation::onEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

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


