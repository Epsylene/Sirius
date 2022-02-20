
#include "Panels.hpp"

#include "Scene.hpp"
#include "../Core/Core.hpp"
#include "../Renderer/Utils/Texture.hpp"
#include "../Renderer/Renderer3D.hpp"
#include "../Core/Application.hpp"

namespace Sirius
{
    ImGui::FileBrowser PropertiesPanel::meshBrowser {};
    ImGui::FileBrowser PropertiesPanel::skyboxBrowser { ImGuiFileBrowserFlags_MultipleSelection };

    std::vector<const char*> ppFlagsStrs {};
    int selectedFlag;

    void PropertiesPanel::init()
    {
        meshBrowser.SetTitle("Open mesh");
        meshBrowser.SetTypeFilters({".fbx", ".obj"});
        meshBrowser.SetPwd("../../app/res/meshes");

        skyboxBrowser.SetTitle("Open skybox");
        skyboxBrowser.SetTypeFilters({".png", ".jpg"});
        skyboxBrowser.SetPwd("../../app/res/textures");

        constexpr auto& flags = magic_enum::enum_names<PostProcessingFlags>();
        for (auto& flag: flags)
        {
            ppFlagsStrs.emplace_back(flag.data());
        }

    }

    void toggleButton(const char* str_id, bool* v)
    {
        ImVec2 p = ImGui::GetCursorScreenPos();
        ImDrawList* draw_list = ImGui::GetWindowDrawList();

        float height = ImGui::GetFrameHeight();
        float width = height * 1.55f;
        float radius = height * 0.50f;

        if (ImGui::InvisibleButton(str_id, ImVec2(width, height)))
            *v = !*v;
        ImU32 col_bg;
        if (ImGui::IsItemHovered())
            col_bg = *v ? IM_COL32(145+20, 211, 68+20, 255) : IM_COL32(218-20, 218-20, 218-20, 255);
        else
            col_bg = *v ? IM_COL32(145, 211, 68, 255) : IM_COL32(218, 218, 218, 255);

        draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
        draw_list->AddCircleFilled(ImVec2(*v ? (p.x + width - radius) : (p.x + radius), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));
        draw_list->AddText(ImVec2(p.x + width + 10, p.y + height / 5.f), col_bg, str_id);
    }

    void PropertiesPanel::render()
    {
        ImGui::Begin("Properties");
        if(ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
        {
            if(ImGui::Button("Open##Mesh"))
                meshBrowser.Open();

            if(meshBrowser.HasSelected())
            {
                ImGui::SameLine(0, 5.0f);
                ImGui::Text("%s", meshBrowser.GetSelected().filename().string().c_str());
            }
        }

        if(ImGui::CollapsingHeader("Skybox"))
        {
            if(ImGui::Button("Open##Skybox"))
                skyboxBrowser.Open();
        }

        meshBrowser.Display();
        if(meshBrowser.HasSelected())
        {
            auto filePath = meshBrowser.GetSelected().string();
            std::ranges::replace(filePath, '\\', '/');
            Scene::sceneData.models.emplace_back(std::make_shared<Model>(filePath));

            meshBrowser.ClearSelected();
        }

        skyboxBrowser.Display();
        if(skyboxBrowser.HasSelected())
        {
            auto filePaths = skyboxBrowser.GetMultiSelected();
            std::unordered_map<CubeFace, std::string> skybox;

            for (auto& filePath: filePaths)
            {
                auto filename = filePath.filename().string();
                auto name = filename.substr(0, filename.find_first_of('.'));

                if(name == "right" || name == "posx")
                    skybox[CubeFace::RIGHT] = filePath.string();
                else if(name == "left" || name == "negx")
                    skybox[CubeFace::LEFT] = filePath.string();
                else if(name == "top" || name == "posy")
                    skybox[CubeFace::TOP] = filePath.string();
                else if(name == "bottom" || name == "negy")
                    skybox[CubeFace::BOTTOM] = filePath.string();
                else if(name == "front" || name == "posz")
                    skybox[CubeFace::FRONT] = filePath.string();
                else if(name == "back" || name == "negz")
                    skybox[CubeFace::BACK] = filePath.string();
            }

            Scene::sceneData.skybox = std::make_shared<Skybox>(skybox);
            skyboxBrowser.ClearSelected();
        }

        if(ImGui::CollapsingHeader("Scene options"))
        {
            ImGui::ColorEdit3("Scene background color", &Scene::properties.background.r);
            ImGui::Checkbox("Wireframe mode", &Scene::properties.wireframe);
            toggleButton("2D mode", &Scene::properties.render2D);

            ImGui::Combo("Postprocessing", &selectedFlag, &ppFlagsStrs[0], ppFlagsStrs.size());
            Scene::properties.ppFlag = PostProcessingFlags(selectedFlag);
            ImGui::SliderFloat("Separator", &Scene::properties.ppSeparator, 0.f, (float)Application::get().getWindow().getWidth());
        }
        ImGui::End();
    }
}
