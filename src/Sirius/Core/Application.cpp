
#include "Application.hpp"

namespace Sirius
{
    Application* Application::instance = nullptr;

    Application::Application(const fs::path& path)
    {
        SRS_CORE_ASSERT(!instance, "Application already exists")
        instance = this;

        Log::init();

        window = std::make_unique<Window>();
        window->setEventCallback([this](Event& event) { onEvent(event); });

        Renderer::init();

        imGuiLayer = std::make_shared<ImGuiLayer>();
        pushOverlay(imGuiLayer);
    }

    void Application::pushLayer(const Ref<Layer>& layer)
    {
        layerStack.pushLayer(layer);
        layer->onAttach();
    }

    void Application::pushOverlay(const Ref<Layer>& overlay)
    {
        layerStack.pushOverlay(overlay);
        overlay->onAttach();
    }

    void Application::onEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowCloseEvent>([this](WindowCloseEvent& event) { return onWindowClose(event); });
        dispatcher.dispatch<WindowResizeEvent>([this](WindowResizeEvent& event) { return onWindowResize(event); });

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

    bool Application::onWindowResize(WindowResizeEvent& event)
    {
        if(event.getWidth() == 0 || event.getHeight() == 0)
        {
            minimized = true;
            return false;
        }
        minimized = false;

        return false;
    }

    void Application::run()
    {
        while(running)
        {
            Renderer::preRender();

            auto time = (float)glfwGetTime();
            Timestep dt = time - lastFrameTime;
            lastFrameTime = time;

            // Update the layers
            if(!minimized)
            {
                for (const auto& layer: layerStack)
                    layer->onUpdate(dt);
            }

            Renderer::postRender();

            // Run ImGui and its callbacks
            imGuiLayer->begin();
            for (const auto& layer: layerStack)
                layer->onImGuiRender();
            imGuiLayer->end();

            // Update the window
            window->onUpdate(dt);
        }
    }
}


