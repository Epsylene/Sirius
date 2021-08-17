
#include <Sirius.hpp>
#include <Sirius/Core/EntryPoint.hpp>

class ExampleLayer: public Sirius::Layer
{
    private:

        Sirius::PointLight ptLight {{2.f, 0.f, 0.f}, 60.f};
        Sirius::DirectionalLight dirLight {{1.f, 0.f, 0.f}};

        Sirius::Ref<Sirius::Model> suzanne;

    public:

        ExampleLayer(): Layer("Example")
        {
            Sirius::Renderer3D::setDirectionalLight(dirLight);
            Sirius::Renderer3D::addPointLight(ptLight);
            Sirius::Renderer3D::addPointLight({{2.f, 5.f, 3.f}, 500.f});

            suzanne = std::make_shared<Sirius::Model>("../../app/res/meshes/suzanne/suzanne.obj");
        }

        void onUpdate(Sirius::Timestep dt) override
        {
            Sirius::Renderer3D::drawEmissionCube({{2.f, 0.f, 1.f}, 500.f});
            Sirius::Renderer3D::drawModel(suzanne, Sirius::DrawMode::REFLECTION);
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
