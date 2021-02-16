
#include "Sirius/Platform/Windows/WindowsWindow.h"

namespace Sirius
{
    static bool glfwInitialized = false;

    static void glfwErrorCallback(int error, const char* description)
    {
        std::cout << "GLFW error (" << error << "): " << description;
    }

    Window* Window::create(const WindowProps& props)
    {
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& wp)
    {
        init(wp);
    }

    void WindowsWindow::init(const WindowProps& wp)
    {
        windowData.title = wp.title;
        windowData.width = wp.width;
        windowData.height = wp.height;

        std::cout << "Creating window " << wp.title << " ("
            << wp.width << "x" << wp.height << ")\n";

        if(!glfwInitialized)
        {
            int success = glfwInit();
            if(!success)
                std::cout << "Could not initialize GLFW !\n";

            glfwSetErrorCallback(glfwErrorCallback);
            glfwInitialized = true;
        }

        window = glfwCreateWindow((int)wp.width, (int)wp.height, wp.title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(window);
        glfwSetWindowUserPointer(window, &windowData);
        setVSync(true);

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

    void WindowsWindow::shutdown()
    {
        glfwDestroyWindow(window);
    }

    void WindowsWindow::onUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    void WindowsWindow::setVSync(bool enabled)
    {
        if(enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        windowData.vSync = enabled;
    }

    bool WindowsWindow::vSync() const
    {
        return windowData.vSync;
    }

    void* WindowsWindow::getNativeWindow() const
    {
        return window;
    }
}
