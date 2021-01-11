
#pragma once

#include "Event.h"

namespace Sirius
{
    class WindowResizeEvent: public Event
    {
        private:

            unsigned int width, height;

        public:

            WindowResizeEvent(unsigned int width, unsigned int height):
                width(width), height(height) {}

            inline unsigned int getWidth() const { return width; }
            inline unsigned int getHeigth() const { return height; }

            EVENT_CLASS_TYPE(WindowResize);

            std::string toString() const override
            {
                std::stringstream ss;
                ss << "WindowResizeEvent: " << width << ", " << height;
                return ss.str();
            }
    };

    class WindowCloseEvent: public Event
    {
        public:

            WindowCloseEvent() {}

            EVENT_CLASS_TYPE(WindowClose);
    };
}
