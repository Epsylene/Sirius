
#include "Renderer.hpp"

#include "Renderer2D.hpp"
#include "Renderer3D.hpp"

#include "../UI/Scene.hpp"

#include "../Core/Application.hpp"

namespace Sirius
{
    Scope<Renderer::SceneData> Renderer::sceneData = std::make_unique<Renderer::SceneData>();

    const Mat3 Kernel::Edges {1.f,  1.f, 1.f,
                              1.f, -8.f, 1.f,
                              1.f,  1.f, 1.f};
    const Mat3 Kernel::Sharpen { 0.f, -1.f,  0.f,
                                -1.f,  5.f, -1.f,
                                 0.f, -1.f,  0.f};
    const Mat3 Kernel::Blur {1.f/16.f, 2.f/16.f, 1.f/16.f,
                             2.f/16.f, 4.f/16.f, 2.f/16.f,
                             1.f/16.f, 2.f/16.f, 1.f/16.f};

    void Renderer::init()
    {
        RenderCommand::init();
        Renderer2D::init();
        Renderer3D::init();

        BufferLayout layout = {{DataType::Mat4,   "viewProj"},
                               {DataType::Float3, "viewDir"},
                               {DataType::Float3, "cameraPos"}};
        sceneData->cameraData = std::make_shared<UniformBuffer>(layout, 0);

        auto& window = Application::get().getWindow();
        sceneData->renderFBO = std::make_unique<FrameBuffer>(window.getWidth(), window.getHeight());
        sceneData->postRenderFBO = std::make_unique<FrameBuffer>(window.getWidth(), window.getHeight());

        float vertices[] = { -1.f,  1.f,  0.f, 1.f,
                             -1.f, -1.f,  0.f, 0.f,
                              1.f,  1.f,  1.f, 1.f,
                              1.f, -1.f,  1.f, 0.f };
        std::vector<uint32_t> indices = {0, 1, 2, 2, 1, 3};

        auto vb = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
        vb->setLayout({{DataType::Float2, "a_position"},
                       {DataType::Float2, "a_texture"}});
        auto ib = std::make_shared<IndexBuffer>(indices);

        sceneData->renderQuad = std::make_shared<VertexArray>(vb, ib);

        sceneData->postprocess = std::make_shared<Shader>(Sirius::resPath/"shaders/postprocess.glsl");
    }

    void Renderer::applyPostProcessing(const Scope<FrameBuffer>& frameBuffer,
                                       const Matrix4f& transform)
    {
        sceneData->postprocess->bind();
        sceneData->renderQuad->bind();
        frameBuffer->colorBuffer.bind(0);
        sceneData->postprocess->uploadUniformInt("u_screenTex", 0);
        sceneData->postprocess->uploadUniformMat4("u_transform", transform);
        sceneData->postprocess->uploadUniformFloat("u_separator", Scene::properties.ppSeparator);

        sceneData->renderQuad->bind();
        RenderCommand::drawIndexed(sceneData->renderQuad, Primitives::TRIANGLES);
    }

    void Renderer::setPostProcessing(PostProcessingFlags flags)
    {
        sceneData->postprocess->bind();
        sceneData->postprocess->uploadUniformInt("u_ppFlag", (int)flags);

        switch (flags)
        {
            case EDGES:
                sceneData->postprocess->uploadUniformMat3("u_kernel", Kernel::Edges);
                break;

            case SHARPEN:
                sceneData->postprocess->uploadUniformMat3("u_kernel", Kernel::Sharpen);
                break;

            case BLUR:
                sceneData->postprocess->uploadUniformMat3("u_kernel", Kernel::Blur);
                break;
        }

        sceneData->postprocess->unbind();
    }

    void Renderer::preRender()
    {
        sceneData->renderFBO->bind();
        RenderCommand::setDepthTest(true);
        RenderCommand::setClearColor(Scene::properties.background);
        RenderCommand::clear();
        RenderCommand::setWireframeMode(Scene::properties.wireframe);
    }

    void Renderer::postRender()
    {
        RenderCommand::setWireframeMode(false);
        sceneData->renderFBO->unbind();
        RenderCommand::setDepthTest(false);
        RenderCommand::setClearColor(Color::White);
        RenderCommand::clear(COLOR_BUFFER);

        sceneData->postRenderFBO->bind();
        Renderer::setPostProcessing(Scene::properties.ppFlag);
        applyPostProcessing(sceneData->renderFBO);
        sceneData->postRenderFBO->unbind();
    }
}