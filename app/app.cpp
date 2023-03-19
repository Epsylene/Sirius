
#include <Sirius.hpp>

#include "Core/EntryPoint.hpp"

class ExampleLayer: public Sirius::Layer
{
    public:

        Sirius::Ref<Sirius::Model> suzanne;

        ExampleLayer(): Layer("Example")
        {
        }

        void onUpdate(Sirius::Timestep dt) override
        {
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

        Test(): Application()
        {
            // @todo : rehaul layer/overlay system
            pushLayer(std::make_shared<ExampleLayer>());
        }
};

std::unique_ptr<Sirius::Application> Sirius::createApplication()
{
    return std::make_unique<Test>();
}
