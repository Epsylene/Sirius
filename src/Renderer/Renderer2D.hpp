
#pragma once

#include "Core/Core.hpp"

#include "Renderer/Objects/Camera.hpp"
#include "Renderer/Utils/Texture.hpp"
#include "Renderer/Utils/Color.hpp"

#include "Math/Math.hpp"

namespace Sirius
{
    enum class Shapes
    {
        QUAD, CIRCLE
    };

    /// @brief 2D renderer class
    class Renderer2D
    {
        public:

            /// @brief Initialize the 2D renderer
            static void init();

            /// @brief Shutdown the 2D renderer
            static void shutdown();

            /// @brief Begin a 2D scene
            ///
            /// @param camera The 2D camera attached to the scene
            /// @see Camera2D
            static void beginScene(const Camera2D& camera);

            /// @brief End a 2D scene
            static void endScene();

            /// @brief Draw a colored shape
            ///
            /// @param pos 2D position of the shape
            /// @param size Size of the shape
            /// @param color Color of the shape
            static void drawShape(Shapes shape, const Vec2& pos, const Vec2& size, const Color& color);

            /// @brief Draw a colored quad
            ///
            /// @param pos 2D position of the quad
            /// @param size Size of the quad
            /// @param color Color of the quad
            static void drawQuad(const Vec2& pos, const Vec2& size, const Color& color);

            /// @brief Draw a colored circle
            ///
            /// @param pos 2D position of the circle
            /// @param size Size of the circle
            /// @param color Color of the circle
            static void drawCircle(const Vec2& pos, const Vec2& size, const Color& color);
    };
}
