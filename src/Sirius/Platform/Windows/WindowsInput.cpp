
#include "Sirius/Platform/Windows/WindowsInput.h"

namespace Sirius
{
    Input* Input::instance = new WindowsInput();

    bool WindowsInput::isKeyPressed(int keyCode)
    {
        auto window = static_cast<GLFWwindow*>(Simulation::get().getWindow().getNativeWindow());
        auto state = glfwGetKey(window, keyCode);

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::isMouseButtonPressed(int button)
    {
        auto window = static_cast<GLFWwindow*>(Simulation::get().getWindow().getNativeWindow());
        auto state = glfwGetMouseButton(window, button);

        return state == GLFW_PRESS;
    }

    float WindowsInput::getMouseX()
    {
        auto window = static_cast<GLFWwindow*>(Simulation::get().getWindow().getNativeWindow());
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        return (float)xPos;
    }

    float WindowsInput::getMouseY()
    {
        auto window = static_cast<GLFWwindow*>(Simulation::get().getWindow().getNativeWindow());
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        return (float)yPos;
    }

    std::pair<float, float> WindowsInput::getMousePos()
    {
        auto window = static_cast<GLFWwindow*>(Simulation::get().getWindow().getNativeWindow());
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        return { (float)xPos, (float)yPos };
    }
}
