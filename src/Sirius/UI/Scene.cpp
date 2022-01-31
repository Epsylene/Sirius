
#include "Sirius/UI/Scene.hpp"

#include "Sirius/Core/Application.hpp"
#include "Sirius/Core/Input.hpp"
#include "Sirius/Renderer/Renderer2D.hpp"
#include "Sirius/Renderer/Renderer3D.hpp"

#include <imgui.h>

namespace Sirius
{
    SceneProperties Scene::properties {};
    SceneData Scene::sceneData {};

    void Scene::init()
    {
        properties.ppSeparator = (float)Application::get().getWindow().getWidth() / 2.f;

        sceneData.controller2D = std::make_shared<CameraController2D>();
        sceneData.controller3D = std::make_shared<CameraController3D>();

        std::unordered_map<Sirius::CubeFace, std::string> skybox =
                {{Sirius::CubeFace::RIGHT, "../../app/res/textures/skybox/right.jpg"},
                 {Sirius::CubeFace::LEFT, "../../app/res/textures/skybox/left.jpg"},
                 {Sirius::CubeFace::BOTTOM, "../../app/res/textures/skybox/bottom.jpg"},
                 {Sirius::CubeFace::TOP, "../../app/res/textures/skybox/top.jpg"},
                 {Sirius::CubeFace::BACK, "../../app/res/textures/skybox/back.jpg"},
                 {Sirius::CubeFace::FRONT, "../../app/res/textures/skybox/front.jpg"}};

        sceneData.skybox = std::make_shared<Skybox>(skybox);
    }

    void Scene::render()
    {
        ImGui::Begin("Scene");

        if(properties.render2D)
            properties.background = Color::White;

        ImVec2 panelSize = ImGui::GetContentRegionAvail();
        sceneData.controller2D->setAspect(panelSize.x / panelSize.y);
        sceneData.controller3D->setAspect(panelSize.x / panelSize.y);
        auto& tex = Renderer::sceneData->postRenderFBO->colorBuffer;
        ImGui::Image(reinterpret_cast<void*>(tex.textureID), panelSize, ImVec2(0, 1), ImVec2(1, 0));

        properties.active = ImGui::IsWindowHovered();

        ImGui::End();
    }

    void Scene::onUpdate(Timestep dt)
    {
        properties.render2D ? Renderer2D::beginScene(sceneData.controller2D->getCamera())
                            : Renderer3D::beginScene(sceneData.controller3D->getCamera());

        if(properties.active)
        {
            properties.render2D ? sceneData.controller2D->onUpdate(dt)
                                : sceneData.controller3D->onUpdate(dt);
        }

        if(!properties.render2D)
        {
            if(!properties.wireframe)
                Renderer3D::drawSkybox();

            for (auto& model: sceneData.models)
                Renderer3D::drawModel(model, DrawMode::TEXTURE);
        }

        Renderer2D::endScene();
        Renderer3D::endScene();
    }
}