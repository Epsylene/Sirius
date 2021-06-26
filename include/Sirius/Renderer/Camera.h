
#pragma once

#include "Sirius/Math/Math.h"

namespace Sirius
{
    /////////////////////////////////////////////////////////
    /// @brief Generic camera object class
    ///
    /// This class is not intended to be instanciated, but to
    /// be derived from and create actual camera objects with
    /// a defined view-projection matrix.
    class Camera
    {
        protected:

            Mat4 projMatrix;
            Mat4 viewMatrix;
            Mat4 viewProjMatrix;

            Vec3 pos, direction, up;
            float pitch = 0.f, yaw = -90.f, roll = 0.f;

            virtual void calculateViewProjMatrix() = 0;

        public:

            /////////////////////////////////////////////////
            /// @brief Constructs a generic camera object
            ///     at (0, 0, 1), pointing towards (0, 0, -1)
            ///     and with up vector (0, 1, 0)
            Camera();

            //////////////////////////////////////
            /// @brief Set the camera2D's position
            virtual void setPosition(const Vec3& pos);

            //////////////////////////////////////
            /// @brief Get the camera2D's position
            virtual const Vec3& getPosition() const;

            /////////////////////////////////////////////////////
            /// @brief Get the camera2D's normal direction vector
            virtual const Vec3& getDirection() const;

            ////////////////////////////////////////////////
            /// @brief Get the OpenGL view-projection matrix
            virtual const Mat4& getViewProjMatrix() const;
    };

    ///////////////////////////////////////////////////////////////
    /// @brief Orthographic 2D camera object class
    ///
    /// This camera is intended to be used only for 2D rendering
    /// purposes. As such, it always points in negative Z direction
    /// and can only translate or, if specified, rotate around this
    /// axis.
    class Camera2D: public Camera
    {
        protected:

            //////////////////////////////////////////////////////
            /// @brief Calculates the view-projection matrix of
            ///     the 2D camera
            ///
            /// The view matrix is a composed of a rotation matrix
            /// around `direction` and a `pos` translation matrix;
            /// the projection matrix is a `Sirius::ortho()` with the
            /// arguments from the constructor.
            ///
            /// @see Camera2D constructor, `Sirius::ortho()`
            virtual void calculateViewProjMatrix() override;

        public:

            /////////////////////////////////////////////////////////
            /// @brief Constructs an orthographic camera2D pointing
            ///     towards -Z with left and bottom planes distances
            ///     set to -1, right and top to 1, near and far to -1
            ///     and 1)
            Camera2D();

            //////////////////////////////////////////////////////////
            /// @brief Constructs an orthographic 2D camera2D pointing
            ///     towards -Z with the provided arguments
            ///
            /// @param left Left plane distance
            /// @param right Right plane distance
            /// @param bottom Bottom plane distance
            /// @param top Top plane distance
            Camera2D(float left, float right, float bottom, float top);

            ///////////////////////////////////////////////////////
            /// @brief Set the 2D camera2D's rotation
            ///
            /// @param rotation Rotation in the 2D plane the camera
            ///     is looking at
            void setRotation(float rotation);

            ////////////////////////////////////////////////////////////
            /// @brief Set the 2D camera2D's projection matrix arguments
            ///
            /// @param left Left plane distance
            /// @param right Right plane distance
            /// @param bottom Bottom plane distance
            /// @param top Top plane distance
            virtual void setProjection(float left, float right, float bottom, float top);
    };

    ////////////////////////////////////////////////////////////
    /// @brief 3D perspective camera object class
    ///
    /// This camera is intended for general 3D usage: it is a
    /// classical first-person camera, used to roam around the
    /// scene and watch the objects in it from different angles.
    class Camera3D: public Camera
    {
        protected:

            ////////////////////////////////////////////////////////////////////////////////
            /// @brief 	Calculates the view-projection matrix of the 3D camera.
            ///
            /// The view matrix is a `Sirius::lookAt()` with `pos` as eye, `pos + direction`
            /// as center and `up` as... up. The projection matrix is a `Sirius::perspective()`
            /// that takes the arguments from the constructor.
            ///
            /// @see Camera3D constructor, `Sirius::lookAt()`, `Sirius::perspective()`
            virtual void calculateViewProjMatrix() override;

        public:

            //////////////////////////////////////////////////////
            /// @brief Constructs a default perspective 3D camera
            ///     (90º FOV, 16/9 aspect ratio, distances to near
            ///     and far planes set to 0.1 and a 100).
            Camera3D();

            /////////////////////////////////////////////////////////////////////////
            /// @brief Constructs a perspective 3D camera with the given parameters
            ///
            /// @param fov Field of view, that is, the angle the camera2D "sees" of
            ///     the world; a FOV of 90º means that the righmost and leftmost
            ///     objects in the camera2D's visual field are at 45º right and left.
            /// @param aspect Aspect ratio of the camera2D's visual field
            /// @param near Near plane distance
            /// @param far Far plane distance
            Camera3D(float fov, float aspect, float near, float far);

            ////////////////////////////////////////////////////
            /// @brief Set the camera's rotation in Euler angles
            ///
            /// @param pitch Rotation around the right vector
            /// @param yaw Rotation around the up vector
            /// @param roll Rotation around the direction vector
            virtual void setRotation(float pitch, float yaw, float roll);

            /////////////////////////////////////////////////////////////////////////
            /// @brief Set the camera's projection matrix arguments
            ///
            /// @param fov Field of view, that is, the angle the camera2D "sees" of
            ///     the world; a FOV of 90º means that the righmost and leftmost
            ///     objects in the camera2D's visual field are at 45º right and left.
            /// @param aspect Aspect ratio of the camera2D's visual field
            /// @param near Near plane distance
            /// @param far Far plane distance
            virtual void setProjection(float fov, float aspect, float near, float far);
    };
}
