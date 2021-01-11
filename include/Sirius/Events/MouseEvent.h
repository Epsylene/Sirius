
#pragma once

#include "Event.h"

namespace Sirius
{
    class MouseMovedEvent: public Event
    {
        private:

            float mouseX, mouseY;

        public:

            MouseMovedEvent(float x, float y): mouseX(x), mouseY(y) {}

            inline float getX() const { return mouseX; }
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

    class MouseScrolledEvent: public Event
    {
        private:

            float xOffset, yOffset;

        public:

            MouseScrolledEvent(float xOffset, float yOffset):
                    xOffset(xOffset), yOffset(yOffset) {}

            inline float getOffsetX() const { return xOffset; }
            inline float getOffsetY() const { return yOffset; }

            EVENT_CLASS_TYPE(MouseScrolled);

            std::string toString() const override
            {
                std::stringstream ss;
                ss << "MouseScrolledEvent: (" << xOffset << ", "
                   << yOffset << ")";
                return ss.str();
            }
    };

    class MouseButtonEvent: public Event
    {
        protected:

            int button;

            MouseButtonEvent(int button): button(button) {}

        public:

            inline int getMouseButton() const { return button; }
    };

    class MouseButtonPressedEvent: public MouseButtonEvent
    {
        public:

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

    class MouseButtonReleasedEvent: public MouseButtonEvent
    {
        public:

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
