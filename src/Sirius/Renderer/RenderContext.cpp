
#include "Sirius/Renderer/RenderContext.h"

namespace Sirius
{
    RenderContext::RenderContext(GLFWwindow* window): window(window)
    {
        if(!window)
            std::cout << "ERORR: Window handle is null !";
    }

    void RenderContext::init()
    {
        glfwMakeContextCurrent(window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        std::cout << "OpenGL info:\n";
        std::cout << "  Vendor: " << glGetString(GL_VENDOR);
        std::cout << "  Renderer: " << glGetString(GL_RENDERER);
        std::cout << "  Version: " << glGetString(GL_VERSION);
    }

    void RenderContext::swapBuffers()
    {
        glfwSwapBuffers(window);
    }
}
