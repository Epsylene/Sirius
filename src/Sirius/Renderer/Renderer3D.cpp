
#include "Sirius/Renderer/Renderer3D.hpp"

#include "Sirius/Renderer/RenderCommand.hpp"
#include "Sirius/Renderer/Utils/Shader.hpp"

#include "Sirius/Core/Input.hpp"
#include "Sirius/Core/MouseButtonCodes.h"

namespace Sirius
{
    struct Renderer3DStorage
    {
        uint16_t ptLightNb = 0;
        Ref<VertexArray> cubeVA;
//        Ref<VertexArray> modelVA;
        std::vector<Ref<VertexArray>> modelVA;
        Ref<Shader> flatColorShader;
        Ref<Shader> textureShader;
        Ref<Shader> flatTextureShader;
        Ref<Shader> emissionShader;
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
        data->cubeVA->unbind();

        data->flatColorShader = std::make_shared<Shader>("../../app/res/shaders/flat_color.glsl");
        data->emissionShader = std::make_shared<Shader>("../../app/res/shaders/emission.glsl");
        data->textureShader = std::make_shared<Shader>("../../app/res/shaders/texture.glsl");
        data->flatTextureShader = std::make_shared<Shader>("../../app/res/shaders/flat_texture.glsl");
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

        data->emissionShader->bind();
        data->emissionShader->uploadUniformMat4("u_viewProj", camera.getViewProjMatrix());
        
        data->flatTextureShader->bind();
        data->flatTextureShader->uploadUniformMat4("u_viewProj", camera.getViewProjMatrix());
    }

    void Renderer3D::endScene()
    {
        data->ptLightNb = 0;
    }

