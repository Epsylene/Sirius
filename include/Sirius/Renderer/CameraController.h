
#pragma once

#include "Camera.h"

#include "Sirius/Events/MouseEvent.h"
#include "Sirius/Events/ApplicationEvent.h"

#include "Sirius/Core/Timestep.h"

namespace Sirius
{
    ////////////////////////////////////////////////////////////////////
    /// @brief Generic camera object controller
    ///
    /// This is a generic controller, that is not intended to be
    /// instanciated, but to be derived from. The controller provides
    /// functions to update a camera and set callbacks to events; as
    /// such, each Camera class shall have a CameraController class
    /// that will be the object actually used in the application's code.
    class CameraController
    {
        protected:

            std::shared_ptr<Camera> camera;

            glm::vec3 pos = {0.f, 0.f, 1.f};
            float movSpeed = 5.f;

            float aspect;
            float zoom = 1.f;

            virtual bool onMouseScrolled(MouseScrolledEvent& event) = 0;
            virtual bool onWindowResized(WindowResizeEvent& event) = 0;

        public:

            virtual void onUpdate(Timestep dt) = 0;

            ////////////////////////////////////////////////////
            /// @brief Generic event callback function
            ///
            /// The events that are dispatched are mouse scrolls
            /// and windows resizes.
            virtual void onEvent(Event& event);

            //////////////////////////////////////
            /// @brief Get the controller's camera
            virtual Camera& getCamera();
    };

    ///////////////////////////////////////////////////
    /// @brief Orthographic 2D camera controller
    ///
    /// The controller allows control over the rotation
    /// (enabling/disabling, speed) and translation.
    class CameraController2D: public CameraController
    {
        private:

            bool enableRotation;
            float rotation = 0.f, rotSpeed = 5.f;

            ////////////////////////////////////////////////
            /// @brief Mouse scroll event callback
            ///
            /// The zoom factor is inversely proportional to
            /// the scrolling offset.
            virtual bool onMouseScrolled(MouseScrolledEvent& event) override;

            /////////////////////////////////
            /// @brief Window resize callback
            virtual bool onWindowResized(WindowResizeEvent& event) override;

        public:

            ////////////////////////////////////////////////////
            /// @brief Constructs a default 2D camera controller
            ///
            /// This controller's camera is a default 2D camera
            /// with 16/9 aspect ratio and which cannot be rotated.
            CameraController2D();

            ////////////////////////////////////////////
            /// @brief Constructs a 2D camera controller
            ///
            /// @param aspect Aspect ratio of the camera
            /// @param enableRotation Can the camera be rotated ?
            CameraController2D(float aspect, bool enableRotation);

            /////////////////////////////////////////////////////
            /// @brief Updates the controller
            ///
            /// The inputs (WASD to move, Q and E to rotate left
            /// and right, X to reset the rotation) are set here.
            virtual void onUpdate(Timestep dt) override;
    };

    //////////////////////////////////////////////////////
    /// @brief 3D perspective camera controller
    ///
    /// The controller allows control over the rotation
    /// (enabling/disabling, speed) and movement in space.
    class CameraController3D: public CameraController
    {
        private:

            glm::vec2 lastMousePos;

            float fov, sensitivity = 20.f, rollSpeed = 5.f;
            float pitch = 0.f, yaw = -90.f, roll = 0.f;

            ////////////////////////////////////////////////
            /// @brief Mouse scroll event callback
            ///
            /// The zoom factor is inversely proportional to
            /// the scrolling offset.
            virtual bool onMouseScrolled(MouseScrolledEvent& event) override;

            /////////////////////////////////
            /// @brief Window resize callback
            virtual bool onWindowResized(WindowResizeEvent& event) override;

        public:

            ////////////////////////////////////////////////////
            /// @brief Constructs a default 3D camera controller
            ///
            /// This controller's camera is a default 3D camera
            /// with 16/9 aspect ratio.
            CameraController3D();

            /// @brief Construct a 3D camera controller
            ///
            /// @param fov Field of view, that is, the angle the camera2D "sees" of
            ///     the world; a FOV of 90º means that the righmost and leftmost
            ///     objects in the camera2D's visual field are at 45º right and left.
            /// @param aspect Aspect ratio of the camera2D's visual field
            CameraController3D(float fov, float aspect);

            //////////////////////////////////////////////////////////
            /// @brief Updates the controller
            ///
            /// The inputs (WASD to move, R and F to move up and down,
            /// mouse cursor to look around, Q and E to roll left and
            /// right, X to reset the rolling rotation) are set here.
            virtual void onUpdate(Timestep dt) override;
    };
}
