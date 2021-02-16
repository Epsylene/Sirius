
#pragma once

#include "GLFW/glfw3.h"

#include "srspch.h"
#include "Sirius/Input.h"
#include "Sirius/Simulation.h"

namespace Sirius
{
    class WindowsInput: public Input
    {
        public:

            virtual bool isKeyPressed(int keyCode) override;
            virtual bool isMouseButtonPressed(int button) override;
            virtual float getMouseX() override;
            virtual float getMouseY() override;
            virtual std::pair<float, float> getMousePos() override;
    };
}
