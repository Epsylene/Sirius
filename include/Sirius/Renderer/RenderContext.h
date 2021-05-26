
#pragma once

#include "srspch.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Sirius
{
    //////////////////////////////////////////////
    /// @brief Rendering context abstraction class
    ///
    /// This class handles
    class RenderContext
    {
        private:

            GLFWwindow* window;

        public:

            ///////////////////////////////////////////////
            /// @brief Main constructor
            /// 
            /// @param window The window on which to render
            RenderContext(GLFWwindow* window);

            /////////////////////////////////////////
            /// @brief Swap the GPU buffers
            void swapBuffers();
    };
}
