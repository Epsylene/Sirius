
#include "Sirius/Renderer/RenderCommand.h"

#include <glad/glad.h>

namespace Sirius
{
    void RenderCommand::init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void RenderCommand::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderCommand::setClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void RenderCommand::setViewport(uint32_t x, uint32_t y, uint32_t width,
                                    uint32_t height)
    {
        glViewport(x, y, width, height);
    }

    void RenderCommand::drawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
    {
        glDrawElements(GL_TRIANGLES,
                       vertexArray->getIndexBuffer()->getCount(),
                       GL_UNSIGNED_INT,
                       nullptr);
    }
}