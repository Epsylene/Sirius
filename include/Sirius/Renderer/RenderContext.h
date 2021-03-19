
#pragma once

#include "srspch.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Sirius
{
    class RenderContext
    {
        private:

            GLFWwindow* window;

        public:

            RenderContext(GLFWwindow* window);

            void init();
            void swapBuffers();
    };
}
