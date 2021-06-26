
#pragma once

#include "Vector.h"

namespace Sirius
{
    template<unsigned dim, typename T> constexpr T dot(const Vector<dim, T>& v1, const Vector<dim, T>& v2);
    template<typename T> constexpr T dot(const Vector2<T>& v1, const Vector2<T>& v2);
    template<typename T> constexpr T dot(const Vector3<T>& v1, const Vector3<T>& v2);
    template<typename T> constexpr T dot(const Vector4<T>& v1, const Vector4<T>& v2);

    template<typename T> constexpr Vector3<T> cross(const Vector3<T>& v1, const Vector3<T>& v2);

    template<unsigned dim, typename T> requires std::is_floating_point_v<T>
    constexpr Vector<dim, T> normalize(const Vector<dim, T>& vec);
    template<typename T> constexpr Vector2<T> normalize(const Vector2<T>& vec);
    template<typename T> constexpr Vector3<T> normalize(const Vector3<T>& vec);
    template<typename T> constexpr Vector4<T> normalize(const Vector4<T>& vec);

    template<typename T> constexpr Vector2<T> rotate(const Vector2<T>& vec, T angle);
    template<typename T> constexpr Vector3<T> rotate(const Vector3<T>& vec, const Vector3<T>& axis, T angle);
    template<typename T> constexpr Vector4<T> rotate(const Vector4<T>& vec, const Vector3<T>& axis, T angle);
}

#include "transforms.tpp"
