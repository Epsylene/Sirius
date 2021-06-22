
#pragma once

#include "Sirius/Math/Vector/Vector3.h"

namespace Sirius
{
    template<typename T> constexpr Matrix<4, T> operator+(const Matrix<4, T>& mat1, const Matrix<4, T>& mat2);
    template<typename T> constexpr Matrix<4, T> operator-(const Matrix<4, T>& mat1, const Matrix<4, T>& mat2);
    template<typename T> constexpr Matrix<4, T> operator*(const Matrix<4, T>& mat, T scalar);
    template<typename T> constexpr Vector<4, T> operator*(const Matrix<4, T>& mat, const Vector<4, T>& vec);
    template<typename T> constexpr Matrix<4, T> operator*(const Matrix<4, T>& mat1, const Matrix<4, T>& mat2);

    using Matrix4i = Matrix<4, int>;
    using Matrix4f = Matrix<4, float>;
    using Matrix4d = Matrix<4, double>;
}

#include "Matrix4.tpp"
