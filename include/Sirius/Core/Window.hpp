
#pragma once

#include <GLFW/glfw3.h>

#include "srspch.hpp"

#include "Sirius/Core/Timestep.hpp"
#include "Sirius/Events/Event.hpp"
#include "Sirius/Renderer/RenderContext.hpp"
#include "Sirius/Renderer/Utils/Buffer.hpp"
#include "Sirius/Renderer/Utils/Shader.hpp"

namespace Sirius
{
    //////////////////////////////////////////
    /// @brief Window properties handler class
    struct WindowProps
    {
        std::string title;
        unsigned int width, height;

        /////////////////////////////////////
        /// @brief Default constructor
        ///
        /// @param title The window's title
        /// @param width The window's width
        /// @param height The window's height
        explicit WindowProps(const std::string& title = "Sirius Engine", unsigned int width = 1024, unsigned int height = 576):
            title(title), width(width), height(height) {}
    };

    ///////////////////////////
    /// @brief Window interface
    class Window
    {
        private:

            GLFWwindow* window;
            RenderContext* context;

            ////////////////////////////////////////////////////
            /// @brief Event callback function
            /// 
            /// Alias for a void function that takes in an event
            /// reference, like an onEvent() function.
            using EventCallbackFn = std::function<void(Event&)>;

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

            ///////////////////////////////////////////////
            /// @brief Function that terminates the window
            void shutdown();

        public:

            Scope<FrameBuffer> preRenderFBO;
            Scope<FrameBuffer> postRenderFBO;

            //////////////////////////////////////////
            /// @brief The default constructor
            ///
            /// @param wp The window properties object
            /// @see WindowProps class, Window interface
            explicit Window(const WindowProps& wp = WindowProps());

            //////////////////////////////
            /// @brief Get the GLFW window
            inline GLFWwindow* getNativeWindow() const { return window; }

            /////////////////////////////////////////////////
            /// @brief Function called on the window's update
            void onUpdate(Timestep dt);

            /////////////////////////////////
            /// @brief Get the window's width
            ///
            /// @return The window's width
            inline unsigned int getWidth() const { return windowData.width; }

            //////////////////////////////////
            /// @brief Get the window's height
            ///
            /// @return The window's height
            inline unsigned int getHeight() const { return windowData.height; }

            ///////////////////////////////////////////////
            /// @brief Set the event callback
            ///
            /// @param callback The event callback function
            /// @see EventCallbackFn
            inline void setEventCallback(const EventCallbackFn& callback) { windowData.eventCallback = callback; }

            ///////////////////////////////////////////////////
            /// @brief Set the v-sync
            ///
            /// @param enabled True to enable, false to disable
            void setVSync(bool enabled);

            /////////////////////////////////////////////
            /// @brief Returns true if v-sync is enabled
            bool vSync() const;
    };
}