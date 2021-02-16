
#pragma once

#include "srspch.h"
#include "GLFW/glfw3.h"
#include "Sirius/Window.h"
#include "Sirius/Events/ApplicationEvent.h"
#include "Sirius/Events/KeyEvent.h"
#include "Sirius/Events/MouseEvent.h"

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
            ///
            /// @param wp The window properties
            virtual void init(const WindowProps& wp);

            ///////////////////////////////////////////////
            /// @brief Function that terminates the window
            virtual void shutdown();

        public:

            //////////////////////////////////////////
            /// @brief The default constructor
            ///
            /// @param wp The window properties object
            /// @see WindowProps class, Window interface
            WindowsWindow(const WindowProps& wp);

            /////////////////////////////////////////////////
            /// @brief Function called on the window's update
            void onUpdate() override;

            ///////////////////////////////
            /// @brief Get the window width
            ///
            /// @return The window width
            inline unsigned int getWidth() const override { return windowData.width; }
            
            ////////////////////////////////
            /// @brief Get the window height
            /// 
            /// @return The window height
            inline unsigned int getHeight() const override { return windowData.height; }

            //////////////////////////////////////////////////
            /// @brief Set the generic event callback function
            ///
            /// @param callback The event callback function
            void setEventCallback(const EventCallbackFn& callback) override { windowData.eventCallback = callback; }

            ///////////////////////////////////////////////////
            /// @brief Set the v-sync
            ///
            /// @param enabled True to enable, false to disable
            void setVSync(bool enabled) override;

            /////////////////////////////////////////////
            /// @brief Returns true if v-sync is enabled
            bool vSync() const override;

            //////////////////////////////////////////
            /// @brief Get the system's native windows
            ///     (OpenGL, DirectX, etc)
            void* getNativeWindow() const override;
    };
}
