
#include <Sirius.hpp>

#include "Sirius/Core/EntryPoint.hpp"

class ExampleLayer: public Sirius::Layer
{
    public:

        Sirius::Ref<Sirius::Model> suzanne;

        ExampleLayer(): Layer("Example")
        {
            suzanne = std::make_shared<Sirius::Model>(Sirius::resPath/"meshes/suzanne/suzanne.obj");
            Sirius::Scene::sceneData.models.emplace_back(suzanne);
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
