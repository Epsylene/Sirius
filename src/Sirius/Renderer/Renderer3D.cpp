
#include "Sirius/Renderer/Renderer3D.hpp"

#include "Sirius/Renderer/RenderCommand.hpp"
#include "Sirius/Renderer/Utils/Shader.hpp"
#include "Sirius/Renderer/Objects/PrefabMeshes.h"

#include "Sirius/Core/Input.hpp"
#include "Sirius/Core/MouseButtonCodes.h"

namespace Sirius
{
    struct Renderer3DStorage
    {
        uint16_t ptLightNb = 0;
        Ref<Cube> emissionCube;
        Ref<Shader> flatColorShader;
        Ref<Shader> textureShader;
        Ref<Shader> flatTextureShader;
        Ref<Shader> emissionShader;
    };

    static Scope<Renderer3DStorage> data;

    void Renderer3D::init()
    {
        data = std::make_unique<Renderer3DStorage>();

        data->emissionCube = std::make_shared<Cube>();

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
        }
        else
        {
            SRS_CORE_ASSERT(false, "There can only be up to 10 point lights in a scene.");
        }
    }

    void Renderer3D::drawEmissionCube(const PointLight& light)
    {
        addPointLight(light);

        data->emissionShader->bind();
        data->emissionShader->uploadUniformFloat3("u_color", light.diffuse);

        Mat4 transform = translate(light.pos) * scale(0.5f);
        data->emissionShader->uploadUniformMat4("u_transform", transform);

        auto emissionCubeVA = data->emissionCube->meshes.begin()->vertexArray;
        emissionCubeVA->bind();
        RenderCommand::drawIndexed(emissionCubeVA);
    }

    void Renderer3D::drawModel(const Ref<Model>& model, const Vec3& pos, const Vec3& size, bool outline)
    {
        data->textureShader->bind();
        Mat4 transform = translate(pos) * scale(size);
        data->textureShader->uploadUniformMat4("u_transform", transform);
        data->textureShader->uploadUniformMat4("u_normalMat", transpose(inverse(transform)));

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
                        data->textureShader->uploadUniformInt("material.diffuse", 0);
                        break;

                    case TextureType::Specular:
                        tex->bind(1);
                        data->textureShader->uploadUniformInt("material.specular", 1);
                        break;

                    case TextureType::Ambient:
                        tex->bind(2);
                        data->textureShader->uploadUniformInt("material.ambient", 2);
                        break;
                }
            }

            data->textureShader->uploadUniformFloat("material.shininess", 32.f);

            if(Input::isMouseButtonPressed(SRS_MOUSE_BUTTON_1) && outline)
            {
                glStencilFunc(GL_ALWAYS, 1, 0xFF);
                glStencilMask(0xFF);

                mesh.vertexArray->bind();
                RenderCommand::drawIndexed(mesh.vertexArray);

                glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
                glStencilMask(0x00);
                glDisable(GL_DEPTH_TEST);

                data->emissionShader->bind();
                data->emissionShader->uploadUniformFloat3("u_color", {0.9f, 0.56f, 0.f});
                data->emissionShader->uploadUniformMat4("u_transform", translate(pos) * scale(size * 1.05f));

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
}