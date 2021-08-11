
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

        float vertices[] = { -1.f,  1.f,  0.f, 1.f,
                             -1.f, -1.f,  0.f, 0.f,
                              1.f,  1.f,  1.f, 1.f,
                              1.f, -1.f,  1.f, 0.f };
        std::vector<uint32_t> indices = {0, 1, 2, 2, 1, 3};

        auto vb = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
        vb->setLayout({ {ShaderDataType::Float2, "a_position"},
                        {ShaderDataType::Float2, "a_texture"} });
        auto ib = std::make_shared<IndexBuffer>(indices);

        sceneData->quad = std::make_shared<VertexArray>(vb, ib);

        sceneData->postprocess = std::make_shared<Shader>("../../app/res/shaders/postprocess.glsl");
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

    void Renderer::updateFrameBuffer(const Scope<FrameBuffer>& frameBuffer)
    {
        sceneData->postprocess->bind();
        sceneData->quad->bind();
        frameBuffer->colorBuffer.bind(0);
        sceneData->postprocess->uploadUniformInt("u_screenTex", 0);
        RenderCommand::drawIndexed(sceneData->quad);
    }
}