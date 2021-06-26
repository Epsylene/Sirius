
#pragma once

#include "Matrix.h"

namespace Sirius
{
    template<typename T> constexpr Matrix<4, T> operator+(const Matrix<4, T>& mat1, const Matrix<4, T>& mat2);
    template<typename T> constexpr Matrix<4, T> operator-(const Matrix<4, T>& mat1, const Matrix<4, T>& mat2);
    template<typename T> constexpr Matrix<4, T> operator*(const Matrix<4, T>& mat, T scalar);
    template<typename T> constexpr Matrix<4, T> operator*(const Matrix<4, T>& mat1, const Matrix<4, T>& mat2);
    template<typename T> constexpr Vector4<T> operator*(const Matrix<4, T>& mat, const Vector4<T>& vec);

    using Matrix4i = Matrix<4, int>;
    using Matrix4f = Matrix<4, float>;
    using Matrix4d = Matrix<4, double>;

    using Mat4 = Matrix4f;
}

#include "Matrix4.tpp"
