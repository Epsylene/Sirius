
#pragma once

namespace Sirius
{
    template<typename T> requires std::is_scalar_v<T>
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

        constexpr Vector3<T> operator-();

        bool operator==(const Vector3<T>& rhs) const;
        bool operator!=(const Vector3<T>& rhs) const;

        constexpr operator Vector<3, T>() const;
    };

    template<typename T> constexpr Vector3<T> operator+(const Vector3<T>& v1, const Vector3<T>& v2);
    template<typename T> constexpr Vector3<T> operator-(const Vector3<T>& v1, const Vector3<T>& v2);
    template<typename T> constexpr Vector3<T> operator*(const Vector3<T>& vec, T scalar);
    template<typename T> constexpr Vector3<T> operator*(const Vector3<T>& v1, const Vector3<T>& v2);
    template<typename T> constexpr Vector3<T> operator/(const Vector3<T>& vec, T scalar);

    using Vector3i = Vector3<int>;
    using Vector3f = Vector3<float>;
    using Vector3d = Vector3<double>;

    using Vec3 = Vector3f;
}

#include "Vector3.tpp"
