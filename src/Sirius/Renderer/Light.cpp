
#include "Sirius/Renderer/Light.h"

namespace Sirius
{
    Light::Light(const Vec3& pos): pos(pos), ambient(1.f, 1.f, 1.f),
        diffuse(1.f, 1.f, 1.f), specular(1.f, 1.f, 1.f)
    {}

    Light::Light(const Vec3& pos, const Color& diffuse): pos(pos),
        ambient(1.f, 1.f, 1.f), diffuse(diffuse), specular(1.f, 1.f, 1.f)
    {}

    Light::Light(const Vec3& pos, const Color& ambient, const Color& diffuse, const Color& specular):
        pos(pos), ambient(ambient), diffuse(diffuse), specular(specular)
    {}
}
