
#include "Sirius/UI/Scene.hpp"

#include "Sirius/Core/Application.hpp"
#include "Sirius/Core/Input.hpp"
#include "Sirius/Renderer/Renderer3D.hpp"

#include <imgui.h>

namespace Sirius
{
    SceneProperties Scene::properties {};
    SceneData Scene::data {};

    void Scene::init()
    {
        data.controller = std::make_shared<CameraController3D>();

        std::unordered_map<Sirius::CubeFace, std::string> skybox =
                {{Sirius::CubeFace::RIGHT, "../../app/res/textures/skybox/right.jpg"},
                 {Sirius::CubeFace::LEFT, "../../app/res/textures/skybox/left.jpg"},
                 {Sirius::CubeFace::BOTTOM, "../../app/res/textures/skybox/bottom.jpg"},
                 {Sirius::CubeFace::TOP, "../../app/res/textures/skybox/top.jpg"},
                 {Sirius::CubeFace::BACK, "../../app/res/textures/skybox/back.jpg"},
                 {Sirius::CubeFace::FRONT, "../../app/res/textures/skybox/front.jpg"}};

        data.skybox = std::make_shared<Skybox>(skybox);
    }

    void Scene::render()
    {
        ImGui::Begin("Scene");

        ImVec2 vMin = ImGui::GetWindowContentRegionMin();
        ImVec2 vMax = ImGui::GetWindowContentRegionMax();

        vMin.x += ImGui::GetWindowPos().x;
        vMin.y += ImGui::GetWindowPos().y;
        vMax.x += ImGui::GetWindowPos().x;
        vMax.y += ImGui::GetWindowPos().y;

        ImVec2 panelSize = ImGui::GetContentRegionAvail();
        data.controller->setAspect(panelSize.x / panelSize.y);
        auto& tex = Renderer::sceneData->postRenderFBO->colorBuffer;
        ImGui::Image(reinterpret_cast<void*>(tex.textureID), panelSize, ImVec2(0, 1), ImVec2(1, 0));

        properties.pos = { vMin.x, vMin.y };
        properties.size = { panelSize.x, panelSize.y };

        auto p0 = properties.pos, p1 = properties.pos + properties.size;
        properties.active = Input::mouseInArea(p0, p1, true) && !PropertiesPanel::browserOpened();

        ImGui::End();
    }

    void Scene::onUpdate(Timestep dt)
    {
        Renderer3D::beginScene(data.controller->getCamera());

        if(properties.active)
            data.controller->onUpdate(dt);

        for (auto& model: data.models)
            Renderer3D::drawModel(model, DrawMode::TEXTURE);

        if(!properties.wireframe)
            Renderer3D::drawSkybox();

        Renderer3D::endScene();
    }
}