
#include "Sirius/Renderer/Renderer.h"

namespace Sirius
{
    std::unique_ptr<Renderer::SceneData> Renderer::sceneData = std::make_unique<Renderer::SceneData>();

    void Renderer::beginScene(Camera& camera)
    {
        sceneData->viewProjMatrix = camera.getViewProjMatrix();
    }

    void Renderer::endScene()
    {

    }

    void Renderer::submit(std::shared_ptr<Shader>& shader,
                          std::shared_ptr<VertexArray>& vertexArray,
                          const glm::mat4& transform)
    {
        shader->bind();
        shader->uploadUniformMat4("viewProj", sceneData->viewProjMatrix);
        shader->uploadUniformMat4("transform", transform);

        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }

}