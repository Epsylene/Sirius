
#include "Sirius/UI/Panels.hpp"

#include "Sirius/UI/Scene.hpp"
#include "Sirius/Core/Core.hpp"
#include "Sirius/Renderer/Utils/Texture.hpp"
#include "Sirius/Renderer/Renderer3D.hpp"
#include "Sirius/Core/Application.hpp"

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
            ImGui::Checkbox("2D mode", &Scene::properties.render2D);

            ImGui::Combo("Postprocessing", &selectedFlag, &ppFlagsStrs[0], ppFlagsStrs.size());
            Scene::properties.ppFlag = PostProcessingFlags(selectedFlag);
            ImGui::SliderFloat("Separator", &Scene::properties.ppSeparator, 0.f, (float)Application::get().getWindow().getWidth());
        }
        ImGui::End();
    }
}
