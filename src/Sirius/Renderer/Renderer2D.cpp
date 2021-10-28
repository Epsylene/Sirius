
#include "Sirius/Renderer/Renderer2D.hpp"

#include "Sirius/Renderer/Utils/Shader.hpp"
#include "Sirius/Renderer/RenderCommand.hpp"
#include "Sirius/Renderer/Renderer.hpp"

namespace Sirius
{
    struct Renderer2DStorage
    {
        Ref<VertexArray> quadVA;

        ShaderLibrary shaderLib;
    };

    static Scope<Renderer2DStorage> data;

    void Renderer2D::init()
    {
        data = std::make_unique<Renderer2DStorage>();

        float vertices[] = { -1.f,  1.f,  0.f, 1.f,
                             -1.f, -1.f,  0.f, 0.f,
                              1.f,  1.f,  1.f, 1.f,
                              1.f, -1.f,  1.f, 0.f };
        std::vector<uint32_t> indices = {0, 1, 2, 2, 1, 3};

        auto vb = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
        vb->setLayout({{DataType::Float2, "a_position"},
                       {DataType::Float2, "a_texture"}});
        auto ib = std::make_shared<IndexBuffer>(indices);

        data->quadVA = std::make_shared<VertexArray>(vb, ib);

        data->shaderLib.load("../../app/res/shaders/flat_color.glsl");
        data->shaderLib.load("../../app/res/shaders/texture.glsl");
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
        drawQuad({pos.x, pos.y, 0.f}, size, color);
    }

    void Renderer2D::drawQuad(const Vec3& pos, const Vec2& size,
                              const Color& color)
    {
        auto& emissionShader = data->shaderLib["emission"];

        emissionShader->bind();
        emissionShader->uploadUniformFloat3("u_color", color);

        Mat4 transform = translate(pos) * scale({size.x, size.y, 1.f});
        emissionShader->uploadUniformMat4("u_transform", transform);

        data->quadVA->bind();
        RenderCommand::drawIndexed(data->quadVA, Primitives::TRIANGLES);
    }

    void Renderer2D::drawQuad(const Vec2& pos, const Vec2& size,
                              const Ref<Texture2D>& texture)
    {
        drawQuad({pos.x, pos.y, 0.f}, size, texture);
    }

    void Renderer2D::drawQuad(const Vec3& pos, const Vec2& size,
                              const Ref<Texture2D>& texture)
    {
        auto& textureShader = data->shaderLib["texture"];
        textureShader->bind();

        Mat4 transform = translate(pos) * scale({size.x, size.y, 1.f});
        textureShader->uploadUniformMat4("u_transform", transform);

        texture->bind();

        data->quadVA->bind();
        RenderCommand::drawIndexed(data->quadVA, Primitives::TRIANGLES);
    }
}