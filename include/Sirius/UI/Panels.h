
#pragma once

#include <imgui.h>
#include <filebrowser/imfilebrowser.h>

namespace Sirius
{
    class PropertiesPanel
    {
        public:

            static ImGui::FileBrowser fileBrowser;

            static void render();
    };
}
