
#include "Sirius/Core/Application.h"

namespace Sirius
{
    Application* Application::instance = nullptr;

    Application::Application()
    {
        SRS_CORE_ASSERT(!instance, "Application already exists")
        instance = this;

        Log::init();

        window = std::unique_ptr<Window>(Window::create());
        window->setEventCallback([this](Event& event) { onEvent(event); });

        RenderCommand::init();

        imGuiLayer = new ImGuiLayer();
        pushOverlay(imGuiLayer);
    }

    void Application::pushLayer(Layer* layer)
    {
        layerStack.pushLayer(layer);
        layer->onAttach();
    }

    void Application::pushOverlay(Layer* overlay)
    {
        layerStack.pushOverlay(overlay);
        overlay->onAttach();
    }

    void Application::onEvent(Event& event)
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

    bool Application::onWindowClose(WindowCloseEvent& event)
    {
        running = false;
        return true;
    }

    void Application::run()
    {
        while(running)
        {
            // Clear the window
            RenderCommand::clear();

            auto time = (float)glfwGetTime();
            Timestep dt = time - lastFrameTime;
            lastFrameTime = time;
            
            // Update the layers
            for (Layer* layer: layerStack)
                layer->onUpdate(dt);

            // Run ImGui and its callbacks
            imGuiLayer->begin();
            for (Layer* layer: layerStack)
                layer->onImGuiRender();
            imGuiLayer->end();

            // Update the window
            window->onUpdate(dt);
        }
    }
}


