
#include "Sirius/Core/Input.hpp"
#include "Sirius/Core/Application.hpp"

namespace Sirius
{
    std::unique_ptr<Input> Input::instance = std::make_unique<Input>();

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

    Vec2 Input::getMousePos()
    {
        auto window = Application::get().getWindow().getNativeWindow();
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        return {(float)xPos, (float)yPos};
    }
}
