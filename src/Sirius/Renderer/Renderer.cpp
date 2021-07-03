
#include "Sirius/Renderer/Renderer.hpp"

#include "Sirius/Renderer/Renderer2D.hpp"
#include "Sirius/Renderer/Renderer3D.hpp"

namespace Sirius
{
    Scope<Renderer::SceneData> Renderer::sceneData = std::make_unique<Renderer::SceneData>();

    void Renderer::init()
    {
        RenderCommand::init();
        Renderer2D::init();
        Renderer3D::init();
    }

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

    void Renderer::submit(const Ref<Shader>& shader,
                          const Ref<VertexArray>& vertexArray,
                          const Mat4& transform)
    {
        shader->bind();
        shader->uploadUniformMat4("u_viewProj", sceneData->viewProjMatrix);
        shader->uploadUniformMat4("u_transform", transform);
        shader->uploadUniformFloat4("u_color", {1.f, 1.f, 1.f, 1.f});

        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }

}