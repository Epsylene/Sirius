
#pragma once

#include "Color.hpp"
#include "Texture.hpp"

namespace Sirius
{
    /////////////////////////
    /// @brief Material class
    struct Material
    {
        Ref<Texture2D> diffuseMap, specularMap;
        float shininess;

        ///////////////////////////////////////////////////////////
        /// @brief Create a flat-colored material
        ///
        /// @param diffuseMap The material's color
        /// @param shininess The material's reflectance; the greater
        ///     the shininess is, the sharper the light will be
        ///     reflected by the material.
        explicit Material(const Ref<Texture2D>& diffuseMap, float shininess = 32.f);

        ////////////////////////////////////////////////////////////
        /// @brief Create a flat-colored material
        ///
        /// @param ambient The world's light color
        /// @param diffuseMap The material's color
        /// @param specularMap The reflected light color
        /// @param shininess The material's reflectance; the greater
        ///     the shininess is, the sharper the light will be
        ///     reflected by the material.
        Material(const Ref<Texture2D>& diffuseMap, const Ref<Texture2D>& specularMap,
                 float shininess = 32.f);
    };
}
