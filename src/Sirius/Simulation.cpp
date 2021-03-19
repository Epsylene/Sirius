
#include "Sirius/Simulation.h"

#include <memory>

namespace Sirius
{
    Simulation* Simulation::instance = nullptr;

    Simulation::Simulation()
    {
        instance = this;

        window = std::unique_ptr<Window>(Window::create());
        window->setEventCallback([this](Event& event) { onEvent(event); });

        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);

        float vertices[3 * 3] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f,  0.5f, 0.0f
        };

        vertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        unsigned int indices[3] = {0, 1, 2};
        indexBuffer = std::make_unique<IndexBuffer>(indices, std::size(indices));

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

        shader = std::make_unique<Shader>(vertexSrc, fragmentSrc);
    }

    void Simulation::onEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowCloseEvent>([this](WindowCloseEvent& event) { return onWindowClose(event); });

        std::cout << event << "\n";
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
            glBindVertexArray(vertexArray);
            glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);

            window->onUpdate();
        }
    }
}


