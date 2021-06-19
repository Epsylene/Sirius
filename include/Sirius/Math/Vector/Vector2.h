
#pragma once

namespace Sirius
{
    ////////////////////////////////////////
    /// @brief Sirius vector class
    ///
    /// @tparam dim The vector dimension
    /// @tparam T The vector elements types
    template<unsigned dim, typename T> struct Vector;

    template<typename T>
    struct Vector<2, T>
    {
            T x, y;

            constexpr Vector() = default;
            constexpr explicit Vector(T scalar);
            constexpr Vector(T x, T y);
            constexpr Vector(const Vector& vec) = default;
            constexpr Vector(Vector&& vec) noexcept = default;

            constexpr Vector<2, T>& operator=(const Vector<2, T>& vec) = default;
            template<typename U> constexpr Vector<2, T>& operator=(const Vector<2, U>& vec);

            T operator[](unsigned index);
            const T operator[](unsigned index) const;

            constexpr Vector<2, T>& operator+=(const Vector<2, T>& vec);
            constexpr Vector<2, T>& operator-=(const Vector<2, T>& vec);
            constexpr Vector<2, T>& operator*=(T scalar);
            constexpr Vector<2, T>& operator/=(T scalar);
    };

    template<typename T> constexpr Vector<2, T> operator+(const Vector<2, T>& v1, const Vector<2, T>& v2);
    template<typename T> constexpr Vector<2, T> operator-(const Vector<2, T>& v1, const Vector<2, T>& v2);
    template<typename T> constexpr Vector<2, T> operator*(const Vector<2, T>& vec, T scalar);
    template<typename T> constexpr Vector<2, T> operator/(const Vector<2, T>& vec, T scalar);

    using Vector2i = Vector<2, int>;
    using Vector2f = Vector<2, float>;
    using Vector2d = Vector<2, double>;
}

#include "Vector2.tpp"
