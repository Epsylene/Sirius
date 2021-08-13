
#pragma once

#include "Sirius/Math/Vector/Vector.hpp"
#include "Sirius/Renderer/Objects/CameraController.hpp"
#include "Sirius/Renderer/Objects/Model.hpp"
#include "Sirius/Renderer/Renderer.hpp"

namespace Sirius
{
    struct SceneProperties
    {
        Color background;
        bool wireframe;
        PostProcessingFlags ppFlag;
    };

    class Scene
    {
        public:

            static bool mouseInArea;
            static SceneProperties properties;
            static std::vector<Ref<Model>> models;
            static Ref<CameraController3D> controller;

            Scene() = delete;

            static void init();

            static void render();

            static void onUpdate(Timestep dt);

            static void drawModel(const Ref<Model>& model, const Vec3& pos = {}, const Vec3& size = Vec3(1.f));
    };
}
