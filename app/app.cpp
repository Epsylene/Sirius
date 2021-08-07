
#include <Sirius.hpp>
#include <Sirius/Core/EntryPoint.hpp>

class ExampleLayer: public Sirius::Layer
{
    private:

        Sirius::Model model;
        Sirius::Ref<Sirius::Texture2D> diffuse, specular;
        Sirius::PointLight ptLight {{0.f, 0.f, 0.f}, 60.f};
        Sirius::DirectionalLight dirLight {{-1.f, 0.f, 0.f}};
        Sirius::Spotlight spotLight {{0.f, 0.f, 0.f}, {1.f, 0.f, 0.f}, 60.f, 60.f, 0.1f};

        Sirius::CameraController3D controller {{1.f, 1.f, 1.f}};

    public:

        ExampleLayer(): Layer("Example"), model("../../app/res/meshes/suzanne/suzanne.obj")
        {
//            Sirius::Renderer3D::setDirectionalLight(Sirius::DirectionalLight({1.f, 0.f, 0.f}));
//            Sirius::Renderer3D::addPointLight(ptLight);
//            Sirius::Renderer3D::addPointLight({{2.f, 5.f, 3.f}, 500.f});

            Sirius::Renderer3D::addModel(model);
        }

        void onUpdate(Sirius::Timestep dt) override
        {
            Sirius::RenderCommand::setClearColor({0.003, 0.006, 0.078, 1});
            Sirius::Renderer3D::beginScene(controller.getCamera());

            controller.onUpdate(dt);

            Sirius::Renderer3D::drawEmissionCube({ptLight.pos, 500.f});
            Sirius::Renderer3D::drawModel(model);
//            Sirius::Renderer3D::drawCube({5.f, 0.f, 0.f});

            Sirius::Renderer3D::endScene();
        }

        void onImGuiRender() override
        {
            ImGui::DragFloat3("Light position", &ptLight.pos.x, 0.005f);
        }

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
            pushLayer(std::make_shared<ExampleLayer>());
        }
};

std::unique_ptr<Sirius::Application> Sirius::createApplication()
{
    return std::make_unique<Test>();
}
