
#include <Sirius.hpp>
#include <Sirius/Core/EntryPoint.hpp>

class ExampleLayer: public Sirius::Layer
{
    private:

        Sirius::Ref<Sirius::Texture2D> diffuse, specular;
        Sirius::PointLight ptLight {{1.5f, -1.f, 1.5f}, 50.f};
        Sirius::DirectionalLight dirLight {{1.f, -1.f, 1.f}};
        Sirius::Spotlight spotLight {{0.f, 0.f, 0.f}, {1.f, 0.f, 0.f}, 60.f, 60.f, 0.1f};

        Sirius::CameraController3D controller {{1.f, 1.f, 1.f}};

    public:

        ExampleLayer(): Layer("Example")
        {
            diffuse = std::make_shared<Sirius::Texture2D>("../../app/assets/textures/container.png");
            specular = std::make_shared<Sirius::Texture2D>("../../app/assets/textures/container_specular.png");
        }

        void onUpdate(Sirius::Timestep dt) override
        {
            Sirius::RenderCommand::setClearColor({0.003, 0.006, 0.078, 1});
            Sirius::Renderer3D::beginScene(controller.getCamera());

            controller.onUpdate(dt);

//            Sirius::Renderer3D::addPointLight(ptLight);
//            Sirius::Renderer3D::addDirectionalLight(dirLight);
            Sirius::Renderer3D::addSpotlight(spotLight);

            for (int i = 0; i < 10; ++i)
            {
                for (int j = 0; j < 10; ++j)
                {
                    Sirius::Renderer3D::drawCube({-5.f, i - 5.f, j - 5.f}, Sirius::Vec3(1.f), Sirius::Material(diffuse, specular, 32.f));
                }
            }
//            Sirius::Renderer3D::drawCube({-1.f, -1.f, -1.f}, {1.f, 1.f, 1.f}, Sirius::Material(diffuse, specular, 32.f));
//            Sirius::Renderer3D::drawCube({4.f, -1.f, -1.f}, {1.f, 1.f, 1.f}, Sirius::Material(diffuse, specular, 32.f));

            Sirius::Renderer3D::endScene();
        }

        void onImGuiRender() override
        {
            ImGui::SliderFloat3("Light direction", &spotLight.dir.x, -2.f, 2.f);
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
            pushLayer(new ExampleLayer());
        }
};

std::unique_ptr<Sirius::Application> Sirius::createApplication()
{
    return std::make_unique<Test>();
}
