
#include "Sirius.h"

class ExampleLayer: public Sirius::Layer
{
    private:

        std::shared_ptr<Sirius::Shader> shader;
        std::shared_ptr<Sirius::VertexArray> vertexArray;

    public:

        ExampleLayer(): Layer("Example")
        {
            float vertices[3 * 3] = {
                    -0.5f, -0.5f, 0.0f,
                    0.5f, -0.5f, 0.0f,
                    0.0f,  0.5f, 0.0f
            };

            auto vertexBuffer = std::make_shared<Sirius::VertexBuffer>(vertices, sizeof(vertices));

            Sirius::BufferLayout layout {
                    { Sirius::ShaderDataType::Float3, "position" }
            };

            vertexBuffer->setLayout(layout);
            vertexArray = std::make_shared<Sirius::VertexArray>();
            vertexArray->addVertexBuffer(vertexBuffer);

            unsigned int indices[3] = {0, 1, 2};
            auto indexBuffer = std::make_shared<Sirius::IndexBuffer>(indices, std::size(indices));
            vertexArray->setIndexBuffer(indexBuffer);

            std::string vertexSrc = R"(
                #version 330 core

                layout(location = 0) in vec3 position;

                out vec3 vPos;

                void main()
                {
                    vPos = position;
                    gl_Position = vec4(position, 1.0);
                }
            )";

            std::string fragmentSrc = R"(
                #version 330 core

                layout(location = 0) out vec4 color;

                in vec3 vPos;

                void main()
                {
                    color = vec4(vPos + 0.5, 1.0);
                }
            )";

            shader = std::make_shared<Sirius::Shader>(vertexSrc, fragmentSrc);
        }

        void onUpdate() override
        {
            Sirius::Renderer::beginScene();
            Sirius::Renderer::submit(shader, vertexArray);
            Sirius::Renderer::endScene();
        }

        void onImGuiRender() override {}
        void onEvent(Sirius::Event& event) override {}
};

class Test: public Sirius::Simulation
{
    public:

        Test()
        {
            pushLayer(new ExampleLayer());
        }
};

Sirius::Simulation* Sirius::createSimulation()
{
    return new Test();
}
