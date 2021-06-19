
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
    struct Vector<3, T>
    {
        T x, y, z;

        constexpr Vector() = default;
        constexpr explicit Vector(T scalar);
        constexpr Vector(T x, T y, T z);
        constexpr Vector(const Vector& vec) = default;
        constexpr Vector(Vector&& vec) noexcept = default;

        constexpr Vector<3, T>& operator=(const Vector<3, T>& vec) = default;
        template<typename U> constexpr Vector<3, T>& operator=(const Vector<3, U>& vec);

        T operator[](unsigned index);
        const T operator[](unsigned index) const;

        constexpr Vector<3, T>& operator+=(const Vector<3, T>& vec);
        constexpr Vector<3, T>& operator-=(const Vector<3, T>& vec);
        constexpr Vector<3, T>& operator*=(T scalar);
        constexpr Vector<3, T>& operator/=(T scalar);
    };

    template<typename T> constexpr Vector<3, T> operator+(const Vector<3, T>& v1, const Vector<3, T>& v3);
    template<typename T> constexpr Vector<3, T> operator-(const Vector<3, T>& v1, const Vector<3, T>& v3);
    template<typename T> constexpr Vector<3, T> operator*(const Vector<3, T>& vec, T scalar);
    template<typename T> constexpr Vector<3, T> operator/(const Vector<3, T>& vec, T scalar);

    using Vector3i = Vector<3, int>;
    using Vector3f = Vector<3, float>;
    using Vector3d = Vector<3, double>;
}
