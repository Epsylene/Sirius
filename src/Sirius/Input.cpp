
#include <GLFW/glfw3.h>

#include "Sirius/Input.h"
#include "Sirius/Simulation.h"

namespace Sirius
{
    Input* Input::instance = new Input();

    bool Input::isKeyPressed(int keyCode)
    {
        auto window = static_cast<GLFWwindow*>(Simulation::get().getWindow().getNativeWindow());
        auto state = glfwGetKey(window, keyCode);

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::isMouseButtonPressed(int button)
    {
        auto window = static_cast<GLFWwindow*>(Simulation::get().getWindow().getNativeWindow());
        auto state = glfwGetMouseButton(window, button);

        return state == GLFW_PRESS;
    }

    float Input::getMouseX()
    {
        auto window = static_cast<GLFWwindow*>(Simulation::get().getWindow().getNativeWindow());
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        return (float)xPos;
    }

    float Input::getMouseY()
    {
        auto window = static_cast<GLFWwindow*>(Simulation::get().getWindow().getNativeWindow());
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        return (float)yPos;
    }

    std::pair<float, float> Input::getMousePos()
    {
        auto window = static_cast<GLFWwindow*>(Simulation::get().getWindow().getNativeWindow());
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        return { (float)xPos, (float)yPos };
    }
}
