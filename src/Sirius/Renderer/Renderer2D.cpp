
#include "Sirius/Renderer/Renderer2D.hpp"

#include "Sirius/Renderer/Utils/Shader.hpp"
#include "Sirius/Renderer/RenderCommand.hpp"
#include "Sirius/Renderer/Renderer.hpp"

namespace Sirius
{
    struct Renderer2DStorage
    {
        Ref<VertexArray> quadVA;
        Ref<VertexArray> circleVA;

        ShaderLibrary shaderLib;
    };

    static Scope<Renderer2DStorage> data;

    void generateQuadVA()
    {
        float quadVtx[] = { -1.f,  1.f,  0.f, 1.f,
                            -1.f, -1.f,  0.f, 0.f,
                            1.f,  1.f,  1.f, 1.f,
                            1.f, -1.f,  1.f, 0.f };
        std::vector<uint32_t> quadIdx = {0, 1, 2, 2, 1, 3};

        auto vb = std::make_shared<VertexBuffer>(quadVtx, sizeof(quadVtx));
        vb->setLayout({{DataType::Float2, "a_position"},
                       {DataType::Float2, "a_texture"}});
        auto ib = std::make_shared<IndexBuffer>(quadIdx);

        data->quadVA = std::make_shared<VertexArray>(vb, ib);
    }

    void generateCircleVA()
    {
        std::vector<float> circleVB;
        std::vector<uint32_t> circleIB;
        circleVB.push_back(0);
        circleVB.push_back(0);
        for (int i = 99; i > 69; i--)
        {
            circleVB.push_back((float)i / 99.f);
            circleVB.push_back(std::sqrt(1.f - (float)(i*i) / (99.f * 99.f)));
        }
        for (int i = circleVB.size() - 1; i > 2; i-=2)
        {
            circleVB.push_back(circleVB[i]);
            circleVB.push_back(circleVB[i - 1]);
        }
        for (int i = circleVB.size() - 1; i > 0; i-=2)
        {
            circleVB.push_back(-circleVB[i - 1]);
            circleVB.push_back(circleVB[i]);
        }
        for (int i = circleVB.size() - 1; i > 0; i-=2)
        {
            circleVB.push_back(circleVB[i - 1]);
            circleVB.push_back(-circleVB[i]);
        }

        for (int i = 0; i < 244; i++)
        {
            circleIB.push_back(0);
            circleIB.push_back(i + 1);
            circleIB.push_back(i + 2);
        }

        auto vb = std::make_shared<VertexBuffer>(circleVB.data(), circleVB.size() * sizeof(float));
        vb->setLayout({{DataType::Float2, "a_position"}});
        auto ib = std::make_shared<IndexBuffer>(circleIB);
        data->circleVA = std::make_shared<VertexArray>(vb, ib);
    }

    void Renderer2D::init()
    {
        data = std::make_unique<Renderer2DStorage>();
        generateQuadVA();
        generateCircleVA();

        data->shaderLib.load("../../app/res/shaders/emission.glsl");
    }

    void Renderer2D::shutdown()
    {
        data.reset();
    }

    void Renderer2D::beginScene(const Camera2D& camera)
    {
        Renderer::sceneData->cameraData->uploadMat4("viewProj", camera.getViewProjMatrix());
        Renderer::sceneData->cameraData->uploadFloat3("viewDir", camera.getDirection());
        Renderer::sceneData->cameraData->uploadFloat3("cameraPos", camera.getPosition());
    }

    void Renderer2D::endScene()
    {}

    void Renderer2D::drawQuad(const Vec2& pos, const Vec2& size,
                              const Color& color)
    {
        auto& emissionShader = data->shaderLib["emission"];

        emissionShader->bind();
        emissionShader->uploadUniformFloat3("u_color", color);

        Mat4 transform = translate({pos}) * scale({size.x, size.y, 1.f});
        emissionShader->uploadUniformMat4("u_transform", transform);

        data->quadVA->bind();
        RenderCommand::drawIndexed(data->quadVA);
    }

    void Renderer2D::drawCircle(const Vec2& pos, const Vec2& size, const Color& color)
    {
        auto& emissionShader = data->shaderLib["emission"];

        emissionShader->bind();
        emissionShader->uploadUniformFloat3("u_color", color);

        Mat4 transform = translate({pos}) * scale({size.x, size.y, 1.f});
        emissionShader->uploadUniformMat4("u_transform", transform);

        data->circleVA->bind();
        RenderCommand::drawIndexed(data->circleVA);
    }
}