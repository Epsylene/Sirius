
#pragma once

#include "Camera.hpp"
#include "Color.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "Light.hpp"
#include "Model.hpp"

namespace Sirius
{
    ////////////////////////////
    /// @brief 3D renderer class
    class Renderer3D
    {
        public:

            //////////////////////////////////////
            /// @brief Initialize the 3D renderer
            static void init();

            //////////////////////////////////////
            /// @brief Shutdown the 3D renderer
            static void shutdown();

            /////////////////////////////////////////////////////
            /// @brief Begin a 3D scene
            ///
            /// @param camera The 3D camera attached to the scene
            /// @see Camera3D
            static void beginScene(const Camera3D& camera);

            /////////////////////////
            /// @brief End a 3D scene
            static void endScene();

            ///////////////////////////////////
            /// @brief Draw a flat-colored cube
            ///
            /// @param pos The cube's position
            /// @param size The cube's size
            /// @param color The cube's color
            static void drawCube(const Vec3& pos, const Vec3& size = {1.f, 1.f, 1.f}, const Color& color = Color::White);

            //////////////////////////////////////
            /// @brief Draw a cube with a material
            ///
            /// @param pos The cube's position
            /// @param size The cube's size
            /// @param material The cube's material
            static void drawCube(const Vec3& pos, const Vec3& size, const Material& material);

            static void drawEmissionCube(const PointLight& light);

            static void addModel(const Model& model);

            static void drawModel(const Model& model, const Vec3& pos = {}, const Vec3& size = Vec3(1.f));

            static void addPointLight(const PointLight& ptLight);

            static void setDirectionalLight(const DirectionalLight& dirLight);

            static void setSpotlight(const Spotlight& spotlight);
    };
}
