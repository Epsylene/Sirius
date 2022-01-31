
#include <Sirius.hpp>
#include <Sirius/Core/EntryPoint.hpp>

class ExampleLayer: public Sirius::Layer
{
    public:

        Sirius::Vec2 pos {-2.f, -2.f};
        Sirius::Vec2 vel {5.f, 0.0f};
        Sirius::Vec2 acc {};

        Sirius::Vec2 q0 {}, p0 {};
        Sirius::Vec2 q {}, p {};
        float m1 = 50, m2 = 10;

        ExampleLayer(): Layer("Example")
        {
        }

        void onUpdate(Sirius::Timestep dt) override
        {

            Sirius::Renderer2D::drawCircle(pos, {0.5f, 0.5f}, Sirius::Color::Red);
            Sirius::Renderer2D::drawCircle({}, {0.1f, 0.1f}, Sirius::Color::Black);
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
