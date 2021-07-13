
#include <Sirius.hpp>
#include <Sirius/Core/EntryPoint.hpp>

class ExampleLayer: public Sirius::Layer
{
    private:

        Sirius::Ref<Sirius::Texture2D> diffuse, specular;
        Sirius::Light light {{1.5f, -1.f, 1.5f}};

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

            Sirius::Renderer3D::setLightSource(light);
            Sirius::Renderer3D::drawCube({}, {1.f, 1.f, 1.f}, {0.8f, 0.3f, 0.2f});
            Sirius::Renderer3D::drawCube({2.f, -1.f, -1.f}, {1.f, 1.f, 1.f}, Sirius::Material(diffuse, specular, 32.f));

            Sirius::Renderer3D::endScene();
        }

        void onImGuiRender() override
        {
            ImGui::SliderFloat3("Light position", &light.pos.x, -2.f, 2.f);
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
