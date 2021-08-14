
#include "Sirius/UI/Scene.hpp"

#include "Sirius/Core/Application.hpp"
#include "Sirius/Core/Input.hpp"
#include "Sirius/Renderer/Renderer3D.hpp"

#include <imgui.h>

namespace Sirius
{
    bool Scene::mouseInArea = false;
    Vec2 Scene::panelSize {};
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

        auto mousePos = Sirius::Input::getMouseScreenPos();
        if(mousePos.x > vMin.x && mousePos.x < vMax.x && mousePos.y > vMin.y && mousePos.y < vMax.y)
            mouseInArea = true;
        else
            mouseInArea = false;

        ImVec2 panelSize = ImGui::GetContentRegionAvail();
        Scene::panelSize = { panelSize.x, panelSize.y };
        controller->setAspect(panelSize.x / panelSize.y);
        auto& tex = Renderer::sceneData->postRenderFBO->colorBuffer;
        ImGui::Image(reinterpret_cast<void*>(tex.textureID), panelSize, ImVec2(0, 1), ImVec2(1, 0));

        ImGui::End();
    }

    void Scene::drawModel(const Ref<Model>& model, const Vec3& pos, const Vec3& size)
    {
        if(mouseInArea && !PropertiesPanel::fileBrowser.IsOpened())
            Renderer3D::drawModel(model, pos, size, true);
        else
            Renderer3D::drawModel(model, pos, size, false);
    }

    void Scene::onUpdate(Timestep dt)
    {
        Renderer3D::beginScene(Scene::controller->getCamera());

        if(Scene::mouseInArea && !PropertiesPanel::fileBrowser.IsOpened())
            Scene::controller->onUpdate(dt);

        for (auto& model: Scene::models)
        {
            Scene::drawModel(model);
        }

        Sirius::Renderer3D::endScene();
    }

}