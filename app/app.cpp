
#include <Sirius.hpp>
#include <Sirius/Core/EntryPoint.hpp>

class ExampleLayer: public Sirius::Layer
{
    private:

        Sirius::Ref<Sirius::Texture2D> texture;
        Sirius::Color color;

        Sirius::CameraController2D controller;

    public:

        ExampleLayer(): Layer("Example")
        {
            texture = std::make_shared<Sirius::Texture2D>("../../app/assets/textures/sirius.jpg");
        }

        void onUpdate(Sirius::Timestep dt) override
        {
            Sirius::RenderCommand::setClearColor({0.003, 0.006, 0.078, 1});
            Sirius::Renderer2D::beginScene(controller.getCamera());

            controller.onUpdate(dt);

            Sirius::Renderer2D::drawQuad({0.f, 0.f}, {1.f, 1.f}, color);

            Sirius::Renderer::endScene();
        }

        void onImGuiRender() override
        {}

        void onEvent(Sirius::Event& event) override
        {
            controller.onEvent(event);
        }
};

class Test: public Sirius::Application
{
    public:

        Test()
        {
            pushLayer(new ExampleLayer());
        }
};

Sirius::Application* Sirius::createSimulation()
{
    return new Test();
}
