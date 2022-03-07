
#include <Sirius.hpp>

#include "Sirius/Core/EntryPoint.hpp"

class ExampleLayer: public Sirius::Layer
{
    public:

        Sirius::Ref<Sirius::Model> cylinder;

        ExampleLayer(): Layer("Example")
        {
            cylinder = std::make_shared<Sirius::Model>(Sirius::appPath/"res/meshes/cylinder/cylinder.obj");
            Sirius::Scene::sceneData.models.emplace_back(cylinder);
        }

        void onUpdate(Sirius::Timestep dt) override
        {
            Sirius::Renderer3D::drawEmissionCube({{2.f, 2.f, 2.f}, 100.f});
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
