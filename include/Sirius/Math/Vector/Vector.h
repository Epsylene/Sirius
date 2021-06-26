
#pragma once

namespace Sirius
{
    template<unsigned dim, typename T>
    requires std::is_scalar_v<T>
    class Vector
    {
        private:

            std::array<T, dim> vals {};

        public:

            constexpr Vector() = default;
            constexpr explicit Vector(T scalar);

            template<typename... Ts> requires std::is_scalar_v<T>
            explicit constexpr Vector(Ts... xs);

            constexpr Vector(const Vector& vec) = default;
            constexpr Vector(Vector&& vec) noexcept = default;

            constexpr Vector<dim, T>& operator=(const Vector<dim, T>& vec) = default;
            template<typename U> requires std::is_convertible_v<U, T>
            constexpr Vector<dim, T>& operator=(const Vector<dim, U>& vec);

            constexpr T& operator[](unsigned index);
            constexpr const T& operator[](unsigned index) const;

            constexpr Vector<dim, T>& operator+=(const Vector<dim, T>& vec);
            constexpr Vector<dim, T>& operator-=(const Vector<dim, T>& vec);
            constexpr Vector<dim, T>& operator*=(T scalar);
            constexpr Vector<dim, T>& operator/=(T scalar);

            constexpr Vector<dim, T>& operator-();

            bool operator==(const Vector<dim, T>& rhs) const;
            bool operator!=(const Vector<dim, T>& rhs) const;
    };

    template<unsigned dim, typename T> constexpr Vector<dim, T> operator+(const Vector<dim, T>& v1, const Vector<dim, T>& v2);
    template<unsigned dim, typename T> constexpr Vector<dim, T> operator-(const Vector<dim, T>& v1, const Vector<dim, T>& v2);
    template<unsigned dim, typename T> constexpr Vector<dim, T> operator*(const Vector<dim, T>& vec, T scalar);
    template<unsigned dim, typename T> constexpr Vector<dim, T> operator*(const Vector<dim, T>& v1, const Vector<dim, T>& v2);
    template<unsigned dim, typename T> constexpr Vector<dim, T> operator/(const Vector<dim, T>& vec, T scalar);
}

#include "Vector.tpp"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
