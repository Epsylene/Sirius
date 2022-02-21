

#include "RenderContext.hpp"
#include "../Core/Core.hpp"

#include <glad/glad.h>

namespace Sirius
{
    RenderContext::RenderContext(GLFWwindow* window): window(window)
    {
        SRS_CORE_ASSERT(window, "Window handle is null !")

        // Bind the window to GLFW
        glfwMakeContextCurrent(window);

        // Binds GLAD to GLFW's OpenGL context
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        SRS_CORE_ASSERT(status, "Failed to initialize GLAD.");

        Log::info(LogChannel::CORE, "OpenGL info: {}");
        Log::info(LogChannel::CORE, "  Vendor: {0}", glGetString(GL_VENDOR));
        Log::info(LogChannel::CORE, "  Renderer: {0}", glGetString(GL_RENDERER));
        Log::info(LogChannel::CORE, "  Version: {0}", glGetString(GL_VERSION));
    }

    void RenderContext::swapBuffers()
    {
        glfwSwapBuffers(window);
    }
}
