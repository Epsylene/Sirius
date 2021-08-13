
#include "Sirius/UI/Panels.h"

#include "Sirius/UI/Scene.hpp"

namespace Sirius
{
    ImGui::FileBrowser PropertiesPanel::fileBrowser {};

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

        ImGui::End();

        fileBrowser.Display();
        if(fileBrowser.HasSelected())
        {
//            Log::coreTrace(fileBrowser.GetPwd().string());
            auto filePath = fileBrowser.GetSelected().string();
            std::ranges::replace(filePath, '\\', '/');
            Scene::models.emplace_back(std::make_shared<Model>(filePath));
            Log::coreTrace(Scene::models.size());

//            mMeshLoadCallback(file_path);

            fileBrowser.ClearSelected();
        }
    }
}
