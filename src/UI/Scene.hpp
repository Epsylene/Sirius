
#pragma once

#include "Renderer/Objects/Skybox.hpp"
#include "Math/Math.hpp"
#include "Renderer/Objects/CameraController.hpp"
#include "Renderer/Objects/Model.hpp"
#include "Renderer/Renderer.hpp"

namespace Sirius
{
    struct SceneProperties
    {
        bool active;
        bool render2D = false;
        Color background;
        bool wireframe;
        PostProcessingFlags ppFlag;
        float ppSeparator;
    };

    struct SceneData
    {
        std::vector<Ref<Model>> models;
        Ref<CameraController2D> controller2D;
        Ref<CameraController3D> controller3D;
        Ref<Skybox> skybox;
    };

    ////////////////////////////////////////////
    /// @brief "Scene" panel class
    ///
    /// This is a static class representing the
    /// "Scene" panel, and thus the rendering
    /// scene, that is, not the actual rendering
    /// but how it is presented and processed.
    class Scene
    {
        public:

            static SceneProperties properties;
            static SceneData sceneData;

            Scene() = delete;

            ////////////////////////////////
            /// @brief Initialize the scene
            static void init();

            ////////////////////////////////////////
            /// @brief Render the ImGui scene panel
            ///
            /// The rendered color buffer is applied
            /// on an ImGui::Image().
            static void render();

            ///////////////////////////
            /// @brief Update the scene
            static void onUpdate(Timestep dt);
    };
}
