
#pragma once

#include "Sirius/Renderer/Color.hpp"

namespace Sirius
{
    /////////////////////////
    /// @brief Material class
    struct Material
    {
        Color ambient, diffuse, specular;
        float shininess;

        ///////////////////////////////////////////////////////////
        /// @brief Create a flat-colored material
        ///
        /// @param diffuse The material's color
        /// @param shininess The material's reflectance; the greater
        ///     the shininess is, the sharper the light will be
        ///     reflected by the material.
        explicit Material(const Color& diffuse, float shininess = 32.f);

        ////////////////////////////////////////
        /// @brief Create a flat-colored material
        ///
        /// @param ambient The world's light color
        /// @param diffuse The material's color
        /// @param specular The specular highlight color
        /// @param shininess The material's reflectance; the greater
        ///     the shininess is, the sharper the light will be
        ///     reflected by the material.
        Material(const Color& ambient, const Color& diffuse,
                     const Color& specular, float shininess = 32.f);
    };
}
