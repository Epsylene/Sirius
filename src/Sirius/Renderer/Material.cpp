
#include "Sirius/Renderer/Material.hpp"

namespace Sirius
{
    Material::Material(const Color& diffuse, float shininess):
        ambient(1.f, 1.f, 1.f), diffuse(diffuse),
        specular(1.f, 1.f, 1.f), shininess(shininess)
    {}

    Material::Material(const Color& ambient, const Color& diffuse,
                       const Color& specular, float shininess):
        ambient(ambient), diffuse(diffuse),
        specular(specular), shininess(shininess)
    {}
}