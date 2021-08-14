
#pragma once

#include "Sirius/Math/Vector/Vector.hpp"
#include "Sirius/Renderer/Objects/CameraController.hpp"
#include "Sirius/Renderer/Objects/Model.hpp"
#include "Sirius/Renderer/Renderer.hpp"

namespace Sirius
{
    struct SceneProperties
    {
        Vec2 pos, size;
        Color background;
        bool wireframe;
        PostProcessingFlags ppFlag;
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

            static std::vector<Ref<Model>> models;
            static Ref<CameraController3D> controller;

            Scene() = delete;

            ////////////////////////////////
            /// @brief Initialize the scene
            static void init();

            ///////////////////////////////////////
            /// @brief Render the ImGui scene panel
            ///
            /// The rendered color buffer is applied
            /// on an ImGui::Image().
            static void render();

            ///////////////////////////
            /// @brief Update the scene
            static void onUpdate(Timestep dt);

            ////////////////////////////////////
            /// @brief Draw a model in the scene
            static void drawModel(const Ref<Model>& model, const Vec3& pos = {}, const Vec3& size = Vec3(1.f));
    };
}
