
#pragma once

namespace Sirius
{
    template<typename T>
    struct Vector2
    {
        T x, y;

        constexpr Vector2() = default;
        constexpr explicit Vector2(T scalar);
        constexpr Vector2(T x, T y);
        constexpr Vector2(const Vector2& vec) = default;
        constexpr Vector2(Vector2&& vec) noexcept = default;

        constexpr Vector2<T>& operator=(const Vector2<T>& vec) = default;
        template<typename U> constexpr Vector2<T>& operator=(const Vector2<U>& vec);

        constexpr T operator[](unsigned index);
        constexpr T operator[](unsigned index) const;

        constexpr Vector2<T>& operator+=(const Vector2<T>& vec);
        constexpr Vector2<T>& operator-=(const Vector2<T>& vec);
        constexpr Vector2<T>& operator*=(T scalar);
        constexpr Vector2<T>& operator/=(T scalar);

        bool operator==(const Vector2<T>& rhs) const;
        bool operator!=(const Vector2<T>& rhs) const;

        constexpr operator Vector<2, T>() const;
    };

    template<typename T> constexpr Vector2<T> operator+(const Vector2<T>& v1, const Vector2<T>& v2);
    template<typename T> constexpr Vector2<T> operator-(const Vector2<T>& v1, const Vector2<T>& v2);
    template<typename T> constexpr Vector2<T> operator*(const Vector2<T>& vec, T scalar);
    template<typename T> constexpr Vector2<T> operator/(const Vector2<T>& vec, T scalar);

    using Vector2i = Vector2<int>;
    using Vector2f = Vector2<float>;
    using Vector2d = Vector2<double>;
}

#include "Vector2.tpp"
