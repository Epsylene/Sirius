
#pragma once

#include "Event.h"

namespace Sirius
{
    class KeyEvent: public Event
    {
        protected:

            int keyCode;
            KeyEvent(int keyCode): keyCode(keyCode) {}
    };

    class KeyPressedEvent: public KeyEvent
    {
        private:

            int repeatCount;

        public:

            KeyPressedEvent(int keyCode, int repeatCount):
                KeyEvent(keyCode), repeatCount(repeatCount) {}

            inline int getRepeatCount() const { return repeatCount; }

            EVENT_CLASS_TYPE(KeyPressed);

            std::string toString() const override
            {
                std::stringstream ss;
                ss << "KeyPressedEvent: " << keyCode << " ("
                    << repeatCount << " repeats)";
                return ss.str();
            }
    };

    class KeyReleasedEvent: public KeyEvent
    {
        public:

            KeyReleasedEvent(int keycode): KeyEvent(keycode) {}

            EVENT_CLASS_TYPE(KeyReleased);

            std::string toString() const override
            {
                std::stringstream ss;
                ss << "KeyReleasedEvent : " << keyCode;
                return ss.str();
            }
    };
}
