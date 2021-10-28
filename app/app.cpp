
#include <Sirius.hpp>
#include <Sirius/Core/EntryPoint.hpp>

class ExampleLayer: public Sirius::Layer
{
    public:

        ExampleLayer(): Layer("Example")
        {

        }

        void onUpdate(Sirius::Timestep dt) override
        {
            Sirius::Renderer2D::drawQuad({0.f, 0.f}, {1.f, 1.f}, Sirius::Color::Black);
        }

        void onImGuiRender() override
        {
        }

        void onEvent(Sirius::Event& event) override
        {
        }
};

class Test: public Sirius::Application
{
    public:

        Test()
        {
            pushLayer(std::make_shared<ExampleLayer>());
        }
};

std::unique_ptr<Sirius::Application> Sirius::createApplication()
{
    return std::make_unique<Test>();
}
