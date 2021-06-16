
#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Sirius
{
    ///////////////////////////////////////
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
            static void clear();

            /////////////////////////////////////
            /// @brief Set the window clear color
            static void setClearColor(const glm::vec4& color);

            static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

            ////////////////////////////////
            /// @brief Draw the vertex array
            static void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray);
    };
}
