
#pragma once

#include "Sirius/Math/Vector/Vector.hpp"
#include "Sirius/Renderer/Objects/CameraController.hpp"
#include "Sirius/Renderer/Objects/Model.hpp"

namespace Sirius
{
    class Scene
    {
        public:

            static bool mouseInArea;
            static std::vector<Ref<Model>> models;
            static Ref<CameraController3D> controller;

            Scene() = delete;

            static void init();

            static void render();

            static void drawModel(const Ref<Model>& model);
    };
}
