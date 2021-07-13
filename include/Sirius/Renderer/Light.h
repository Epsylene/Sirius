
#pragma once

#include "Sirius/Math/Vector/Vector.hpp"
#include "Color.hpp"

namespace Sirius
{
    struct Light
    {
        Vec3 pos;
        Color ambient, diffuse, specular;

        explicit Light(const Vec3& pos);

        Light(const Vec3& pos, const Color& diffuse);

        Light(const Vec3& pos, const Color& ambient, const Color& diffuse, const Color& specular);
    };
}
