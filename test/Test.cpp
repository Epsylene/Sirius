
#include "Sirius.h"

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer: public Sirius::Layer
{
    private:

        Sirius::ShaderLibrary shaderLib;
        std::shared_ptr<Sirius::VertexArray> vertexArray;

        Sirius::CameraController2D controller;

    public:

        ExampleLayer(): Layer("Example")
        {
            float vertices[3 * 4] = {
                    -0.5f, -0.5f, 0.0f,
                    -0.5f,  0.5f, 0.0f,
                     0.5f,  0.5f, 0.0f,
                     0.5f, -0.5f, 0.0f
            };

            auto vertexBuffer = std::make_shared<Sirius::VertexBuffer>(vertices, sizeof(vertices));

            Sirius::BufferLayout layout {
                    { Sirius::ShaderDataType::Float3, "position" }
            };

            vertexBuffer->setLayout(layout);
            vertexArray = std::make_shared<Sirius::VertexArray>();
            vertexArray->addVertexBuffer(vertexBuffer);

            unsigned int indices[6] = {0, 1, 2, 2, 3, 0};
            auto indexBuffer = std::make_shared<Sirius::IndexBuffer>(indices, std::size(indices));
            vertexArray->setIndexBuffer(indexBuffer);

            shaderLib.load("../../test/assets/shaders/rainbow.glsl");
            shaderLib.load("../../test/assets/shaders/blue.glsl");
        }

        void onUpdate(Sirius::Timestep dt) override
        {
            Sirius::Renderer::beginScene(controller.getCamera());

            controller.onUpdate(dt);

            auto rainbowShader = shaderLib.get("rainbow");
            auto blueShader = shaderLib.get("blue");

            Sirius::Renderer::submit(rainbowShader, vertexArray, glm::mat4(glm::scale(glm::mat4(1.f), glm::vec3(1.f))));

            Sirius::Renderer::endScene();
        }

        void onImGuiRender() override {}

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

Sirius::Application* Sirius::createSimulation()
{
    return new Test();
}
