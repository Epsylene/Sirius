
#include "Sirius/Core/Input.h"
#include "Sirius/Core/Application.h"

namespace Sirius
{
    Input* Input::instance = new Input();

    bool Input::isKeyPressed(int keyCode)
    {
        auto window = Application::get().getWindow().getNativeWindow();
        auto state = glfwGetKey(window, keyCode);

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::isMouseButtonPressed(int button)
    {
        auto window = Application::get().getWindow().getNativeWindow();
        auto state = glfwGetMouseButton(window, button);

        return state == GLFW_PRESS;
    }

    float Input::getMouseX()
    {
        auto window = Application::get().getWindow().getNativeWindow();
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        return (float)xPos;
    }

    float Input::getMouseY()
    {
        auto window = Application::get().getWindow().getNativeWindow();
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        return (float)yPos;
    }

    glm::vec2 Input::getMousePos()
    {
        auto window = Application::get().getWindow().getNativeWindow();
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        return {(float)xPos, (float)yPos};
    }
}
