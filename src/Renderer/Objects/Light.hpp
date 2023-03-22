
#pragma once

#include "Math/Math.hpp"
#include "Renderer/Utils/Color.hpp"

namespace Sirius
{
    /// @brief Generic light class
    ///
    /// @details The light object defined by this class
    /// only has color properties.
    struct Light
    {
        Color ambient, diffuse;

        /// @brief Create a generic white light
        Light();

        /// @brief Create a generic light of `diffuse` color
        ///     and white ambient and specular components
        ///
        /// @details The diffuse color is the light's color, ambient is
        /// the world's color, and specular the light's color upon
        /// reflection.
        explicit Light(const Color& diffuse);

        /// @brief Create a generic light of given components
        ///
        /// @details The diffuse color is the light's color, ambient is
        /// the world's color, and specular the light's color upon
        /// reflection.
        Light(const Color& ambient, const Color& diffuse);
    };

    /// @brief Point light class
    ///
    /// @details This defines bulb-like object light, that has a color, a
    /// position, and an attenuation distance.
    struct PointLight: public Light
    {
        Vec3 pos;
        float attDistance;

        /// @brief Create a white point light at `pos`, which
        /// grows dimmer up to `attDistance`
        PointLight(const Vec3& pos, float attDistance);

        /// @brief Create a point light with user-defined
        /// components at `pos`, which grows dimmer up to
        /// `attDistance`
        PointLight(const Vec3& pos, const Light& light, float attDistance);
    };

    /// @brief Directional light class
    ///
    /// @details This defines a sun-like light, pointing towards
    /// the objects with a certain angle defined by a direction.
    struct DirectionalLight: public Light
    {
        Vec3 dir;

        /// @brief Create a white sun light pointing towards
        /// `dir`
        explicit DirectionalLight(const Vec3& dir);

        /// @brief Create a sun light with user-defined
        /// components pointing towards `dir`
        DirectionalLight(const Vec3& dir, const Light& light);
    };

    /// @brief Spotlight class
    ///
    /// @details The name speaks for itself, hopefully. The
    /// spotlight is defined by a position, a direction, an
    /// attenuation distance, the inner light cone cutoff angle,
    /// and an epsilon angle, which corresponds to the angle
    /// difference between the inner and the outer light cones
    /// cutoff angles.
    struct Spotlight: public Light
    {
        Vec3 pos, dir;
        float attDistance, cutoff, epsilon;

        /// @brief Create a white spotlight
        ///
        /// @param pos The spotlight's position
        /// @param dir The direction it is pointing at
        /// @param attDistance Its attenuation distance
        /// @param cutoff The inner light cone cutoff angle
        /// @param epsilon The difference between the inner
        ///     and outer light cones angles
        Spotlight(const Vec3& pos, const Vec3& dir, float attDistance, float cutoff, float epsilon = 0.1f);

        /// @brief Create a white spotlight
        ///
        /// @param pos The spotlight's position
        /// @param dir The direction it is pointing at
        /// @param light Its light's components
        /// @param attDistance Its attenuation distance
        /// @param cutoff The inner light cone cutoff angle
        /// @param epsilon The difference between the inner
        ///     and outer light cones angles
        Spotlight(const Vec3& pos, const Vec3& dir, const Light& light, float attDistance, float cutoff, float epsilon = 0.1f);
    };
}
