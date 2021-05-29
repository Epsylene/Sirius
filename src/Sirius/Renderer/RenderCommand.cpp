
#include "Sirius/Renderer/RenderCommand.h"

namespace Sirius
{
    void RenderCommand::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderCommand::setClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void RenderCommand::drawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
    {
        glDrawElements(GL_TRIANGLES,
                       vertexArray->getIndexBuffer()->getCount(),
                       GL_UNSIGNED_INT,
                       nullptr);
    }
}