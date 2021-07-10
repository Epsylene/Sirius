
#include <Sirius/Renderer/Material.hpp>
#include "Sirius/Renderer/Renderer3D.hpp"

#include "Sirius/Renderer/RenderCommand.hpp"
#include "Sirius/Renderer/Shader.hpp"

namespace Sirius
{
    struct Renderer3DStorage
    {
        Vec3 lightPos;
        Ref<VertexArray> cubeVA;
        Ref<Shader> flatColorShader;
        Ref<Shader> textureShader;
    };

    static Scope<Renderer3DStorage> data;

    void Renderer3D::init()
    {
        data = std::make_unique<Renderer3DStorage>();

        data->cubeVA = std::make_shared<VertexArray>();

        float vertices[8 * 4 * 6] = {
                -0.5f, -0.5f, -0.5f,   0.f,  0.f, -1.f,   0.f, 0.f,
                 0.5f, -0.5f, -0.5f,   0.f,  0.f, -1.f,   0.f, 1.f,
                 0.5f,  0.5f, -0.5f,   0.f,  0.f, -1.f,   1.f, 1.f,
                -0.5f,  0.5f, -0.5f,   0.f,  0.f, -1.f,   1.f, 0.f,

                -0.5f, -0.5f,  0.5f,   0.f,  0.f,  1.f,   0.f, 0.f,
                 0.5f, -0.5f,  0.5f,   0.f,  0.f,  1.f,   0.f, 1.f,
                 0.5f,  0.5f,  0.5f,   0.f,  0.f,  1.f,   1.f, 1.f,
                -0.5f,  0.5f,  0.5f,   0.f,  0.f,  1.f,   1.f, 0.f,

                -0.5f,  0.5f,  0.5f,  -1.f,  0.f,  0.f,   0.f, 0.f,
                -0.5f,  0.5f, -0.5f,  -1.f,  0.f,  0.f,   0.f, 1.f,
                -0.5f, -0.5f, -0.5f,  -1.f,  0.f,  0.f,   1.f, 1.f,
                -0.5f, -0.5f,  0.5f,   1.f,  0.f,  0.f,   1.f, 0.f,

                 0.5f,  0.5f,  0.5f,   1.f,  0.f,  0.f,   0.f, 0.f,
                 0.5f,  0.5f, -0.5f,   1.f,  0.f,  0.f,   0.f, 1.f,
                 0.5f, -0.5f, -0.5f,   1.f,  0.f,  0.f,   1.f, 1.f,
                 0.5f, -0.5f,  0.5f,   1.f,  0.f,  0.f,   1.f, 0.f,

                -0.5f, -0.5f, -0.5f,   0.f, -1.f,  0.f,   0.f, 0.f,
                 0.5f, -0.5f, -0.5f,   0.f, -1.f,  0.f,   0.f, 1.f,
                 0.5f, -0.5f,  0.5f,   0.f, -1.f,  0.f,   1.f, 1.f,
                -0.5f, -0.5f,  0.5f,   0.f, -1.f,  0.f,   1.f, 0.f,

                -0.5f,  0.5f, -0.5f,   0.f,  1.f,  0.f,   0.f, 0.f,
                 0.5f,  0.5f, -0.5f,   0.f,  1.f,  0.f,   0.f, 1.f,
                 0.5f,  0.5f,  0.5f,   0.f,  1.f,  0.f,   1.f, 1.f,
                -0.5f,  0.5f,  0.5f,   0.f,  1.f,  0.f,   1.f, 0.f
        };

        auto vertexBuffer = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));

        vertexBuffer->setLayout({
            { ShaderDataType::Float3, "a_position" },
            { ShaderDataType::Float3, "a_normal" },
            { ShaderDataType::Float2, "a_texCoord" }});
        data->cubeVA->addVertexBuffer(vertexBuffer);

        unsigned int indices[6 * 6] = { 0,  1,  2,  2,  3,  0,
                                        4,  5,  6,  6,  7,  4,
                                        8,  9,  10, 10, 11, 8,
                                        12, 13, 14, 14, 15, 12,
                                        16, 17, 18, 18, 19, 16,
                                        20, 21, 22, 22, 23, 20 };
        auto indexBuffer = std::make_shared<IndexBuffer>(indices, std::size(indices));
        data->cubeVA->setIndexBuffer(indexBuffer);

        data->flatColorShader = std::make_shared<Shader>("../../app/assets/shaders/flat_color.glsl");
        data->textureShader = std::make_shared<Shader>("../../app/assets/shaders/texture.glsl");
        data->textureShader->bind();
        data->textureShader->uploadUniformInt("u_texture", 0);
    }

    void Renderer3D::shutdown()
    {
        data.reset();
    }

    void Renderer3D::beginScene(const Camera3D& camera)
    {
        data->flatColorShader->bind();
        data->flatColorShader->uploadUniformMat4("u_viewProj", camera.getViewProjMatrix());
        data->flatColorShader->uploadUniformFloat3("u_viewDir", camera.getDirection());

        data->textureShader->bind();
        data->textureShader->uploadUniformMat4("u_viewProj", camera.getViewProjMatrix());
    }

    void Renderer3D::endScene()
    {}

    void Renderer3D::drawCube(const Vec3& pos, const Vec3& size, const Color& color)
    {
        drawCube(pos, size, Material(color));
    }

    void Renderer3D::drawCube(const Vec3& pos, const Vec3& size, const Material& material)
    {
        data->flatColorShader->bind();
        data->flatColorShader->uploadUniformFloat3("u_ambient", material.ambient);
        data->flatColorShader->uploadUniformFloat3("u_diffuse", material.diffuse);
        data->flatColorShader->uploadUniformFloat3("u_specular", material.specular);
        data->flatColorShader->uploadUniformFloat("u_shininess", material.shininess);

        Mat4 transform = translate(pos) * scale({size.x, size.y, size.z});
        data->flatColorShader->uploadUniformMat4("u_transform", transform);
        data->flatColorShader->uploadUniformMat4("u_normalMat", transpose(inverse(transform)));
        data->flatColorShader->uploadUniformFloat3("u_lightPos", data->lightPos);

        data->cubeVA->bind();
        RenderCommand::drawIndexed(data->cubeVA);
    }

    void Renderer3D::drawCube(const Vec3& pos, const Vec3& size, const Ref<Texture>& texture)
    {
        data->textureShader->bind();

        Mat4 transform = translate(pos) * scale({size.x, size.y, size.z});
        data->textureShader->uploadUniformMat4("u_transform", transform);

        texture->bind();

        data->cubeVA->bind();
        RenderCommand::drawIndexed(data->cubeVA);
    }

    void Renderer3D::setLightSource(Vec3& pos)
    {
        data->lightPos = pos;
    }
}