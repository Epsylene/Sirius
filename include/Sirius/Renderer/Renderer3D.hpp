
#pragma once

#include "Sirius/Renderer/Objects/Camera.hpp"
#include "Sirius/Renderer/Utils/Color.hpp"
#include "Sirius/Renderer/Utils/Texture.hpp"
#include "Sirius/Renderer/Utils/Material.hpp"
#include "Sirius/Renderer/Objects/Light.hpp"
#include "Sirius/Renderer/Objects/Model.hpp"
#include "Sirius/Renderer/Objects/Skybox.hpp"

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

            ////////////////////////////////////
            /// @brief Draw a cube emiting light
            static void drawEmissionCube(const PointLight& light);

            //////////////////////////////////////////////////
            /// @brief Draw the model at `pos` and with `size`
            static void drawModel(const Ref<Model>& model, const Vec3& pos = {}, const Vec3& size = Vec3(1.f), bool outline = true);

            static void setSkybox(const std::unordered_map<CubeFace, std::string>& skybox);

            static void drawSkybox();

            ////////////////////////////
            /// @brief Add a point light
            ///
            /// @see PointLight class
            static void addPointLight(const PointLight& ptLight);

            ////////////////////////////////////
            /// @brief Set the directional light
            ///
            /// @see DirectionalLight class
            static void setDirectionalLight(const DirectionalLight& dirLight);

            ////////////////////////////
            /// @brief Set the spotlight
            ///
            /// @see Spotlight class
            static void setSpotlight(const Spotlight& spotlight);
    };
}
