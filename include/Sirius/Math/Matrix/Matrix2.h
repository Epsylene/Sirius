
#pragma once

#include "Matrix.h"

namespace Sirius
{
    template<typename T> constexpr Matrix<2, T> operator+(const Matrix<2, T>& mat1, const Matrix<2, T>& mat2);
    template<typename T> constexpr Matrix<2, T> operator-(const Matrix<2, T>& mat1, const Matrix<2, T>& mat2);
    template<typename T> constexpr Matrix<2, T> operator*(const Matrix<2, T>& mat, T scalar);
    template<typename T> constexpr Vector<2, T> operator*(const Matrix<2, T>& mat, const Vector<2, T>& vec);
    template<typename T> constexpr Matrix<2, T> operator*(const Matrix<2, T>& mat1, const Matrix<2, T>& mat2);

    using Matrix2i = Matrix<2, int>;
    using Matrix2f = Matrix<2, float>;
    using Matrix2d = Matrix<2, double>;
}

#include "Matrix2.tpp"
