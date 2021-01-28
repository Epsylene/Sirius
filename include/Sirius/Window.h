
#pragma once

#include "srspch.h"
#include "Sirius/Events/Event.h"

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
        WindowProps(const std::string& title = "Sirius Engine", unsigned int width = 1024, unsigned int height = 576):
            title(title), width(width), height(height) {}
    };

    ///////////////////////////
    /// @brief Window interface
    class Window
    {
        public:

            /////////////////////////////////////////////////
            /// @brief Function called on the window's update
            virtual void onUpdate() = 0;

            /////////////////////////////////
            /// @brief Get the window's width
            ///
            /// @return The window's width
            virtual unsigned int getWidth() const = 0;

            //////////////////////////////////
            /// @brief Get the window's height
            ///
            /// @return The window's height
            virtual unsigned int getHeight() const = 0;

            ////////////////////////////////////////////////////
            /// @brief Event callback function
            /// 
            /// Alias for a void function that takes in an event
            /// reference, like an onEvent() function.
            using EventCallbackFn = std::function<void(Event&)>;

            ///////////////////////////////////////////////
            /// @brief Set the event callback
            ///
            /// @param callback The event callback function
            /// @see EventCallbackFn
            virtual void setEventCallback(const EventCallbackFn& callback) = 0;

            ///////////////////////////////////////////////////
            /// @brief Set the v-sync
            ///
            /// @param enabled True to enable, false to disable
            virtual void setVSync(bool enabled) = 0;

            /////////////////////////////////////////////
            /// @brief Returns true if v-sync is enabled
            ///
            /// @return Is v-sync enabled ?
            virtual bool vSync() const = 0;

            ////////////////////////////////////////////
            /// @brief Create the window
            ///
            /// @param props The window properties
            /// @return A pointer to the created window
            static Window* create(const WindowProps& props = WindowProps());
    };
}