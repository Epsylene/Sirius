
#include "Sirius/Renderer/Renderer.h"

namespace Sirius
{
    std::unique_ptr<Renderer::SceneData> Renderer::sceneData = std::make_unique<Renderer::SceneData>();

    void Renderer::beginScene(Camera& camera)
    {
        sceneData->viewProjMatrix = camera.getViewProjMatrix();
    }

    void Renderer::endScene()
    {}

    void Renderer::onWindowResize(uint32_t width, uint32_t height)
    {
        RenderCommand::setViewport(0, 0, width, height);
    }

    void Renderer::submit(const std::shared_ptr<Shader>& shader,
                          const std::shared_ptr<VertexArray>& vertexArray,
                          const glm::mat4& transform)
    {
        shader->bind();
        shader->uploadUniformMat4("u_viewProj", sceneData->viewProjMatrix);
        shader->uploadUniformMat4("u_transform", transform);

        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }

}