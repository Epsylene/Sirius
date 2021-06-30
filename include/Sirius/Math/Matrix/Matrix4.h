
#pragma once

#include "Matrix.h"

namespace Sirius
{
    ////////////////////////////////////////////
    /// @brief Binary 4-dimensional matrices sum
    template<typename T> constexpr Matrix<4, T> operator+(const Matrix<4, T>& mat1, const Matrix<4, T>& mat2);
    
    ///////////////////////////////////////////////////
    /// @brief Binary 4-dimensional matrices difference
    template<typename T> constexpr Matrix<4, T> operator-(const Matrix<4, T>& mat1, const Matrix<4, T>& mat2);
    
    ///////////////////////////////////////////////////////
    /// @brief Binary 4-dimensional matrices scalar product
    template<typename T> constexpr Matrix<4, T> operator*(const Matrix<4, T>& mat, T scalar);
    
    ////////////////////////////////////////////////
    /// @brief Binary 4-dimensional matrices product
    template<typename T> constexpr Matrix<4, T> operator*(const Matrix<4, T>& mat1, const Matrix<4, T>& mat2);
    
    /////////////////////////////////////////////////////
    /// @brief Binary 4-dimensional matrix-vector product
    template<typename T> constexpr Vector4<T> operator*(const Matrix<4, T>& mat, const Vector4<T>& vec);

    using Matrix4i = Matrix<4, int>;
    using Matrix4f = Matrix<4, float>;
    using Matrix4d = Matrix<4, double>;

    using Mat4 = Matrix4f;
}

#include "Matrix4.tpp"
