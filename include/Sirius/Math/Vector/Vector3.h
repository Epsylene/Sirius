
#pragma once

namespace Sirius
{
    template<typename T>
    struct Vector3
    {
        T x, y, z;

        constexpr Vector3() = default;
        constexpr explicit Vector3(T scalar);
        constexpr Vector3(T x, T y, T z);
        constexpr Vector3(const Vector3& vec) = default;
        constexpr Vector3(Vector3&& vec) noexcept = default;

        constexpr Vector3<T>& operator=(const Vector3<T>& vec) = default;
        template<typename U> constexpr Vector3<T>& operator=(const Vector3<U>& vec);

        T operator[](unsigned index);
        const T operator[](unsigned index) const;

        constexpr Vector3<T>& operator+=(const Vector3<T>& vec);
        constexpr Vector3<T>& operator-=(const Vector3<T>& vec);
        constexpr Vector3<T>& operator*=(T scalar);
        constexpr Vector3<T>& operator/=(T scalar);

        bool operator==(const Vector3<T>& rhs) const;
        bool operator!=(const Vector3<T>& rhs) const;

        constexpr operator Vector<3, T>() const;
    };

    template<typename T> constexpr Vector3<T> operator+(const Vector3<T>& v1, const Vector3<T>& v3);
    template<typename T> constexpr Vector3<T> operator-(const Vector3<T>& v1, const Vector3<T>& v3);
    template<typename T> constexpr Vector3<T> operator*(const Vector3<T>& vec, T scalar);
    template<typename T> constexpr Vector3<T> operator/(const Vector3<T>& vec, T scalar);

    using Vector33i = Vector3<int>;
    using Vector33f = Vector3<float>;
    using Vector33d = Vector3<double>;
}

#include "Vector3.tpp"
