
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

    Vec2 Input::getMouseScreenPos()
    {
        auto window = Application::get().getWindow().getNativeWindow();
        double xPos, yPos;
        int xWindowPos, yWindowPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        glfwGetWindowPos(window, &xWindowPos, &yWindowPos);

        return {(float)(xWindowPos + xPos), (float)(yWindowPos + yPos)};
    }

    bool Input::mouseInArea(const Vec2& p0, const Vec2& p1, bool screenCoords)
    {
        auto mousePos = screenCoords ? getMouseScreenPos() : getMousePos();

        return (mousePos.x > p0.x && mousePos.x < p1.x && mousePos.y > p0.y && mousePos.y < p1.y);
    }
}
