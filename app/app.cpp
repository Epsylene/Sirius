
#include <Sirius.hpp>
#include <Sirius/Core/EntryPoint.hpp>

class ExampleLayer: public Sirius::Layer
{
    private:

        Sirius::PointLight ptLight {{2.f, 0.f, 0.f}, 60.f};
        Sirius::DirectionalLight dirLight {{1.f, 0.f, 0.f}};

        Sirius::Ref<Sirius::Skybox> skybox;
        Sirius::Ref<Sirius::Model> cylinder;

    public:

        ExampleLayer(): Layer("Example")
        {
            Sirius::Renderer3D::setDirectionalLight(dirLight);
            Sirius::Renderer3D::addPointLight(ptLight);
            Sirius::Renderer3D::addPointLight({{2.f, 5.f, 3.f}, 500.f});

            std::array<std::string, 6> paths = {"../../app/res/textures/skybox/right.jpg",
                                                "../../app/res/textures/skybox/left.jpg",
                                                "../../app/res/textures/skybox/top.jpg",
                                                "../../app/res/textures/skybox/bottom.jpg",
                                                "../../app/res/textures/skybox/front.jpg",
                                                "../../app/res/textures/skybox/back.jpg"};

            skybox = std::make_shared<Sirius::Skybox>(paths);
            Sirius::Scene::setSkybox(skybox);

            cylinder = std::make_shared<Sirius::Model>("../../app/res/meshes/cylinder/cylinder.obj");
        }

        void onUpdate(Sirius::Timestep dt) override
        {
            Sirius::Renderer3D::drawEmissionCube({{2.f, 0.f, 1.f}, 500.f});
            Sirius::Scene::drawModel(cylinder);
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
