
#include "UI/Scene.hpp"
#include "Renderer3D.hpp"

#include "RenderCommand.hpp"
#include "Renderer/Utils/Shader.hpp"
#include "Renderer/Objects/PrefabMeshes.hpp"

#include "Core/Input/Input.hpp"
#include "Core/Input/MouseButtonCodes.h"

#include "Math/vector_functions.hpp"

namespace Sirius
{
    struct Renderer3DStorage
    {
        uint16_t ptLightNb = 0;
        struct PointLight
        {
            Color ambient;
            Color diffuse;
            Vec4 pos;
            float attDistance;
        } ptLights[10] {};
        Ref<Cube> emissionCube;

        ShaderLibrary shaderLib;
        Ref<UniformBuffer> ptLightsData;
        Ref<UniformBuffer> dirLightData;
        Ref<UniformBuffer> spotlightData;
    };

    static Scope<Renderer3DStorage> data;

    void Renderer3D::init()
    {
        data = std::make_unique<Renderer3DStorage>();

        data->emissionCube = std::make_shared<Cube>();

        auto shadersPath = Sirius::resPath/"shaders";

        data->shaderLib.load(shadersPath/"flat_color.glsl");
        data->shaderLib.load(shadersPath/"emission.glsl");
        data->shaderLib.load(shadersPath/"texture.glsl");
        data->shaderLib.load(shadersPath/"flat_texture.glsl");
        data->shaderLib.load(shadersPath/"skybox.glsl");
        data->shaderLib.load(shadersPath/"reflection.glsl");
        data->shaderLib.load(shadersPath/"refraction.glsl");

        BufferLayout layout = {{{DataType::Float3, DataType::Float3, DataType::Float3}, "dirLight"}};
        data->dirLightData = std::make_shared<UniformBuffer>(layout, 1);

        layout = {{{DataType::Float3, DataType::Float,
                    DataType::Float3, DataType::Float,
                    DataType::Float3, DataType::Float,
                    DataType::Float3}, "spotlight"}};
        data->spotlightData = std::make_shared<UniformBuffer>(layout, 2);

        layout = {{{DataType::Float4, DataType::Float4,
                    DataType::Float3, DataType::Float}, "ptLights"}};

        data->ptLightsData = std::make_shared<UniformBuffer>(layout, 3);
    }

    void Renderer3D::shutdown()
    {
        data.reset();
    }

    void Renderer3D::beginScene(const Camera3D& camera)
    {
        Renderer::sceneData->cameraData->uploadMat4("viewProj", camera.getViewProjMatrix());
        Renderer::sceneData->cameraData->uploadFloat3("viewDir", camera.getDirection());
        Renderer::sceneData->cameraData->uploadFloat3("cameraPos", camera.getPosition());

        data->shaderLib["refraction"]->uploadUniformFloat3("u_otherCameraPos", camera.getPosition());
        data->shaderLib["skybox"]->bind();
        data->shaderLib["skybox"]->uploadUniformMat4("u_view", Mat4(Mat3(camera.getViewAndProjMatrices().first)));
        data->shaderLib["skybox"]->uploadUniformMat4("u_proj", camera.getViewAndProjMatrices().second);
    }

    void Renderer3D::endScene()
    {
        data->ptLightNb = 0;
    }

    void Renderer3D::setDirectionalLight(const DirectionalLight& dirLight)
    {
        struct DirLight
        {
            Color ambient;
            Color diffuse;
            Vec4 dir;
        } dirLightStruct { dirLight.ambient,
                           dirLight.diffuse,
                           vec4(dirLight.dir) };

        data->dirLightData->uploadStruct("dirLight", &dirLightStruct);
    }

    void Renderer3D::setSpotlight(const Spotlight& spotlight)
    {
        struct Spotlight
        {
            Vec3 diffuse;
            float cosInCutoff;
            Vec3 pos;
            float cosOutCutoff;
            Vec3 ambient;
            float attDistance;
            Vec3 dir;
        } spotlightStruct { spotlight.diffuse, std::cos(spotlight.cutoff), spotlight.pos,
                            std::cos(spotlight.epsilon + spotlight.cutoff), spotlight.ambient,
                            spotlight.attDistance, spotlight.dir };

        data->spotlightData->uploadStruct("spotlight", &spotlightStruct);
    }

    void Renderer3D::addPointLight(const PointLight& ptLight)
    {
        if(data->ptLightNb < 10)
        {
            data->ptLights[data->ptLightNb++] = {ptLight.ambient, ptLight.diffuse,
                                                 vec4(ptLight.pos), ptLight.attDistance};

            data->ptLightsData->uploadStruct("ptLights", &data->ptLights);
        }
        else
        {
            SRS_CORE_ASSERT(false, "There can only be up to 10 point lights in a scene.");
        }
    }

