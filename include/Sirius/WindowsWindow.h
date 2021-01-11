
#pragma once

#include "srspch.h"
#include "GLFW/glfw3.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

namespace Sirius
{
    class WindowsWindow: public Window
    {
        private:

            GLFWwindow* window;

            struct WindowData
            {
                std::string title;
                unsigned int width, height;
                bool vSync;

                EventCallbackFn eventCallback;
            };

            WindowData windowData;

            virtual void init(const WindowProps& wp);
            virtual void shutdown();

        public:

            WindowsWindow(const WindowProps& wp);
            virtual ~WindowsWindow();

            void onUpdate() override;

            inline unsigned int getWidth() const override {return windowData.width; }
            inline unsigned int getHeight() const override {return windowData.height; }

            void setEventCallback(const EventCallbackFn& callback) override { windowData.eventCallback = callback; }

            void setVSync(bool enabled) override;
            bool vSync() const override;
    };
}
