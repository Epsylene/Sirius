
#pragma once

#include "Sirius/Math/Vector/Vector.hpp"

namespace Sirius
{
    ////////////////////////////////////////////////////////
    /// @brief Color class
    ///
    /// This class is actually the same as a Sirius::Vec4
    /// with r, g, b, a components instead of x, y, z and w.
    class Color
    {
        public:

            float r, g, b, a;

            Color() = default;

            ///////////////////////////////////////////////
            /// @brief Constructs an RGBA color
            ///
            /// The parameters are expected to range from
            /// 0 to 1, with the alpha set to 1 by default.
            Color(float r, float g, float b, float a = 1.f);

            Color(const Color& color) = default;
            Color(Color&& color) = default;

            ////////////////////////////////
            /// @brief Construct an RGB
            Color(const Vec4& color);

            Color& operator+=(const Color& color);
            Color& operator-=(const Color& color);
            Color& operator*=(const Color& color);

            operator Vec4() const;
    };

    Color operator+(const Color& c1, const Color& c2);
    Color operator-(const Color& c1, const Color& c2);
    Color operator*(const Color& c1, const Color& c2);
}
