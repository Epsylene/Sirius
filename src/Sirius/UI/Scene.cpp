
#include "Sirius/UI/Scene.hpp"

#include "Sirius/Core/Application.hpp"
#include "Sirius/Core/Input.hpp"
#include "Sirius/Renderer/Renderer3D.hpp"

#include <imgui.h>

namespace Sirius
{
    std::vector<Ref<Model>> Scene::models {};
    Ref<CameraController3D> Scene::controller {};
    SceneProperties Scene::properties {};

    void Scene::init()
    {
        controller = std::make_shared<CameraController3D>();
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
        controller->setAspect(panelSize.x / panelSize.y);
        auto& tex = Renderer::sceneData->postRenderFBO->colorBuffer;
        ImGui::Image(reinterpret_cast<void*>(tex.textureID), panelSize, ImVec2(0, 1), ImVec2(1, 0));

        properties.pos = { vMin.x, vMin.y };
        properties.size = { panelSize.x, panelSize.y };

        ImGui::End();
    }

    void Scene::drawModel(const Ref<Model>& model, const Vec3& pos, const Vec3& size)
    {
        auto p0 = properties.pos, p1 = properties.pos + properties.size;

        if(Input::mouseInArea(p0, p1, true) && !PropertiesPanel::browserOpened())
            Renderer3D::drawModel(model, pos, size, true);
        else
            Renderer3D::drawModel(model, pos, size, false);
    }

    void Scene::onUpdate(Timestep dt)
    {
        Renderer3D::beginScene(controller->getCamera());

        auto p0 = properties.pos, p1 = properties.pos + properties.size;
        if(Input::mouseInArea(p0, p1, true) && !PropertiesPanel::browserOpened())
            controller->onUpdate(dt);

        for (auto& model: models)
            Scene::drawModel(model);

        if(!properties.wireframe)
            Renderer3D::drawSkybox();

        Renderer3D::endScene();
    }

    void Scene::setSkybox(const std::unordered_map<CubeFace, std::string>& skybox)
    {
        Renderer3D::setSkybox(skybox);
    }
}