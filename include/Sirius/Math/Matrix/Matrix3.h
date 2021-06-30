
#pragma once

#include "Sirius/Math/Vector/Vector3.h"

namespace Sirius
{
    ////////////////////////////////////////////
    /// @brief Binary 3-dimensional matrices sum
    template<typename T> constexpr Matrix<3, T> operator+(const Matrix<3, T>& mat1, const Matrix<3, T>& mat2);
    
    ///////////////////////////////////////////////////
    /// @brief Binary 3-dimensional matrices difference
    template<typename T> constexpr Matrix<3, T> operator-(const Matrix<3, T>& mat1, const Matrix<3, T>& mat2);
    
    ///////////////////////////////////////////////////////
    /// @brief Binary 3-dimensional matrices scalar product
    template<typename T> constexpr Matrix<3, T> operator*(const Matrix<3, T>& mat, T scalar);
    
    ////////////////////////////////////////////////
    /// @brief Binary 3-dimensional matrices product
    template<typename T> constexpr Matrix<3, T> operator*(const Matrix<3, T>& mat1, const Matrix<3, T>& mat2);
    
    /////////////////////////////////////////////////////
    /// @brief Binary 3-dimensional matrix-vector product
    template<typename T> constexpr Vector3<T> operator*(const Matrix<3, T>& mat, const Vector3<T>& vec);

    using Matrix3i = Matrix<3, int>;
    using Matrix3f = Matrix<3, float>;
    using Matrix3d = Matrix<3, double>;

    using Mat3 = Matrix3f;
}

#include "Matrix3.tpp"
