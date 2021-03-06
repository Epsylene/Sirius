
#pragma once

#include "Objects/Camera.hpp"
#include "Utils/Color.hpp"
#include "Utils/Texture.hpp"
#include "Utils/Material.hpp"
#include "Objects/Light.hpp"
#include "Objects/Model.hpp"
#include "Objects/Skybox.hpp"

namespace Sirius
{
    enum class DrawMode
    {
        TEXTURE, REFLECTION, REFRACTION, EMISSION
    };

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
            static void drawModel(const Ref <Model>& model, DrawMode mode, const Vec3& pos = {}, const Vec3& size = Vec3(1.f), bool outline = true);

            ////////////////////////////////
            /// @brief Draw the scene skybox
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