    void Renderer3D::drawEmissionCube(const PointLight& light)
    {
        addPointLight(light);

        auto& emissionShader = data->shaderLib["emission"];
        emissionShader->bind();
        emissionShader->uploadUniformFloat3("u_color", light.diffuse);

        Mat4 transform = translate(light.pos) * scale(0.5f);
        emissionShader->uploadUniformMat4("u_transform", transform);

        auto& emissionCubeVA = data->emissionCube->meshes.begin()->vertexArray;
        emissionCubeVA->bind();
        RenderCommand::drawIndexed(emissionCubeVA);
    }

    void Renderer3D::drawModel(const Ref<Model>& model, DrawMode mode, const Vec3& pos, const Vec3& size, bool outline)
    {
        Mat4 transform = translate(pos) * scale(size);

        if(mode == DrawMode::TEXTURE)
        {
            auto& textureShader = data->shaderLib["texture"];

            textureShader->bind();
            textureShader->uploadUniformMat4("u_transform", transform);
            textureShader->uploadUniformMat4("u_normalMat", transpose(inverse(transform)));

            for (auto& mesh: model->meshes)
            {
                for (auto& tex: mesh.textures)
                {
                    switch (tex->type)
                    {
                        case TextureType::None:
                            break;

                        case TextureType::Diffuse:
                            tex->bind(0);
                            textureShader->uploadUniformInt("material.diffuse", 0);
                            break;

                        case TextureType::Specular:
                            tex->bind(1);
                            textureShader->uploadUniformInt("material.specular", 1);
                            break;

                        case TextureType::Ambient:
                            tex->bind(2);
                            textureShader->uploadUniformInt("material.ambient", 2);
                            break;
                    }
                }
            }

            textureShader->uploadUniformFloat("material.shininess", 32.f);
        }
        else if(mode == DrawMode::REFLECTION)
        {
            auto& reflectionShader = data->shaderLib["reflection"];
            reflectionShader->bind();
            reflectionShader->uploadUniformMat4("u_transform", transform);
            reflectionShader->uploadUniformMat4("u_normalMat", transpose(inverse(transform)));

            Scene::sceneData.skybox->texture.bind(0);
            reflectionShader->uploadUniformInt("u_skybox", 0);
        }
        else if(mode == DrawMode::REFRACTION)
        {
            auto& refractionShader = data->shaderLib["refraction"];
            refractionShader->bind();
            refractionShader->uploadUniformMat4("u_transform", transform);
            refractionShader->uploadUniformMat4("u_normalMat", transpose(inverse(transform)));

            Scene::sceneData.skybox->texture.bind(0);
            refractionShader->uploadUniformInt("u_skybox", 0);
        }
        else if(mode == DrawMode::EMISSION)
        {
            auto& emissionShader = data->shaderLib["emission"];
            emissionShader->bind();
            emissionShader->uploadUniformMat4("u_transform", transform);
            emissionShader->uploadUniformFloat3("u_color", Color::Red);
        }

//        auto& emissionShader = data->shaderLib["emission"];
        for (auto& mesh: model->meshes)
        {
            // @todo : rework someday
//            if(Input::isMouseButtonPressed(SRS_MOUSE_BUTTON_1) && outline && Scene::properties.active)
//            {
//                glStencilFunc(GL_ALWAYS, 1, 0xFF);
//                glStencilMask(0xFF);
//
//                mesh.vertexArray->bind();
//                RenderCommand::drawIndexed(mesh.vertexArray, Primitives::TRIANGLES);
//
//                glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
//                glStencilMask(0x00);
//
//                emissionShader->bind();
//                emissionShader->uploadUniformFloat3("u_color", {0.9f, 0.56f, 0.f});
//                emissionShader->uploadUniformMat4("u_transform", translate(pos) * scale(size * 1.05f));
//
//                mesh.vertexArray->bind();
//                RenderCommand::drawIndexed(mesh.vertexArray);
//
//                glStencilMask(0xFF);
//                glStencilFunc(GL_ALWAYS, 1, 0xFF);
//            }
//            else
//            {
                mesh.vertexArray->bind();
                RenderCommand::drawIndexed(mesh.vertexArray);
//            }
        }
    }

    void Renderer3D::drawSkybox()
    {
        RenderCommand::setFaceCulling(false);
        RenderCommand::setDepthTest(false);

        data->shaderLib["skybox"]->bind();
        data->shaderLib["skybox"]->uploadUniformMat4("u_transform", scale(100.f));
        Scene::sceneData.skybox->texture.bind();
        data->shaderLib["skybox"]->uploadUniformInt("u_skybox", 0);
        Scene::sceneData.skybox->cube.meshes.begin()->vertexArray->bind();
        RenderCommand::drawIndexed(Scene::sceneData.skybox->cube.meshes.begin()->vertexArray);

        RenderCommand::setDepthTest(true);
        RenderCommand::setFaceCulling(true);
    }
}