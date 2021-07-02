
#pragma once

#include "srspch.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Sirius
{
    /////////////////////////////////////////////////////////
    /// @brief Rendering context abstraction class
    ///
    /// This class serves to set up the OpenGL rendering
    /// context (the window on which to render, for app).
    class RenderContext
    {
        private:

            GLFWwindow* window;

        public:

            //////////////////////////////////////////////////////
            /// @brief Sets up the OpenGL's context
            ///
            /// The passed window and GLAD are bound to GLFW,
            /// then some graphic driver's information is printed.
            /// 
            /// @param window The window on which to render
            RenderContext(GLFWwindow* window);

            /////////////////////////////////////////
            /// @brief Swap the GPU buffers
            void swapBuffers();
    };
}
