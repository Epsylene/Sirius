
#pragma once

#include "srspch.h"

namespace Sirius
{
    enum class EventType
    {
            None = 0,
            //Window
            WindowClose,
            WindowResize,
            //Keyboard
            KeyPressed,
            KeyReleased,
            //Mouse
            MouseButtonPressed,
            MouseButtonReleased,
            MouseMoved,
            MouseScrolled
    };

#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::type; } \
                               virtual EventType getEventType() const override { return getStaticType(); } \
                               virtual const char* getEventName() const override { return #type; }

    class Event
    {
            friend class EventDispatcher;

        protected:

            bool handled = false;

        public:

            virtual EventType getEventType() const = 0;
            virtual const char* getEventName() const = 0;
            virtual std::string toString() const { return getEventName(); }
    };

    class EventDispatcher
    {
        private:

            Event& event;
            template<typename T> using EventFn = std::function<bool(T&)>;

        public:

            EventDispatcher(Event& event): event(event) {}

            template<typename T>
            bool dispatch(EventFn<T> func)
            {
                if(event.getEventType() == T::getStaticType())
                {
                    event.handled = func(*(T*)&event);
                    return true;
                }

                return false;
            }
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& event)
    {
        return os << event.toString();
    }
}
