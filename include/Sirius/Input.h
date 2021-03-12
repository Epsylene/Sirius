
#pragma once

#include "srspch.h"

namespace Sirius
{
    ////////////////////////////////////////////////
    /// @brief Input class
    /// 
    /// This class handles all key and mouse inputs;
    /// however, it is not an event system class.
    class Input
    {
        public:

            static Input* instance;

            ///////////////////////////////
            /// @brief Is the key pressed ?
            static bool isKeyPressed(int keyCode);

            ////////////////////////////////////////
            /// @brief Is the mouse button pressed ?
            static bool isMouseButtonPressed(int button);

            ///////////////////////////////////
            /// @brief Get the mouse X position
            static float getMouseX();

            ///////////////////////////////////
            /// @brief Get the mouse Y position
            static float getMouseY();

            //////////////////////////////////////////////////
            /// @brief Get the mouse position
            ///
            /// Position is returned as an std::pair of floats
            static std::pair<float, float> getMousePos();
    };
}
