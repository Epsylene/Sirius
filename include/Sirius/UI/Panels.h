
#pragma once

#include <imgui.h>
#include <filebrowser/imfilebrowser.h>

namespace Sirius
{
    /////////////////////////////////////////////////
    /// @brief "Properties" panel class
    ///
    /// This class handles the "Properties" panel,
    /// where the object loading and the object/scene
    /// properties are located.
    class PropertiesPanel
    {
        public:

            static ImGui::FileBrowser fileBrowser;

            ///////////////////////////////
            /// @brief Initialize the panel
            static void init();

            ///////////////////////////
            /// @brief Render the panel
            static void render();
    };
}
