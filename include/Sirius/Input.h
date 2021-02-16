
#pragma once

#include "srspch.h"

namespace Sirius
{
    class Input
    {
        public:

            static Input* instance;

            virtual bool isKeyPressed(int keyCode) = 0;
            virtual bool isMouseButtonPressed(int button) = 0;
            virtual float getMouseX() = 0;
            virtual float getMouseY() = 0;
            virtual std::pair<float, float> getMousePos() = 0;
    };
}
