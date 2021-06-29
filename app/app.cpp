
#include <Sirius.h>
#include <Sirius/Core/EntryPoint.h>

class ExampleLayer: public Sirius::Layer
{
    private:

        Sirius::ShaderLibrary shaderLib;
        std::shared_ptr<Sirius::VertexArray> vertexArray;
        Sirius::Texture2D texture;

        Sirius::CameraController3D controller;

    public:

        ExampleLayer(): Layer("Example"), texture("../../app/assets/textures/sirius.jpg")
        {
            vertexArray = std::make_shared<Sirius::VertexArray>();

            float vertices[5 * 4] = {
                    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                    -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
                     0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
                     0.5f, -0.5f, 0.0f, 1.0f, 0.0f
            };

            auto vertexBuffer = std::make_shared<Sirius::VertexBuffer>(vertices, sizeof(vertices));

            Sirius::BufferLayout layout {
                    { Sirius::ShaderDataType::Float3, "a_position" },
                    { Sirius::ShaderDataType::Float2, "a_texCoord" }
            };

            vertexBuffer->setLayout(layout);
            vertexArray->addVertexBuffer(vertexBuffer);

            unsigned int indices[6] = {0, 1, 2, 2, 3, 0};
            auto indexBuffer = std::make_shared<Sirius::IndexBuffer>(indices, std::size(indices));
            vertexArray->setIndexBuffer(indexBuffer);

            shaderLib.load("../../app/assets/shaders/blue.glsl");
            shaderLib.load("../../app/assets/shaders/texture.glsl");

            shaderLib.get("texture")->bind();
            shaderLib.get("texture")->uploadUniformFloat("u_texture", 0);
        }

        void onUpdate(Sirius::Timestep dt) override
        {
            Sirius::RenderCommand::setClearColor({0.003, 0.006, 0.078, 1});
            Sirius::Renderer::beginScene(controller.getCamera());

            controller.onUpdate(dt);

            auto blueShader = shaderLib.get("blue");
            auto texShader = shaderLib.get("texture");

            texture.bind();

            Sirius::Renderer::submit(texShader, vertexArray);

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
