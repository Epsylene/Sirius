
#include "Sirius.h"

class ExampleLayer: public Sirius::Layer
{
    public:

        ExampleLayer(): Layer("Example")
        {}

        void onUpdate() override {}
        void onImGuiRender() override {}
        void onEvent(Sirius::Event& event) override {}
};

class Test: public Sirius::Simulation
{
    public:

        Test()
        {
            pushLayer(new ExampleLayer());
        }
};

Sirius::Simulation* Sirius::createSimulation()
{
    return new Test();
}
