
#include "Core.hpp"
#include "Window.hpp"

#include "Events/ApplicationEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"

#include "Core/Logger/Logger.hpp"

namespace Sirius
{
    static bool glfwInitialized = false;

    static void glfwErrorCallback(int error, const char* description)
    {
        Logger::error(LogChannel::CORE, "GLFW error ({0}): {1}", error, description);
    }

    Window::Window(const WindowProps& wp)
    {
        // Window properties setup

        windowData.title = wp.title;
        windowData.width = wp.width;
        windowData.height = wp.height;

        Logger::info(LogChannel::CORE, "Creating window {} ({}x{})", wp.title, wp.width, wp.height);

        // GLFW initialization check

        if(!glfwInitialized)
        {
            SRS_CORE_ASSERT(glfwInit(), "Could not initialize GLFW !");

            glfwSetErrorCallback(glfwErrorCallback);
            glfwInitialized = true;
        }

        // Window and render context creation

        window = glfwCreateWindow((int)wp.width, (int)wp.height, wp.title.c_str(), nullptr, nullptr);
        context = new RenderContext(window);

        glfwSetWindowUserPointer(window, &windowData);

        setVSync(true);

        // GLFW window callback functions setup

        glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.width = width;
            data.height = height;

            WindowResizeEvent event(width, height);
            data.eventCallback(event);
        });

        glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowCloseEvent event {};
            data.eventCallback(event);
        });

        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch(action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.eventCallback(event);
                    break;
                }

                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.eventCallback(event);
                    break;
                }

                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.eventCallback(event);
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch(action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.eventCallback(event);
                    break;
                }

                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.eventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.eventCallback(event);
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.eventCallback(event);
        });
    }

    void Window::shutdown()
    {
        glfwDestroyWindow(window);
        window = nullptr;
        context = nullptr;
    }

    void Window::onUpdate(Timestep dt)
    {
        glfwPollEvents();
        context->swapBuffers();
    }

    void Window::setVSync(bool enabled)
    {
        enabled ? glfwSwapInterval(1) : glfwSwapInterval(0);
        windowData.vSync = enabled;
    }

    bool Window::vSync() const
    {
        return windowData.vSync;
    }
}
