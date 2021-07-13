
#include "Sirius/Renderer/Material.hpp"

namespace Sirius
{
    Material::Material(const Ref<Texture2D>& diffuseMap, float shininess):
            diffuseMap(diffuseMap), specularMap(diffuseMap), shininess(shininess)
    {}

    Material::Material(const Ref<Texture2D>& diffuseMap, const Ref<Texture2D>& specularMap,
                       float shininess):
            diffuseMap(diffuseMap), specularMap(specularMap), shininess(shininess)
    {}
}