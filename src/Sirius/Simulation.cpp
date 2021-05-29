
#include "Sirius/Simulation.h"

namespace Sirius
{
    Simulation* Simulation::instance = nullptr;

    Simulation::Simulation()
    {
        SRS_CORE_ASSERT(!instance, "Application already exists")
        instance = this;

        Log::init();

        window = std::unique_ptr<Window>(Window::create());
        window->setEventCallback([this](Event& event) { onEvent(event); });

        imGuiLayer = new ImGuiLayer();
        pushOverlay(imGuiLayer);
    }

    void Simulation::pushLayer(Layer* layer)
    {
        layerStack.pushLayer(layer);
        layer->onAttach();
    }

    void Simulation::pushOverlay(Layer* overlay)
    {
        layerStack.pushOverlay(overlay);
        overlay->onAttach();
    }

    void Simulation::onEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowCloseEvent>([this](WindowCloseEvent& event) { return onWindowClose(event); });

        for (auto it = layerStack.end(); it != layerStack.begin();)
        {
            (*--it)->onEvent(event);

            if(event.handled)
                break;
        }
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
            // Clear the window
            RenderCommand::setClearColor({0.12, 0.12, 0.12, 1});
            RenderCommand::clear();

            // Update the layers
            for (Layer* layer: layerStack)
                layer->onUpdate();

            // Run ImGui and its callbacks
            imGuiLayer->begin();
            for (Layer* layer: layerStack)
                layer->onImGuiRender();
            imGuiLayer->end();

            // Update the window
            window->onUpdate();
        }
    }
}


