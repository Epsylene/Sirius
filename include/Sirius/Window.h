
#pragma once

#include "srspch.h"
#include "Sirius/Events/Event.h"

namespace Sirius
{
    struct WindowProps
    {
        std::string title;
        unsigned int width, height;

        WindowProps(const std::string& title = "Sirius Engine", unsigned int width = 1024, unsigned int height = 576):
            title(title), width(width), height(height) {}
    };

    class Window
    {
        public:

            virtual void onUpdate() = 0;

            virtual unsigned int getWidth() const = 0;
            virtual unsigned int getHeight() const = 0;

            using EventCallbackFn = std::function<void(Event&)>;
            virtual void setEventCallback(const EventCallbackFn& callback) = 0;

            virtual void setVSync(bool enabled) = 0;
            virtual bool vSync() const = 0;

            static Window* create(const WindowProps& props = WindowProps());
    };
}