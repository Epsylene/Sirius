
#include "Light.hpp"

namespace Sirius
{
    ///////////////////////////  LIGHT  ///////////////////////////

    Light::Light(): ambient(1.f, 1.f, 1.f), diffuse(1.f, 1.f, 1.f)
    {}

    Light::Light(const Color& diffuse): ambient(1.f, 1.f, 1.f),
        diffuse(diffuse)
    {}

    Light::Light(const Color& ambient, const Color& diffuse):
        ambient(ambient), diffuse(diffuse)
    {}

    /////////////////////////// POINT LIGHT  ///////////////////////////

    PointLight::PointLight(const Vec3& pos, float attDistance): pos(pos),
        attDistance(attDistance), Light()
    {}

    PointLight::PointLight(const Vec3& pos, const Light& light, float attDistance)
            : pos(pos), attDistance(attDistance), Light(light)
    {}

    ///////////////////////// DIRECTIONAL LIGHT  ///////////////////////////

    DirectionalLight::DirectionalLight(const Vec3& dir): dir(dir), Light()
    {}

    DirectionalLight::DirectionalLight(const Vec3& dir, const Light& light):
        dir(dir), Light(light)
    {}

    ///////////////////////// SPOTLIGHT  ///////////////////////////

    Spotlight::Spotlight(const Vec3& pos, const Vec3& dir, float attDistance, float cutoff,
                         float epsilon): pos(pos), dir(dir), cutoff(cutoff),
                         attDistance(attDistance), epsilon(epsilon), Light()
    {}

    Spotlight::Spotlight(const Vec3& pos, const Vec3& dir, const Light& light, float attDistance, float cutoff, float epsilon):
        pos(pos), dir(dir), cutoff(cutoff), attDistance(attDistance),
        epsilon(epsilon), Light(light)
    {}
}
