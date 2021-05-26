
#include "Sirius/Renderer/RenderContext.h"
#include "Sirius/Core.h"

namespace Sirius
{
    RenderContext::RenderContext(GLFWwindow* window): window(window)
    {
        SRS_CORE_ASSERT(window, "Window handle is null !")

        glfwMakeContextCurrent(window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        SRS_CORE_ASSERT(status, "Failed to initialize GLAD.");

        SRS_CORE_INFO("OpenGL info:");
        SRS_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
        SRS_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
        SRS_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
    }

    void RenderContext::swapBuffers()
    {
        glfwSwapBuffers(window);
    }
}
