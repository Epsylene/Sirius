
#include "Sirius/Renderer/Renderer.h"

namespace Sirius
{
    void Renderer::beginScene()
    {
    }

    void Renderer::endScene()
    {

    }

    void Renderer::submit(std::shared_ptr<Shader>& shader,
                          std::shared_ptr<VertexArray>& vertexArray)
    {
        shader->bind();

        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }
}