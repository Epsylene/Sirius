
#pragma once

#include "srspch.hpp"

#include "Sirius/Math/Vector/Vector.hpp"

namespace Sirius
{
    /////////////////////////////////////////////////////
    /// @brief Input class
    /// 
    /// This class handles all key and mouse inputs;
    /// however, it is not an event system class. Rather,
    /// it provides functions to retrieve information
    /// about the input event.
    class Input
    {
        public:

            static std::unique_ptr<Input> instance;

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

            ////////////////////////////////////////////////////////
            /// @brief Get the mouse position, in window coordinates
            static Vec2 getMousePos();

            ////////////////////////////////////////////////////////
            /// @brief Get the mouse position, in screen coordinates
            static Vec2 getMouseScreenPos();
    };
}
