
#pragma once

#include "Matrix.h"

namespace Sirius
{
    template<typename T> constexpr Matrix<2, T> operator+(const Matrix<2, T>& mat1, const Matrix<2, T>& mat2);
    template<typename T> constexpr Matrix<2, T> operator-(const Matrix<2, T>& mat1, const Matrix<2, T>& mat2);
    template<typename T> constexpr Matrix<2, T> operator*(const Matrix<2, T>& mat, T scalar);
    template<typename T> constexpr Matrix<2, T> operator*(const Matrix<2, T>& mat1, const Matrix<2, T>& mat2);
    template<typename T> constexpr Vector2<T> operator*(const Matrix<2, T>& mat, const Vector2<T>& vec);

    using Matrix2i = Matrix<2, int>;
    using Matrix2f = Matrix<2, float>;
    using Matrix2d = Matrix<2, double>;

    using Mat2 = Matrix2f;
}

#include "Matrix2.tpp"
