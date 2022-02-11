
#include <Sirius.hpp>
#include <Sirius/Core/EntryPoint.hpp>

class ExampleLayer: public Sirius::Layer
{
    public:

        Sirius::Model suzanne;

        ExampleLayer(): Layer("Example"), suzanne()
        {
        }

        void onUpdate(Sirius::Timestep dt) override
        {
//            Sirius::Renderer3D::drawModel()
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
