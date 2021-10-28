
#pragma once

#include "Sirius/Core/Core.hpp"

#include "Sirius/Renderer/Objects/Camera.hpp"
#include "Sirius/Renderer/Utils/Texture.hpp"
#include "Sirius/Renderer/Utils/Color.hpp"

#include "Sirius/Math/Vector/Vector.hpp"

namespace Sirius
{
    ////////////////////////////
    /// @brief 2D renderer class
    class Renderer2D
    {
        public:

            //////////////////////////////////////
            /// @brief Initialize the 2D renderer
            static void init();

            //////////////////////////////////////
            /// @brief Shutdown the 2D renderer
            static void shutdown();

            /////////////////////////////////////////////////////
            /// @brief Begin a 2D scene
            ///
            /// @param camera The 2D camera attached to the scene
            /// @see Camera2D
            static void beginScene(const Camera2D& camera);

            /////////////////////////
            /// @brief End a 2D scene
            static void endScene();

            //////////////////////////////////////
            /// @brief Draw a colored renderQuad
            ///
            /// @param pos 2D position of the renderQuad
            /// @param size Size of the renderQuad
            /// @param color Color of the renderQuad
            static void drawQuad(const Vec2& pos, const Vec2& size, const Color& color);

            //////////////////////////////////////
            /// @brief Draw a colored renderQuad
            ///
            /// @param pos 3D position of the renderQuad
            /// @param size Size of the renderQuad
            /// @param color Color of the renderQuad
            static void drawQuad(const Vec3& pos, const Vec2& size, const Color& color);

            //////////////////////////////////////
            /// @brief Draw a textured renderQuad
            ///
            /// @param pos 2D position of the renderQuad
            /// @param size Size of the renderQuad
            /// @param texture Texture of the renderQuad
            static void drawQuad(const Vec2& pos, const Vec2& size, const Ref<Texture2D>& texture);

            //////////////////////////////////////
            /// @brief Draw a textured renderQuad
            ///
            /// @param pos 3D position of the renderQuad
            /// @param size Size of the renderQuad
            /// @param texture Texture of the renderQuad
            static void drawQuad(const Vec3& pos, const Vec2& size, const Ref<Texture2D>& texture);
    };
}
