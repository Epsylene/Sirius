
#pragma once

#include "srspch.h"
#include "GLFW/glfw3.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

namespace Sirius
{
    //////////////////////////////////////////////////
    /// @brief Windows implementation of the abstract
    ///     Window  class
    class WindowsWindow: public Window
    {
        private:

            GLFWwindow* window;

            ////////////////////////////////////////////
            /// @brief Struct holding the window's data
            struct WindowData
            {
                std::string title;
                unsigned int width, height;
                bool vSync;

                EventCallbackFn eventCallback;
            };

            WindowData windowData;

            ////////////////////////////////////////////
            /// @brief Function that creates the window
            /// @param wp The window properties
            virtual void init(const WindowProps& wp);

            ///////////////////////////////////////////////
            /// @brief Function that terminates the window
            virtual void shutdown();

        public:

            //////////////////////////////////////////
            /// @brief The default constructor
            /// @param wp The window properties object
            /// @see WindowProps class
            WindowsWindow(const WindowProps& wp);

            void onUpdate() override;

            inline unsigned int getWidth() const override { return windowData.width; }
            inline unsigned int getHeight() const override { return windowData.height; }

            void setEventCallback(const EventCallbackFn& callback) override { windowData.eventCallback = callback; }

            void setVSync(bool enabled) override;
            bool vSync() const override;
    };
}
