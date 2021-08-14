
#include "Sirius/Core/Application.hpp"

namespace Sirius
{
    Application* Application::instance = nullptr;

    Application::Application()
    {
        SRS_CORE_ASSERT(!instance, "Application already exists")
        instance = this;

        Log::init();

        window = std::make_unique<Window>();
        window->setEventCallback([this](Event& event) { onEvent(event); });
        window->preRenderFBO = std::make_unique<FrameBuffer>(window->getWidth(), window->getHeight());
        window->postRenderFBO = std::make_unique<FrameBuffer>(window->getWidth(), window->getHeight());

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

        Renderer::onWindowResize(event.getWidth(), event.getHeight());
        return false;
    }

    void Application::run()
    {
        while(running)
        {
            window->preRenderFBO->bind();
            RenderCommand::setDepthTest(true);
            RenderCommand::setClearColor(Scene::properties.background);
            RenderCommand::clear();

            auto time = (float)glfwGetTime();
            Timestep dt = time - lastFrameTime;
            lastFrameTime = time;

            // Update the layers
            if(!minimized)
            {
                RenderCommand::setWireframeMode(Scene::properties.wireframe);

                for (const auto& layer: layerStack)
                    layer->onUpdate(dt);

                RenderCommand::setWireframeMode(false);
            }

            window->preRenderFBO->unbind();
            RenderCommand::setDepthTest(false);
            RenderCommand::setClearColor(Color::White);
            RenderCommand::clear(COLOR_BUFFER);
            Renderer::setPostProcessing(INVERSION);
            window->postRenderFBO->bind();
            Renderer::applyPostProcessing(window->preRenderFBO);
            window->postRenderFBO->unbind();

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


