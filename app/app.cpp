
#include <Sirius.hpp>
#include <Sirius/Core/EntryPoint.hpp>

class ExampleLayer: public Sirius::Layer
{
    private:

        Sirius::Ref<Sirius::Model> model, suzanne;
        Sirius::Ref<Sirius::Cube> cubeModel;
        Sirius::Ref<Sirius::Texture2D> diffuse, specular;
        Sirius::PointLight ptLight {{2.f, 0.f, 0.f}, 60.f};
        Sirius::DirectionalLight dirLight {{-1.f, 0.f, 0.f}};

        Sirius::CameraController3D controller {{1.f, 1.f, 1.f}};

    public:

        ExampleLayer(): Layer("Example")
        {
            diffuse = std::make_shared<Sirius::Texture2D>("../../app/res/textures/container.png", Sirius::TextureType::Diffuse);
            specular = std::make_shared<Sirius::Texture2D>("../../app/res/textures/container_specular.png", Sirius::TextureType::Specular);

//            cubeModel = std::make_shared<Sirius::Cube>(Sirius::Material(diffuse, specular));
//            suzanne = std::make_shared<Sirius::Model>("../../app/res/meshes/suzanne/suzanne.obj");
            model = std::make_shared<Sirius::Model>("../../app/res/meshes/plane/plane.obj");

            Sirius::Renderer3D::setDirectionalLight(Sirius::DirectionalLight({1.f, 0.f, 0.f}));
            Sirius::Renderer3D::addPointLight(ptLight);
            Sirius::Renderer3D::addPointLight({{2.f, 5.f, 3.f}, 500.f});
        }

        void onUpdate(Sirius::Timestep dt) override
        {
            Sirius::Renderer3D::beginScene(controller.getCamera());

            controller.onUpdate(dt);

            Sirius::Renderer3D::drawEmissionCube({ptLight.pos, 500.f});
//            Sirius::Renderer3D::drawModel(suzanne);
//            Sirius::Renderer3D::drawModel(cubeModel, {4.f, 0.f, 0.f}, Sirius::Vec3(1.f), true);
            Sirius::Renderer3D::drawModel(model);

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
