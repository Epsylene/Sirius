
#pragma once

#include "srspch.hpp"
#include "Math.hpp"

namespace Sirius
{
    template<std::size_t N>
    glm::mat<N, N, float> identity()
    {
        return glm::mat<N, N, float>{1.f};
    }

    Mat4 translate(const Vec3& offset);
    Mat4 rotate(const Vec3& axis, float angle);
    Mat4 scale(float factor);
    Mat4 scale(const Vec3& factor);

    Mat4 ortho(float left, float right, float bottom, float top, float near = -1.f, float far = 1.f);
    Mat4 perspective(float fov, float aspect, float near, float far);
}