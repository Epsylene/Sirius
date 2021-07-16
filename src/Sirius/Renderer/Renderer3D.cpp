
#include "Sirius/Renderer/Renderer3D.hpp"

#include "Sirius/Renderer/RenderCommand.hpp"
#include "Sirius/Renderer/Shader.hpp"
#include "Sirius/Renderer/Material.hpp"
#include "Sirius/Renderer/Light.h"

#include <stb_image.h>

namespace Sirius
{
    struct Renderer3DStorage
    {
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
        data->textureShader->uploadUniformFloat3("u_viewDir", camera.getDirection());
    }

    void Renderer3D::endScene()
    {}

    void Renderer3D::drawCube(const Vec3& pos, const Vec3& size, const Color& color)
    {
        data->flatColorShader->bind();

        data->flatColorShader->uploadUniformFloat3("material.ambient", {1.f, 1.f, 1.f});
        data->flatColorShader->uploadUniformFloat3("material.diffuse", color);
        data->flatColorShader->uploadUniformFloat3("material.specular", {1.f, 1.f, 1.f});
        data->flatColorShader->uploadUniformFloat("material.shininess", 32.f);

        Mat4 transform = translate(pos) * scale({size.x, size.y, size.z});
        data->flatColorShader->uploadUniformMat4("u_transform", transform);
        data->flatColorShader->uploadUniformMat4("u_normalMat", transpose(inverse(transform)));

        data->cubeVA->bind();
        RenderCommand::drawIndexed(data->cubeVA);
    }

    void Renderer3D::drawCube(const Vec3& pos, const Vec3& size, const Ref<Texture>& texture)
    {
        data->textureShader->bind();

        texture->bind(0);
        data->textureShader->uploadUniformInt("material.diffuse", 0);
        texture->bind(1);
        data->textureShader->uploadUniformInt("material.specular", 1);
        data->textureShader->uploadUniformFloat("material.shininess", 32.f);

        Mat4 transform = translate(pos) * scale({size.x, size.y, size.z});
        data->textureShader->uploadUniformMat4("u_transform", transform);

        data->cubeVA->bind();
        RenderCommand::drawIndexed(data->cubeVA);
    }

    void Renderer3D::drawCube(const Vec3& pos, const Vec3& size, const Material& material)
    {
        data->textureShader->bind();

        material.diffuseMap->bind(0);
        data->textureShader->uploadUniformInt("material.diffuse", 0);
        material.specularMap->bind(1);
        data->textureShader->uploadUniformInt("material.specular", 1);
        data->textureShader->uploadUniformFloat("material.shininess", material.shininess);

        Mat4 transform = translate(pos) * scale({size.x, size.y, size.z});
        data->textureShader->uploadUniformMat4("u_transform", transform);
        data->textureShader->uploadUniformMat4("u_normalMat", transpose(inverse(transform)));

        data->cubeVA->bind();
        RenderCommand::drawIndexed(data->cubeVA);
    }

    void Renderer3D::addPointLight(const PointLight& ptLight)
    {
        data->flatColorShader->bind();
        data->flatColorShader->uploadUniformFloat3("light.ambient", ptLight.ambient);
        data->flatColorShader->uploadUniformFloat3("light.diffuse", ptLight.diffuse);
        data->flatColorShader->uploadUniformFloat3("light.specular", ptLight.specular);
        data->flatColorShader->uploadUniformFloat3("light.pos", ptLight.pos);

        data->textureShader->bind();
        data->textureShader->uploadUniformFloat3("ptLight.ambient", ptLight.ambient);
        data->textureShader->uploadUniformFloat3("ptLight.diffuse", ptLight.diffuse);
        data->textureShader->uploadUniformFloat3("ptLight.specular", ptLight.specular);
        data->textureShader->uploadUniformFloat3("ptLight.pos", ptLight.pos);
        data->textureShader->uploadUniformFloat("ptLight.attDistance", ptLight.attDistance);
    }

    void Renderer3D::addDirectionalLight(const DirectionalLight& dirLight)
    {
        data->textureShader->bind();
        data->textureShader->uploadUniformFloat3("dirLight.ambient", dirLight.ambient);
        data->textureShader->uploadUniformFloat3("dirLight.diffuse", dirLight.diffuse);
        data->textureShader->uploadUniformFloat3("dirLight.specular", dirLight.specular);
        data->textureShader->uploadUniformFloat3("dirLight.dir", dirLight.dir);
    }

    void Renderer3D::addSpotlight(const Spotlight& spotlight)
    {
        data->textureShader->bind();
        data->textureShader->uploadUniformFloat3("spotlight.ambient", spotlight.ambient);
        data->textureShader->uploadUniformFloat3("spotlight.diffuse", spotlight.diffuse);
        data->textureShader->uploadUniformFloat3("spotlight.specular", spotlight.specular);
        data->textureShader->uploadUniformFloat3("spotlight.pos", spotlight.pos);
        data->textureShader->uploadUniformFloat3("spotlight.dir", spotlight.dir);
        data->textureShader->uploadUniformFloat("spotlight.attDistance", spotlight.attDistance);
        data->textureShader->uploadUniformFloat("spotlight.cosInCutoff", std::cos(spotlight.cutoff));
        data->textureShader->uploadUniformFloat("spotlight.cosOutCutoff", std::cos(spotlight.epsilon + spotlight.cutoff));
    }
}