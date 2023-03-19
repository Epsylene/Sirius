
#include "vector_functions.hpp"

namespace Sirius
{
    Vec3 rotate(const Sirius::Vec3& vec, const Sirius::Vec3& axis, float angle)
    {
        return glm::rotate(vec, angle, axis);
    }

    Vec4 vec4(const Vec3& vec)
    {
        return Vec4{vec, 0.f};
    }
}