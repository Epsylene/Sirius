
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
    struct Vector<4, T>
    {
        T x, y, z, w;

        constexpr Vector() = default;
        constexpr explicit Vector(T scalar);
        constexpr Vector(T x, T y, T z, T w);
        constexpr Vector(const Vector& vec) = default;
        constexpr Vector(Vector&& vec) noexcept = default;

        constexpr Vector<4, T>& operator=(const Vector<4, T>& vec) = default;
        template<typename U> constexpr Vector<4, T>& operator=(const Vector<4, U>& vec);

        T operator[](unsigned index);
        const T operator[](unsigned index) const;

        constexpr Vector<4, T>& operator+=(const Vector<4, T>& vec);
        constexpr Vector<4, T>& operator-=(const Vector<4, T>& vec);
        constexpr Vector<4, T>& operator*=(T scalar);
        constexpr Vector<4, T>& operator/=(T scalar);
    };

    template<typename T> constexpr Vector<4, T> operator+(const Vector<4, T>& v1, const Vector<4, T>& v4);
    template<typename T> constexpr Vector<4, T> operator-(const Vector<4, T>& v1, const Vector<4, T>& v4);
    template<typename T> constexpr Vector<4, T> operator*(const Vector<4, T>& vec, T scalar);
    template<typename T> constexpr Vector<4, T> operator/(const Vector<4, T>& vec, T scalar);

    using Vector4i = Vector<4, int>;
    using Vector4f = Vector<4, float>;
    using Vector4d = Vector<4, double>;
}

#include "Vector4.tpp"
