
#include <Sirius.hpp>
#include <Sirius/Core/EntryPoint.hpp>

class ExampleLayer: public Sirius::Layer
{
    private:

        Sirius::Ref<Sirius::Texture2D> texture;
        Sirius::Light light {{1.5f, 0.f, -1.5f}};

        Sirius::CameraController3D controller {{1.f, 1.f, 1.f}};

    public:

        ExampleLayer(): Layer("Example")
        {
            texture = std::make_shared<Sirius::Texture2D>("../../app/assets/textures/sirius.jpg");
        }

        void onUpdate(Sirius::Timestep dt) override
        {
            Sirius::RenderCommand::setClearColor({0.003, 0.006, 0.078, 1});
            Sirius::Renderer3D::beginScene(controller.getCamera());

            controller.onUpdate(dt);

            Sirius::Renderer3D::setLightSource(light);
            Sirius::Renderer3D::drawCube({}, {1.f, 1.f, 1.f}, Sirius::Material({1.f}, {0.8f, 0.3f, 0.2f}, {0.2f}));
            Sirius::Renderer3D::drawCube(light.pos, {1.f, 1.f, 1.f}, texture);

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
