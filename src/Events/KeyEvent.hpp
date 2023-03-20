
#pragma once

#include "Event.hpp"

namespace Sirius
{
    /// @brief Interface to all key events
    class KeyEvent: public Event
    {
        protected:

            int keyCode;

            /// @brief Default constructor
            /// @param keyCode The keyboard key code
            KeyEvent(int keyCode): keyCode(keyCode) {}
    };

    /// @brief Event class to handle a key press
    class KeyPressedEvent: public KeyEvent
    {
        private:

            int repeatCount;

        public:

            /// @brief Default constructor
            /// @param keyCode The keyboard key code
            /// @param repeatCount When pressing during a long time
            KeyPressedEvent(int keyCode, int repeatCount):
                KeyEvent(keyCode), repeatCount(repeatCount) {}

            /// @brief Get the key repeat counter
            /// @return The repeat counter
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

    /// @brief Event class to handle a key release
    class KeyReleasedEvent: public KeyEvent
    {
        public:

            /// @brief Default constructor
            /// @param keycode The keyboard key code
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
