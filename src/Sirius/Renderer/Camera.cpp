
#include "Sirius/Renderer/Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace Sirius
{
    //--------------------------- CAMERA ---------------------------//

    Camera::Camera(): pos(0.f, 0.f, 1.f), direction(0.f, 0.f, -1.f), up(0.f, 1.f, 0.f)
    {}

    void Camera::setPosition(const glm::vec3& pos)
    {
        this->pos = pos;

        calculateViewProjMatrix();
    }

    const glm::vec3& Camera::getPosition() const
    {
        return pos;
    }

    const glm::vec3& Camera::getDirection() const
    {
        return direction;
    }

    const glm::mat4& Camera::getViewProjMatrix() const
    {
        return viewProjMatrix;
    }

    //-------------------------- 2D CAMERA --------------------------//

    Camera2D::Camera2D(): Camera2D(-1.f, 1.f, -1.f, 1.f)
    {}

    Camera2D::Camera2D(float left, float right, float bottom, float top)
    {
        this->direction = direction;

        projMatrix = glm::ortho(left, right, bottom, top);
        viewMatrix = glm::mat4(1.f);
        viewProjMatrix = projMatrix * viewMatrix;
    }

    void Camera2D::setRotation(float rotation)
    {
        roll = rotation;

        calculateViewProjMatrix();
    }

    void Camera2D::setProjection(float left, float right, float bottom, float top)
    {
        projMatrix = glm::ortho(left, right, bottom, top);

        calculateViewProjMatrix();
    }

    void Camera2D::calculateViewProjMatrix()
    {
        // Rotates a point by 'rotation' around an axis, then translates
        //  it by 'pos'.
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
                              * glm::rotate(glm::mat4(1.0f), roll, direction);

        // The world orientation is the inverse of the cameraController's.
        // Note that the resulting matrix is the same as a glm::lookAt()
        // with pos as eye vector, pos + direction as center, and up as
        // (you guessed it) up vector, with the latter being rotated by
        // roll.
        viewMatrix = glm::inverse(transform);
        viewProjMatrix = projMatrix * viewMatrix;
    }

    //-------------------------- 3D CAMERA --------------------------//

    Camera3D::Camera3D(): Camera3D(90.f, 16.f / 9.f, 0.1f, 100.f)
    {}

    Camera3D::Camera3D(float fov, float aspect, float near, float far)
    {
        projMatrix = glm::perspective(fov, aspect, near, far);

        viewProjMatrix = projMatrix * viewMatrix;
    }

    void Camera3D::setRotation(float pitch, float yaw, float roll)
    {
        this->pitch = pitch;
        this->yaw = yaw;
        this->roll = roll;

        calculateViewProjMatrix();
    }

    void Camera3D::setProjection(float fov, float aspect, float near, float far)
    {
        projMatrix = glm::perspective(fov, aspect, near, far);

        calculateViewProjMatrix();
    }

    void Camera3D::calculateViewProjMatrix()
    {
        // The camera2D's direction
        direction = { std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch)),
                      std::sin(glm::radians(pitch)),
                      std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch)) };
        direction = glm::normalize(direction);

        // The camera2D's up vector
        up = glm::rotate({0.f, 1.f, 0.f}, roll, direction);

        // The lookAt() function builds a view matrix that looks
        // from a position (pos) to a certain point (pos + direction)
        // in a space whose up-pointing vector is 'up'.
        viewMatrix = glm::lookAt(pos, pos + direction, up);
        viewProjMatrix = projMatrix * viewMatrix;
    }
}