    void Renderer3D::drawCube(const Vec3& pos, const Vec3& size, const Color& color)
    {
        data->flatColorShader->bind();

        data->flatColorShader->uploadUniformFloat3("material.diffuse", color);
        data->flatColorShader->uploadUniformFloat3("material.specular", {1.f, 1.f, 1.f});
        data->flatColorShader->uploadUniformFloat("material.shininess", 32.f);

        Mat4 transform = translate(pos) * scale({size.x, size.y, size.z});
        data->flatColorShader->uploadUniformMat4("u_transform", transform);
        data->flatColorShader->uploadUniformMat4("u_normalMat", transpose(inverse(transform)));

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

    void Renderer3D::setDirectionalLight(const DirectionalLight& dirLight)
    {
        data->flatColorShader->bind();
        data->flatColorShader->uploadUniformFloat3("dirLight.ambient", dirLight.ambient);
        data->flatColorShader->uploadUniformFloat3("dirLight.diffuse", dirLight.diffuse);
        data->flatColorShader->uploadUniformFloat3("dirLight.dir", dirLight.dir);

        data->textureShader->bind();
        data->textureShader->uploadUniformFloat3("dirLight.ambient", dirLight.ambient);
        data->textureShader->uploadUniformFloat3("dirLight.diffuse", dirLight.diffuse);
        data->textureShader->uploadUniformFloat3("dirLight.dir", dirLight.dir);
    }

    void Renderer3D::setSpotlight(const Spotlight& spotlight)
    {
        data->flatColorShader->bind();
        data->flatColorShader->uploadUniformFloat3("spotlight.ambient", spotlight.ambient);
        data->flatColorShader->uploadUniformFloat3("spotlight.diffuse", spotlight.diffuse);
        data->flatColorShader->uploadUniformFloat3("spotlight.pos", spotlight.pos);
        data->flatColorShader->uploadUniformFloat3("spotlight.dir", spotlight.dir);
        data->flatColorShader->uploadUniformFloat("spotlight.attDistance", spotlight.attDistance);
        data->flatColorShader->uploadUniformFloat("spotlight.cosInCutoff", std::cos(spotlight.cutoff));
        data->flatColorShader->uploadUniformFloat("spotlight.cosOutCutoff", std::cos(spotlight.epsilon + spotlight.cutoff));

        data->textureShader->bind();
        data->textureShader->uploadUniformFloat3("spotlight.ambient", spotlight.ambient);
        data->textureShader->uploadUniformFloat3("spotlight.diffuse", spotlight.diffuse);
        data->textureShader->uploadUniformFloat3("spotlight.pos", spotlight.pos);
        data->textureShader->uploadUniformFloat3("spotlight.dir", spotlight.dir);
        data->textureShader->uploadUniformFloat("spotlight.attDistance", spotlight.attDistance);
        data->textureShader->uploadUniformFloat("spotlight.cosInCutoff", std::cos(spotlight.cutoff));
        data->textureShader->uploadUniformFloat("spotlight.cosOutCutoff", std::cos(spotlight.epsilon + spotlight.cutoff));
    }

    void Renderer3D::drawEmissionCube(const PointLight& light)
    {
        if(data->ptLightNb < 10)
        {
            auto index = std::to_string(data->ptLightNb++);

            data->flatColorShader->bind();
            data->flatColorShader->uploadUniformFloat3("ptLights[" + index + "].ambient", light.ambient);
            data->flatColorShader->uploadUniformFloat3("ptLights[" + index + "].diffuse", light.diffuse);
            data->flatColorShader->uploadUniformFloat3("ptLights[" + index + "].pos", light.pos);
            data->flatColorShader->uploadUniformFloat("ptLights[" + index + "].attDistance", light.attDistance);

            data->textureShader->bind();
            data->textureShader->uploadUniformFloat3("ptLights[" + index + "].ambient", light.ambient);
            data->textureShader->uploadUniformFloat3("ptLights[" + index + "].diffuse", light.diffuse);
            data->textureShader->uploadUniformFloat3("ptLights[" + index + "].pos", light.pos);
            data->textureShader->uploadUniformFloat("ptLights[" + index + "].attDistance", light.attDistance);

            data->emissionShader->bind();
            data->emissionShader->uploadUniformFloat3("u_color", light.diffuse);

            Mat4 transform = translate(light.pos) * scale(0.5f);
            data->emissionShader->uploadUniformMat4("u_transform", transform);

            data->cubeVA->bind();
            RenderCommand::drawIndexed(data->cubeVA);
        }
        else
        {
            SRS_CORE_ASSERT(false, "There can only be up to 10 point lights in a scene.");
        }
    }

    void Renderer3D::addPointLight(const PointLight& ptLight)
    {
        if(data->ptLightNb < 10)
        {
            auto index = std::to_string(data->ptLightNb++);

            data->flatColorShader->bind();
            data->flatColorShader->uploadUniformFloat3("ptLights[" + index + "].ambient", ptLight.ambient);
            data->flatColorShader->uploadUniformFloat3("ptLights[" + index + "].diffuse", ptLight.diffuse);
            data->flatColorShader->uploadUniformFloat3("ptLights[" + index + "].pos", ptLight.pos);
            data->flatColorShader->uploadUniformFloat("ptLights[" + index + "].attDistance", ptLight.attDistance);

            data->textureShader->bind();
            data->textureShader->uploadUniformFloat3("ptLights[" + index + "].ambient", ptLight.ambient);
            data->textureShader->uploadUniformFloat3("ptLights[" + index + "].diffuse", ptLight.diffuse);
            data->textureShader->uploadUniformFloat3("ptLights[" + index + "].pos", ptLight.pos);
            data->textureShader->uploadUniformFloat("ptLights[" + index + "].attDistance", ptLight.attDistance);

            data->emissionShader->bind();
            data->emissionShader->uploadUniformFloat3("u_color", ptLight.diffuse);

            Mat4 transform = translate(ptLight.pos) * scale(0.5f);
            data->emissionShader->uploadUniformMat4("u_transform", transform);
        }
        else
        {
            SRS_CORE_ASSERT(false, "There can only be up to 10 point lights in a scene.");
        }
    }

    void Renderer3D::addModel(const Model& model)
    {
        for (auto& mesh: model.meshes)
        {
            auto vb = std::make_shared<VertexBuffer>(mesh.vertices);
            auto ib = std::make_shared<IndexBuffer>(mesh.indices);

            data->modelVA.emplace_back(std::make_shared<VertexArray>(vb, ib));
        }
    }

    void Renderer3D::drawModel(const Model& model, const Vec3& pos, const Vec3& size, bool outline)
    {
        if(data->modelVA.empty())
        {
            SRS_CORE_ASSERT(false, "The scene contains no model data. "
                                   "Use Renderer3D::addModel() to add it to the scene.");
        }
        else
        {
            data->textureShader->bind();
            Mat4 transform = translate(pos) * scale(size);
            data->textureShader->uploadUniformMat4("u_transform", transform);
            data->textureShader->uploadUniformMat4("u_normalMat", transpose(inverse(transform)));

            for (auto& mesh: model.meshes)
            {
                for (auto& tex: mesh.textures)
                {
                    switch (tex.type)
                    {
                        case TextureType::None:
                            break;

                        case TextureType::Diffuse:
                            tex.bind(0);
                            data->textureShader->uploadUniformInt("material.diffuse", 0);
                            break;

                            case TextureType::Specular:
                                tex.bind(1);
                                data->textureShader->uploadUniformInt("material.specular", 1);
                                break;

                                case TextureType::Ambient:
                                    tex.bind(2);
                                    data->textureShader->uploadUniformInt("material.ambient", 2);
                                    break;
                    }
                }
            }

            data->textureShader->uploadUniformFloat("material.shininess", 32.f);

            for (auto& meshVA: data->modelVA)
            {
                if(Input::isMouseButtonPressed(SRS_MOUSE_BUTTON_1) && outline)
                {
                    glStencilFunc(GL_ALWAYS, 1, 0xFF);
                    glStencilMask(0xFF);

                    meshVA->bind();
                    RenderCommand::drawIndexed(meshVA);

                    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
                    glStencilMask(0x00);
                    glDisable(GL_DEPTH_TEST);

                    data->emissionShader->bind();
                    data->emissionShader->uploadUniformFloat3("u_color", {0.9f, 0.56f, 0.f});
                    data->emissionShader->uploadUniformMat4("u_transform", translate(pos) * scale(size * 1.05f));

                    meshVA->bind();
                    RenderCommand::drawIndexed(meshVA);

                    glStencilMask(0xFF);
                    glStencilFunc(GL_ALWAYS, 1, 0xFF);
                    glEnable(GL_DEPTH_TEST);
                }
                else
                {
                    meshVA->bind();
                    RenderCommand::drawIndexed(meshVA);
                }
            }
        }
    }

//    void Renderer3D::addModel(const Model& model)
//    {
//        auto vb = std::make_shared<VertexBuffer>(model.vertices);
//        auto ib = std::make_shared<IndexBuffer>(model.indices);
//
//        data->modelVA = std::make_shared<VertexArray>(vb, ib);
//        data->modelVA->unbind();
//    }

//    void Renderer3D::drawModel(const Model& model, const Vec3& pos, const Vec3& size)
//    {
//        data->textureShader->bind();
//
//        Mat4 transform = translate(pos) * scale(size);
//        data->textureShader->uploadUniformMat4("u_transform", transform);
//
//        for (auto& [key, tex]: model.textures)
//        {
//            switch (tex.type)
//            {
//                case TextureType::None:
//                    break;
//
//                case TextureType::Diffuse:
//                    tex.bind(0);
//                    data->textureShader->uploadUniformInt("material.diffuse", 0);
//                    break;
//
//                case TextureType::Specular:
//                    tex.bind(1);
//                    data->textureShader->uploadUniformInt("material.specular", 1);
//                    break;
//
//                case TextureType::Ambient:
//                    tex.bind(2);
//                    data->textureShader->uploadUniformInt("material.ambient", 2);
//                    break;
//            }
//
//            data->textureShader->uploadUniformFloat("material.shininess", 32.f);
//        }
//
//        data->modelVA->bind();
//        RenderCommand::drawIndexed(data->modelVA);
//    }
}