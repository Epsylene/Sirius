
#include "Sirius/UI/Scene.hpp"
#include "Sirius/Renderer/Renderer3D.hpp"

#include "Sirius/Renderer/RenderCommand.hpp"
#include "Sirius/Renderer/Utils/Shader.hpp"
#include "Sirius/Renderer/Objects/PrefabMeshes.hpp"

#include "Sirius/Core/Input.hpp"
#include "Sirius/Core/MouseButtonCodes.h"

namespace Sirius
{
    struct Renderer3DStorage
    {
        uint16_t ptLightNb = 0;
        Ref<Cube> emissionCube;
        Ref<Skybox> skybox;

        ShaderLibrary shaderLib;
    };

    static Scope<Renderer3DStorage> data;

    void Renderer3D::init()
    {
        data = std::make_unique<Renderer3DStorage>();

        data->emissionCube = std::make_shared<Cube>();

        data->shaderLib.load("../../app/res/shaders/flat_color.glsl");
        data->shaderLib.load("../../app/res/shaders/emission.glsl");
        data->shaderLib.load("../../app/res/shaders/texture.glsl");
        data->shaderLib.load("../../app/res/shaders/flat_texture.glsl");
        data->shaderLib.load("../../app/res/shaders/skybox.glsl");

        std::unordered_map<Sirius::CubeFace, std::string> skybox =
                {{Sirius::CubeFace::RIGHT, "../../app/res/textures/skybox/right.jpg"},
                 {Sirius::CubeFace::LEFT, "../../app/res/textures/skybox/left.jpg"},
                 {Sirius::CubeFace::BOTTOM, "../../app/res/textures/skybox/bottom.jpg"},
                 {Sirius::CubeFace::TOP, "../../app/res/textures/skybox/top.jpg"},
                 {Sirius::CubeFace::BACK, "../../app/res/textures/skybox/back.jpg"},
                 {Sirius::CubeFace::FRONT, "../../app/res/textures/skybox/front.jpg"}};

        setSkybox(skybox);
    }

    void Renderer3D::shutdown()
    {
        data.reset();
    }

    void Renderer3D::beginScene(const Camera3D& camera)
    {
        for (auto& [name, shader]: data->shaderLib)
        {
            if(name == "skybox")
            {
                shader->bind();
                auto [view, proj] = camera.getViewAndProjMatrices();
                view = Mat4(Mat3(view));
                view[3][3] = 1.f;
                shader->uploadUniformMat4("u_viewProj", proj * view * scale(5.f));
            }
            else
            {
                shader->bind();
                shader->uploadUniformMat4("u_viewProj", camera.getViewProjMatrix());
            }

            if(name == "flat_color" || name == "texture")
                shader->uploadUniformFloat3("u_viewDir", camera.getDirection());
        }
    }

    void Renderer3D::endScene()
    {
        data->ptLightNb = 0;
    }

    void Renderer3D::setDirectionalLight(const DirectionalLight& dirLight)
    {
        auto& flatColorShader = data->shaderLib["flat_color"];
        auto& textureShader = data->shaderLib["texture"];

        for (auto& [name, shader]: data->shaderLib)
        {
            if(name == "flat_color" || name == "texture")
            {
                shader->bind();
                shader->uploadUniformFloat3("dirLight.ambient", dirLight.ambient);
                shader->uploadUniformFloat3("dirLight.diffuse", dirLight.diffuse);
                shader->uploadUniformFloat3("dirLight.dir", dirLight.dir);
            }
        }
    }

    void Renderer3D::setSpotlight(const Spotlight& spotlight)
    {
        for (auto& [name, shader]: data->shaderLib)
        {
            if(name == "flat_color" || name == "texture")
            {
                shader->bind();
                shader->uploadUniformFloat3("spotlight.ambient", spotlight.ambient);
                shader->uploadUniformFloat3("spotlight.diffuse", spotlight.diffuse);
                shader->uploadUniformFloat3("spotlight.pos", spotlight.pos);
                shader->uploadUniformFloat3("spotlight.dir", spotlight.dir);
                shader->uploadUniformFloat("spotlight.attDistance", spotlight.attDistance);
                shader->uploadUniformFloat("spotlight.cosInCutoff", std::cos(spotlight.cutoff));
                shader->uploadUniformFloat("spotlight.cosOutCutoff", std::cos(spotlight.epsilon + spotlight.cutoff));
            }
        }
    }

    void Renderer3D::addPointLight(const PointLight& ptLight)
    {
        if(data->ptLightNb < 10)
        {
            auto index = std::to_string(data->ptLightNb++);

            for (auto& [name, shader]: data->shaderLib)
            {
                if(name == "flat_color" || name == "texture")
                {
                    shader->bind();
                    shader->uploadUniformFloat3("ptLights[" + index + "].ambient", ptLight.ambient);
                    shader->uploadUniformFloat3("ptLights[" + index + "].diffuse", ptLight.diffuse);
                    shader->uploadUniformFloat3("ptLights[" + index + "].pos", ptLight.pos);
                    shader->uploadUniformFloat("ptLights[" + index + "].attDistance", ptLight.attDistance);
                }
            }
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

    void Renderer3D::drawModel(const Ref<Model>& model, const Vec3& pos, const Vec3& size, bool outline)
    {
        auto& textureShader = data->shaderLib["texture"];
        auto& emissionShader = data->shaderLib["emission"];

        textureShader->bind();
        Mat4 transform = translate(pos) * scale(size);
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

            textureShader->uploadUniformFloat("material.shininess", 32.f);

            if(Input::isMouseButtonPressed(SRS_MOUSE_BUTTON_1) && outline)
            {
                glStencilFunc(GL_ALWAYS, 1, 0xFF);
                glStencilMask(0xFF);

                mesh.vertexArray->bind();
                RenderCommand::drawIndexed(mesh.vertexArray);

                glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
                glStencilMask(0x00);
                glDisable(GL_DEPTH_TEST);

                emissionShader->bind();
                emissionShader->uploadUniformFloat3("u_color", {0.9f, 0.56f, 0.f});
                emissionShader->uploadUniformMat4("u_transform", translate(pos) * scale(size * 1.05f));

                mesh.vertexArray->bind();
                RenderCommand::drawIndexed(mesh.vertexArray);

                glStencilMask(0xFF);
                glStencilFunc(GL_ALWAYS, 1, 0xFF);
                glEnable(GL_DEPTH_TEST);
            }
            else
            {
                mesh.vertexArray->bind();
                RenderCommand::drawIndexed(mesh.vertexArray);
            }
        }
    }

    void Renderer3D::setSkybox(const std::unordered_map<CubeFace, std::string>& skybox)
    {
        data->skybox = std::make_shared<Skybox>(skybox);
    }

    void Renderer3D::drawSkybox()
    {
        if(data->skybox)
        {
            RenderCommand::setFaceCulling(false);
            data->shaderLib["skybox"]->bind();

            data->skybox->texture.bind();
            data->shaderLib["skybox"]->uploadUniformInt("u_skybox", 0);

            data->skybox->cube.meshes.begin()->vertexArray->bind();
            RenderCommand::drawIndexed(data->skybox->cube.meshes.begin()->vertexArray);
            RenderCommand::setFaceCulling(true);
        }
    }
}