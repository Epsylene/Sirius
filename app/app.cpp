
#include <Sirius.hpp>

#include "Core/EntryPoint.hpp"

using namespace Sirius;

class ExampleLayer: public Layer
{
    public:

        Ref<Model> suzanne;

        ExampleLayer(): Layer("Example")
        {
            suzanne = std::make_shared<Model>(resPath/"meshes/suzanne/suzanne.obj");
        }

        void onUpdate(Sirius::Timestep dt) override
        {
            Renderer3D::drawModel(suzanne, DrawMode::REFLECTION);
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
