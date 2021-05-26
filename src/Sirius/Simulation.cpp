
#include "Sirius/Simulation.h"

namespace Sirius
{
    Simulation* Simulation::instance = nullptr;

    Simulation::Simulation()
    {
        SRS_CORE_ASSERT(!instance, "Application already exists")
        instance = this;

        Log::init();

        window = std::unique_ptr<Window>(Window::create());
        window->setEventCallback([this](Event& event) { onEvent(event); });

        float vertices[3 * 3] = {
                -0.5f, -0.5f, 0.0f,
                 0.5f, -0.5f, 0.0f,
                 0.0f,  0.5f, 0.0f
        };

        vertexBuffer = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));

        BufferLayout layout {
                { ShaderDataType::Float3, "position" }
        };

        vertexBuffer->setLayout(layout);
        vertexArray = std::make_shared<VertexArray>();
        vertexArray->addVertexBuffer(vertexBuffer);

        unsigned int indices[3] = {0, 1, 2};
        indexBuffer = std::make_shared<IndexBuffer>(indices, std::size(indices));
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

        shader = std::make_shared<Shader>(vertexSrc, fragmentSrc);
    }

    void Simulation::onEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowCloseEvent>([this](WindowCloseEvent& event) { return onWindowClose(event); });
    }

    bool Simulation::onWindowClose(WindowCloseEvent& event)
    {
        running = false;
        return true;
    }

    void Simulation::run()
    {
        while(running)
        {
            glClearColor(0.12, 0.12, 0.12, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            shader->bind();
            vertexArray->bind();
            glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);

            window->onUpdate();
        }
    }
}


