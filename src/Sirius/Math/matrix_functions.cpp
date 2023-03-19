
#include "matrix_functions.hpp"

namespace Sirius
{
    Mat4 translate(const Vec3& offset)
    {
        return glm::translate(Mat4{}, offset);
    }

    Mat4 rotate(const Vec3& axis, float angle)
    {
        return glm::rotate(Mat4{}, angle, axis);
    }

    Mat4 ortho(float left, float right, float bottom, float top, float near, float far)
    {
        return glm::ortho(left, right, bottom, top, near, far);
    }

    Mat4 perspective(float fov, float aspect, float near, float far)
    {
        return glm::perspective(fov, aspect, near, far);
    }

    Mat4 scale(float factor)
    {
        return glm::scale(Mat4{}, Vec3{factor});
    }

    Mat4 scale(const Vec3& factor)
    {
        return glm::scale(factor);
    }
}