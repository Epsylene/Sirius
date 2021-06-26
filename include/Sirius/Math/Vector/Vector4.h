
#pragma once

namespace Sirius
{
    template<typename T> requires std::is_scalar_v<T>
    struct Vector4
    {
        T x, y, z, w;

        constexpr Vector4() = default;
        constexpr explicit Vector4(T scalar);
        constexpr Vector4(T x, T y, T z, T w);
        constexpr Vector4(const Vector4& vec) = default;
        constexpr Vector4(Vector4&& vec) noexcept = default;

        constexpr Vector4<T>& operator=(const Vector4<T>& vec) = default;
        template<typename U> constexpr Vector4<T>& operator=(const Vector4<U>& vec);

        T operator[](unsigned index);
        const T operator[](unsigned index) const;

        constexpr Vector4<T>& operator+=(const Vector4<T>& vec);
        constexpr Vector4<T>& operator-=(const Vector4<T>& vec);
        constexpr Vector4<T>& operator*=(T scalar);
        constexpr Vector4<T>& operator/=(T scalar);

        constexpr Vector4<T> operator-();

        bool operator==(const Vector4<T>& rhs) const;
        bool operator!=(const Vector4<T>& rhs) const;

        constexpr operator Vector<4, T>() const;
    };

    template<typename T> constexpr Vector4<T> operator+(const Vector4<T>& v1, const Vector4<T>& v2);
    template<typename T> constexpr Vector4<T> operator-(const Vector4<T>& v1, const Vector4<T>& v2);
    template<typename T> constexpr Vector4<T> operator*(const Vector4<T>& vec, T scalar);
    template<typename T> constexpr Vector4<T> operator*(const Vector4<T>& v1, const Vector4<T>& v2);
    template<typename T> constexpr Vector4<T> operator*(const Vector<4, T>& v1, const Vector4<T>& v2);
    template<typename T> constexpr Vector4<T> operator/(const Vector4<T>& vec, T scalar);

    using Vector4i = Vector4<int>;
    using Vector4f = Vector4<float>;
    using Vector4d = Vector4<double>;

    using Vec4 = Vector4f;
}

#include "Vector4.tpp"
