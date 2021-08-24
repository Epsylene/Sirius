
#include "Sirius/Renderer/Renderer2D.hpp"

#include "Sirius/Renderer/Utils/Shader.hpp"
#include "Sirius/Renderer/RenderCommand.hpp"

namespace Sirius
{
    struct Renderer2DStorage
    {
        Ref<VertexArray> quadVA;
        Ref<Shader> flatColorShader;
        Ref<Shader> emissionShader;
        Ref<Shader> textureShader;
    };

    static Scope<Renderer2DStorage> data;

    void Renderer2D::init()
    {
        data = std::make_unique<Renderer2DStorage>();

        data->quadVA = std::make_shared<VertexArray>();

        float vertices[5 * 4] = {
                -0.5f, -0.5f, 0.0f, 0.f, 0.f,
                -0.5f,  0.5f, 0.0f, 0.f, 1.f,
                 0.5f,  0.5f, 0.0f, 1.f, 1.f,
                 0.5f, -0.5f, 0.0f, 1.f, 0.f
        };

        auto vertexBuffer = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));

        vertexBuffer->setLayout({
            {DataType::Float3, "a_position" },
            {DataType::Float2, "a_texCoord" }});
        data->quadVA->addVertexBuffer(vertexBuffer);

        unsigned int indices[6] = {0, 1, 2, 2, 3, 0};
        auto indexBuffer = std::make_shared<IndexBuffer>(indices, std::size(indices));
        data->quadVA->setIndexBuffer(indexBuffer);

        data->flatColorShader = std::make_shared<Shader>("../../app/res/shaders/flat_color.glsl");
        data->textureShader = std::make_shared<Shader>("../../app/res/shaders/texture.glsl");
        data->textureShader->bind();
        data->textureShader->uploadUniformInt("u_texture", 0);
        data->emissionShader = std::make_shared<Shader>("../../app/res/shaders/emission.glsl");
    }

    void Renderer2D::shutdown()
    {
        data.reset();
    }

    void Renderer2D::beginScene(const Camera2D& camera)
    {
        data->flatColorShader->bind();
        data->flatColorShader->uploadUniformMat4("u_viewProj", camera.getViewProjMatrix());

        data->textureShader->bind();
        data->textureShader->uploadUniformMat4("u_viewProj", camera.getViewProjMatrix());

        data->emissionShader->bind();
        data->emissionShader->uploadUniformMat4("u_viewProj", camera.getViewProjMatrix());
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
        data->emissionShader->bind();
        data->emissionShader->uploadUniformFloat4("u_color", color);

        Mat4 transform = translate(pos) * scale({size.x, size.y, 1.f});
        data->emissionShader->uploadUniformMat4("u_transform", transform);

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
        data->textureShader->bind();

        Mat4 transform = translate(pos) * scale({size.x, size.y, 1.f});
        data->textureShader->uploadUniformMat4("u_transform", transform);

        texture->bind();

        data->quadVA->bind();
        RenderCommand::drawIndexed(data->quadVA, Primitives::TRIANGLES);
    }
}