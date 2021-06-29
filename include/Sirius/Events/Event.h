
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

///////////////////////////////////////////////////////////////
/// @brief Macro that defines three functions to be defined in
///     each Event subclass:
///     - getStaticType() (the static type itself; for type comparison)
///     - getEventType() (an Event object's type; for type comparison)
///     - getEventName() (the object's event name, which is the name of the type)
#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::type; } \
                               virtual EventType getEventType() const override { return getStaticType(); } \
                               virtual const char* getEventName() const override { return #type; }

    //////////////////////////////////////////////////////////
    /// @brief Event parent class
    ///
    /// Each event class stems from this abstract class, which
    /// defines functions to retrieve the name and the type of
    /// the event.
    class Event
    {
            friend class EventDispatcher;

        public:

            bool handled = false;

            /////////////////////////////////////
            /// @brief Get an object's event type
            virtual EventType getEventType() const = 0;

            /////////////////////////////
            /// @brief Get the event name
            virtual const char* getEventName() const = 0;

            ////////////////////////////////////////////////////////
            /// @brief Get the event name
            /// @details The difference between getEventName() and
            ///     toString() is that getEventName() always returns
            ///     the event name (which is the event type) and
            ///     nothing else; toString() returns the event name
            ///     by default but can be redefined to print more
            ///     information about the event.
            /// @return A string of the event name
            virtual std::string toString() const { return getEventName(); }
    };

    /////////////////////////////////////////////////////////
    /// @brief Event dispatcher class
    ///
    /// Takes in events and provides a dispatch() function to
    /// do trigger a function when a certain event type is
    /// encountered.
    ///
    /// @see dispatch()
    class EventDispatcher
    {
        private:

            Event& event;
            template<typename T> using EventFn = std::function<bool(T&)>;

        public:

            ///////////////////////////////////////////////////////////////
            /// @brief Default constructor
            ///
            /// The constructor will take in a reference to an event
            ///  object, so functions like dispatch are able to use it.
            ///  For app, an EventDispatcher object could be created
            ///  in an onEvent(Event& event) function taking in the
            ///  incoming events. The EventDispatcher object would take
            ///  the event parameter of the function in its constructor,
            ///  and then call dispatch with a WindowCloseEvent template
            ///  argument. Thus, when a WindowCloseEvent is triggered,
            ///  the dispatch() function will run the function provided
            ///  as a parameter.
            ///
            /// @param event The event object reference
            /// @see dispatch()
            EventDispatcher(Event& event): event(event) {}

            ///////////////////////////////////////////////////////////////
            /// @brief Dispatcher function for the events
            /// @details This function takes in an event function
            ///     (a bool returning a reference to the template
            ///     event type) and runs it if the event member
            ///     is of the same type as the template argument.
            ///     The event member is provided in the constructor.
            /// @tparam T The event type
            /// @param func The EventFn (bool taking in an event of type T)
            /// @return True if the event is of the same type,
            ///     false if not.
            /// @see EventDispatcher constructor
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
