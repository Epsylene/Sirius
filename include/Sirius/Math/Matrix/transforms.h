
#pragma once

#include "Matrix.h"

namespace Sirius
{
    template<unsigned dim, typename T = float> constexpr Matrix<dim, T> identity();

    template<typename T> constexpr Matrix<4, T> translate(const Vector3<T>& direction);
    template<typename T> constexpr Matrix<4, T> rotate(const Vector3<T>& axis, T angle);
    template<typename T> constexpr Matrix<4, T> scale(const Vector3<T>& direction);
    template<typename T> requires std::is_scalar_v<T> constexpr Matrix<4, T> scale(T factor);

    template<typename T> constexpr Matrix<4, T> lookAt(const Vector3<T>& eye, const Vector3<T>& center, const Vector3<T>& up);
}

#include "transforms.tpp"
