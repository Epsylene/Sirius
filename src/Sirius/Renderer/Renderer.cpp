
#include "Sirius/Renderer/Renderer.hpp"

#include "Sirius/Renderer/Renderer2D.hpp"
#include "Sirius/Renderer/Renderer3D.hpp"

namespace Sirius
{
    Scope<Renderer::SceneData> Renderer::sceneData = std::make_unique<Renderer::SceneData>();

    const Mat3 Kernel::Edges {1.f,  1.f, 1.f,
                              1.f, -8.f, 1.f,
                              1.f,  1.f, 1.f};
    const Mat3 Kernel::Sharpen {-1.f, -1.f, -1.f,
                                -1.f,  8.f, -1.f,
                                -1.f, -1.f, -1.f};
    const Mat3 Kernel::Blur {1.f/16.f, 2.f/16.f, 1.f/16.f,
                             2.f/16.f, 4.f/16.f, 2.f/16.f,
                             1.f/16.f, 2.f/16.f, 1.f/16.f};

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

    void Renderer::onWindowResize(uint32_t width, uint32_t height)
    {
        RenderCommand::setViewport(0, 0, width, height);
    }

    void Renderer::applyPostProcessing(const Scope <FrameBuffer>& frameBuffer,
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

        sceneData->postprocess->uploadUniformBool("u_ppFlags.none", false);

        switch (flags)
        {
            case NONE:
                sceneData->postprocess->uploadUniformBool("u_ppFlags.none", true);
                break;

            case INVERSION:
                sceneData->postprocess->uploadUniformBool("u_ppFlags.inversion", true);
                break;

            case GRAYSCALE:
                sceneData->postprocess->uploadUniformBool("u_ppFlags.grayscale", true);
                break;

            case EDGES:
                sceneData->postprocess->uploadUniformBool("u_ppFlags.kernel", true);
                sceneData->postprocess->uploadUniformMat3("u_kernel", Kernel::Edges);
                break;

            case SHARPEN:
                sceneData->postprocess->uploadUniformBool("u_ppFlags.kernel", true);
                sceneData->postprocess->uploadUniformMat3("u_kernel", Kernel::Sharpen);
                break;

            case BLUR:
                sceneData->postprocess->uploadUniformBool("u_ppFlags.kernel", true);
                sceneData->postprocess->uploadUniformMat3("u_kernel", Kernel::Blur);
                break;
        }

        sceneData->postprocess->unbind();
    }
}