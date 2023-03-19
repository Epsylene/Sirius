
#include "CameraController.hpp"

#include "Core/Input/Input.hpp"
#include "Core/Input/KeyCodes.h"

namespace Sirius
{
    // ---------------------- CAMERA CONTROLLER ---------------------- //

    void CameraController::onEvent(Event& event)
    {
        EventDispatcher eventDispatcher(event);

        eventDispatcher.dispatch<MouseScrolledEvent>([this](MouseScrolledEvent& event) { return onMouseScrolled(event); });
        eventDispatcher.dispatch<WindowResizeEvent>([this](WindowResizeEvent& event) { return onWindowResized(event); });
    }

    void CameraController::setAspect(float aspect)
    {
        this->aspect = aspect;
    }

    // --------------------- CAMERA CONTROLLER 2D --------------------- //

    CameraController2D::CameraController2D(): CameraController2D(16.f/9.f, false)
    {}

    CameraController2D::CameraController2D(float aspect, bool enableRotation)
    {
        this->aspect = aspect;
        this->enableRotation = enableRotation;
        camera = std::make_shared<Camera2D>(-aspect * zoom, aspect * zoom, -zoom, zoom);
    }

    CameraController2D::CameraController2D(float left, float right, float bottom, float top)
    {
        enableRotation = true;
        aspect = (top - bottom) / (left - right);
        camera = std::make_shared<Camera2D>(left, right, bottom, top);
    }

    bool CameraController2D::onMouseScrolled(MouseScrolledEvent& event)
    {
        auto zoom = 1.f/this->zoom;
        zoom -= event.getYOffset() * 0.1f;
        zoom = std::max(zoom, 0.1f);
        this->zoom = 1.f/zoom;
        camera->setProjection(-aspect * zoom, aspect * zoom, -zoom, zoom);

        return false;
    }

    bool CameraController2D::onWindowResized(WindowResizeEvent& event)
    {
        aspect = (float)event.getWidth() / (float)event.getHeight();
        camera->setProjection(-aspect * zoom, aspect * zoom, -zoom, zoom);

        return false;
    }

    void CameraController2D::onUpdate(Timestep dt)
    {
        if(Input::isKeyPressed(SRS_KEY_W))
        {
            pos.x += std::sin(rotation) * movSpeed * dt;
            pos.y += std::cos(rotation) * movSpeed * dt;
        }
        if(Input::isKeyPressed(SRS_KEY_A))
        {
            pos.x -= std::cos(rotation) * movSpeed * dt;
            pos.y += std::sin(rotation) * movSpeed * dt;
        }
        if(Input::isKeyPressed(SRS_KEY_S))
        {
            pos.x -= std::sin(rotation) * movSpeed * dt;
            pos.y -= std::cos(rotation) * movSpeed * dt;
        }
        if(Input::isKeyPressed(SRS_KEY_D))
        {
            pos.x += std::cos(rotation) * movSpeed * dt;
            pos.y -= std::sin(rotation) * movSpeed * dt;
        }

        if(enableRotation)
        {
            if(Input::isKeyPressed(SRS_KEY_Q))
                rotation += rotSpeed * dt;
            if(Input::isKeyPressed(SRS_KEY_E))
                rotation -= rotSpeed * dt;

            if(Input::isKeyPressed(SRS_KEY_X))
                rotation = 0.f;

            camera->setRotation(rotation);
        }

        camera->setPosition(pos);
        auto zoom = 1.f/this->zoom;
        camera->setProjection(-aspect * zoom, aspect * zoom, -zoom, zoom);
        movSpeed = 3.f * zoom;
    }

    Camera2D& CameraController2D::getCamera()
    {
        return *camera;
    }

    // --------------------- CAMERA CONTROLLER 3D --------------------- //

    CameraController3D::CameraController3D(): CameraController3D(90.f, 16.f/9.f)
    {}

    CameraController3D::CameraController3D(const Vec3& pos): CameraController3D()
    {
        this->pos = pos;
    }

    CameraController3D::CameraController3D(float fov, float aspect):
        fov(fov)
    {
        this->aspect = aspect;
        lastMousePos = Input::getMousePos();

        camera = std::make_shared<Camera3D>(zoom * fov, aspect, 0.1f, 100.f);
    }

    bool CameraController3D::onMouseScrolled(MouseScrolledEvent& event)
    {
        zoom -= event.getYOffset() * 0.1f;
        zoom = std::clamp(zoom, 0.1f, 2.f);
        camera->setProjection(zoom * fov, aspect, 0.1f, 100.f);

        return false;
    }

    bool CameraController3D::onWindowResized(WindowResizeEvent& event)
    {
        aspect = (float)event.getWidth() / (float)event.getHeight();
        camera->setProjection(zoom * fov, aspect, 0.1f, 100.f);

        return false;
    }

    void CameraController3D::onUpdate(Timestep dt)
    {
        Vec3 dir = camera->getDirection();
        Vec3 up {0, 1, 0};

        // Move around
        if(Input::isKeyPressed(SRS_KEY_W))
            pos += dir * movSpeed * float(dt);
        if(Input::isKeyPressed(SRS_KEY_A))
            pos -= normalize(cross(dir, up)) * movSpeed * float(dt);
        if(Input::isKeyPressed(SRS_KEY_S))
            pos -= dir * movSpeed * float(dt);
        if(Input::isKeyPressed(SRS_KEY_D))
            pos += normalize(cross(dir, up)) * movSpeed * float(dt);

        // Move up and down
        if(Input::isKeyPressed(SRS_KEY_R))
            pos.y += movSpeed * dt;
        if(Input::isKeyPressed(SRS_KEY_F))
            pos.y -= movSpeed * dt;

        // Roll left and right
        if(Input::isKeyPressed(SRS_KEY_Q))
            roll -= rollSpeed * dt;
        if(Input::isKeyPressed(SRS_KEY_E))
            roll += rollSpeed * dt;

        // Reset the rolling rotation
        if(Input::isKeyPressed(SRS_KEY_X))
            roll = 0.f;

        // Look around with the mouse
        if(!Input::isKeyPressed(SRS_KEY_LEFT_SHIFT))
        {
            float xOffset = Input::getMouseX() - lastMousePos.x;
            float yOffset = lastMousePos.y - Input::getMouseY();

            pitch += yOffset * sensitivity * dt;
            yaw += xOffset * sensitivity * dt;

            pitch = std::clamp(pitch, -89.f, 89.f);

            camera->setRotation(pitch, yaw, roll);
        }

        lastMousePos = Input::getMousePos();

        camera->setPosition(pos);
        camera->setProjection(zoom * fov, aspect, 0.1f, 100.f);
    }

    Camera3D& CameraController3D::getCamera()
    {
        return *camera;
    }
}