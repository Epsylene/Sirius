
#pragma once

#include "Event.h"

namespace Sirius
{
    ////////////////////////////////////////////////
    /// @brief Event class to handle a window resize
    class WindowResizeEvent: public Event
    {
        private:

            unsigned int width, height;

        public:

            ///////////////////////////////////
            /// @brief Default constructor
            /// @param width The resize width
            /// @param height The resize height
            WindowResizeEvent(unsigned int width, unsigned int height):
                width(width), height(height) {}

            /////////////////////////////////////////
            /// @brief Get the resized window's width
            /// @return The window resize width
            inline unsigned int getWidth() const { return width; }

            //////////////////////////////////////////
            /// @brief Get the resized window's height
            /// @return The window resize height
            inline unsigned int getHeight() const { return height; }

            EVENT_CLASS_TYPE(WindowResize);

            std::string toString() const override
            {
                std::stringstream ss;
                ss << "WindowResizeEvent: " << width << ", " << height;
                return ss.str();
            }
    };

    ///////////////////////////////////////////////
    /// @brief Event class to handle a window close
    class WindowCloseEvent: public Event
    {
        public:

            WindowCloseEvent() {}

            EVENT_CLASS_TYPE(WindowClose);
    };
}
