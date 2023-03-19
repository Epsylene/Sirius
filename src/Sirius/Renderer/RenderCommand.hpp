
#pragma once

#include "Utils/VertexArray.hpp"
#include "Utils/Color.hpp"
#include "Sirius/Math/Math.hpp"

namespace Sirius
{
    enum ClearBuffers: uint32_t
    {
        COLOR_BUFFER = GL_COLOR_BUFFER_BIT,
        DEPTH_BUFFER = GL_DEPTH_BUFFER_BIT,
        STENCIL_BUFFER = GL_STENCIL_BUFFER_BIT
    };

    enum class Primitives
    {
        TRIANGLES = GL_TRIANGLES,
        POINTS = GL_POINTS,
        LINES = GL_LINES
    };

    ////////////////////////////////////////////////////
    /// @brief OpenGL render commands class
    ///
    /// This class provides functions to execute several
    /// OpenGL render commands, like clearing the window
    /// or drawing an indexed vertex array.
    class RenderCommand
    {
        public:

            ////////////////////////////////////
            /// @brief Run init render commands
            static void init();

            ///////////////////////////
            /// @brief Clear the window
            static void clear(uint32_t flags = COLOR_BUFFER | DEPTH_BUFFER | STENCIL_BUFFER);

            /////////////////////////////////////////////
            /// @brief Enable or disable the depth buffer
            static void setDepthTest(bool state);

            /////////////////////////////////////////
            /// @brief Enable or disable face culling
            static void setFaceCulling(bool state);

            ////////////////////////////////////////////////
            /// @brief Enable or disable wireframe rendering
            static void setWireframeMode(bool state);

            /////////////////////////////////////
            /// @brief Set the window clear color
            static void setClearColor(const Color& color);

            /////////////////////////////////////////////////////////
            /// @brief Set the rendering viewport
            ///
            /// @param x, y Coordinates of the top-left corner of the
            ///     rendering viewport
            /// @param width The rendering viewport's width
            /// @param height The rendering viewport's height
            static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

            ////////////////////////////////
            /// @brief Draw the vertex array
            static void drawIndexed(const Ref <VertexArray>& vertexArray, Primitives drawPrimitive = Primitives::TRIANGLES);
    };
}
