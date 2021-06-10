
#pragma once

#include "Event.h"

namespace Sirius
{
    ////////////////////////////////////////////
    /// @brief Class to handle mouse move events
    class MouseMovedEvent: public Event
    {
        private:

            float mouseX, mouseY;

        public:

            /////////////////////////////////
            /// @brief Default constructor
            /// @param x The mouse X position
            /// @param y The mouse Y position
            MouseMovedEvent(float x, float y): mouseX(x), mouseY(y) {}

            ///////////////////////////////////
            /// @brief Get the mouse X position
            /// @return The mouse X position
            inline float getX() const { return mouseX; }

            ///////////////////////////////////
            /// @brief Get the mouse Y position
            /// @return The mouse Y position
            inline float getY() const { return mouseY; }

            EVENT_CLASS_TYPE(MouseMoved);

            std::string toString() const override
            {
                std::stringstream ss;
                ss << "MouseMovedEvent: (" << mouseX << ", "
                   << mouseY << ")";
                return ss.str();
            }
    };

    //////////////////////////////////////////////
    /// @brief Class to handle mouse scroll events
    class MouseScrolledEvent: public Event
    {
        private:

            float xOffset, yOffset;

        public:

            //////////////////////////////////////
            /// @brief Default constructor
            /// @param xOffset The scroll X offset
            /// @param yOffset The scroll Y offset
            MouseScrolledEvent(float xOffset, float yOffset):
                    xOffset(xOffset), yOffset(yOffset) {}

            ///////////////////////////////////
            /// @brief Get the scroll X offset
            /// @return The scroll X offset
            inline float getXOffset() const { return xOffset; }

            ///////////////////////////////////
            /// @brief Get the scroll Y offset
            /// @return the scroll Y offset
            inline float getYOffset() const { return yOffset; }

            EVENT_CLASS_TYPE(MouseScrolled);

            std::string toString() const override
            {
                std::stringstream ss;
                ss << "MouseScrolledEvent: (" << xOffset << ", "
                   << yOffset << ")";
                return ss.str();
            }
    };

    ///////////////////////////////////////////
    /// @brief Interface to mouse button events
    class MouseButtonEvent: public Event
    {
        protected:

            int button;

            /////////////////////////////////////////////////////
            /// @brief Default constructor
            /// @param button The button that triggered the event
            MouseButtonEvent(int button): button(button) {}

        public:

            ////////////////////////////////////////////////////////
            /// @brief Get the mouse button that triggered the event
            inline int getMouseButton() const { return button; }
    };

    ////////////////////////////////////////////////////
    /// @brief Class to handle mouse button press events
    class MouseButtonPressedEvent: public MouseButtonEvent
    {
        public:

            //////////////////////////////////////////
            /// @brief Constructor
            /// @param button The pressed mouse button
            MouseButtonPressedEvent(int button):
                    MouseButtonEvent(button) {}

            EVENT_CLASS_TYPE(MouseButtonPressed);

            std::string toString() const override
            {
                std::stringstream ss;
                ss << "MouseButtonPressedEvent: " << button;
                return ss.str();
            }
    };

    //////////////////////////////////////////////////////
    /// @brief Class to handle mouse button release events
    class MouseButtonReleasedEvent: public MouseButtonEvent
    {
        public:

            ///////////////////////////////////////////
            /// @brief Constructor
            /// @param button The released mouse button
            MouseButtonReleasedEvent(int button):
                    MouseButtonEvent(button) {}

            EVENT_CLASS_TYPE(MouseButtonReleased);

            std::string toString() const override
            {
                std::stringstream ss;
                ss << "MouseButtonReleasedEvent: " << button;
                return ss.str();
            }
    };
}
