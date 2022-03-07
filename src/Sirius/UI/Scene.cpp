
#include "Scene.hpp"

#include "../Core/Application.hpp"
#include "../Renderer/Renderer2D.hpp"
#include "../Renderer/Renderer3D.hpp"

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

        std::string skyboxPath = Sirius::libPath.string() + "/res/skybox/";
        std::unordered_map<Sirius::CubeFace, std::string> skybox =
                {{Sirius::CubeFace::RIGHT, skyboxPath + "right.jpg"},
                 {Sirius::CubeFace::LEFT, skyboxPath + "left.jpg"},
                 {Sirius::CubeFace::BOTTOM, skyboxPath + "bottom.jpg"},
                 {Sirius::CubeFace::TOP, skyboxPath + "top.jpg"},
                 {Sirius::CubeFace::BACK, skyboxPath + "back.jpg"},
                 {Sirius::CubeFace::FRONT, skyboxPath + "front.jpg"}};

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