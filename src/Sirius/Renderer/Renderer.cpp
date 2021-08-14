
#include "Sirius/Renderer/Renderer.hpp"

#include "Sirius/Renderer/Renderer2D.hpp"
#include "Sirius/Renderer/Renderer3D.hpp"

#include "Sirius/UI/Scene.hpp"

#include "Sirius/Core/Application.hpp"

namespace Sirius
{
    Scope<Renderer::SceneData> Renderer::sceneData = std::make_unique<Renderer::SceneData>();

    const Mat3 Kernel::Edges {1.f,  1.f, 1.f,
                              1.f, -8.f, 1.f,
                              1.f,  1.f, 1.f};
    const Mat3 Kernel::Sharpen {-1.f, -1.f, -1.f,
                                -1.f,  9.f, -1.f,
                                -1.f, -1.f, -1.f};
    const Mat3 Kernel::Blur {1.f/16.f, 2.f/16.f, 1.f/16.f,
                             2.f/16.f, 4.f/16.f, 2.f/16.f,
                             1.f/16.f, 2.f/16.f, 1.f/16.f};

    void Renderer::init()
    {
        RenderCommand::init();
        Renderer2D::init();
        Renderer3D::init();

        auto& window = Application::get().getWindow();
        sceneData->preRenderFBO = std::make_unique<FrameBuffer>(window.getWidth(), window.getHeight());
        sceneData->postRenderFBO = std::make_unique<FrameBuffer>(window.getWidth(), window.getHeight());

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

    void Renderer::applyPostProcessing(const Scope<FrameBuffer>& frameBuffer,
                                       const Matrix4f& transform)
    {
        sceneData->postprocess->bind();
        sceneData->quad->bind();
        frameBuffer->colorBuffer.bind(0);
        sceneData->postprocess->uploadUniformInt("u_screenTex", 0);
        sceneData->postprocess->uploadUniformMat4("u_transform", transform);

        sceneData->quad->bind();
        RenderCommand::drawIndexed(sceneData->quad);
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
        sceneData->preRenderFBO->bind();
        RenderCommand::setDepthTest(true);
        RenderCommand::setClearColor(Scene::properties.background);
        RenderCommand::clear();
        RenderCommand::setWireframeMode(Scene::properties.wireframe);
    }

    void Renderer::postRender()
    {
        RenderCommand::setWireframeMode(false);
        sceneData->preRenderFBO->unbind();
        RenderCommand::setDepthTest(false);
        RenderCommand::setClearColor(Color::White);
        RenderCommand::clear(COLOR_BUFFER);
        Renderer::setPostProcessing(Scene::properties.ppFlag);

        sceneData->postRenderFBO->bind();
        applyPostProcessing(sceneData->preRenderFBO);
        sceneData->postRenderFBO->unbind();
    }
}