
#include "Sirius/UI/Panels.h"

#include "Sirius/UI/Scene.hpp"

namespace Sirius
{
    ImGui::FileBrowser PropertiesPanel::fileBrowser {};

    void PropertiesPanel::init()
    {
        fileBrowser.SetTitle("Open mesh");
        fileBrowser.SetTypeFilters({".fbx", ".obj"});
    }

    void PropertiesPanel::render()
    {
        ImGui::Begin("Properties");
        if(ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
        {
            if(ImGui::Button("Open..."))
                fileBrowser.Open();
            ImGui::SameLine(0, 5.0f);
            ImGui::Text("%s", fileBrowser.GetSelected().filename().string().c_str());
        }

        fileBrowser.Display();
        if(fileBrowser.HasSelected())
        {
            auto filePath = fileBrowser.GetSelected().string();
            std::ranges::replace(filePath, '\\', '/');
            Scene::models.emplace_back(std::make_shared<Model>(filePath));

            fileBrowser.ClearSelected();
        }

        if(ImGui::CollapsingHeader("Scene options", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::ColorEdit3("Scene background color", &Scene::properties.background.r);
            ImGui::Checkbox("Wireframe mode", &Scene::properties.wireframe);
        }
        ImGui::End();
    }
}
