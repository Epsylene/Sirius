
#pragma once

#include "Matrix.hpp"

namespace Sirius
{
    ///////////////////////////////////////
    /// @brief 2-dimensional matrix inverse
    template<typename T> constexpr Matrix<2, T> inverse(const Matrix<2, T>& mat);
    
    ///////////////////////////////////////
    /// @brief 3-dimensional matrix inverse
    template<typename T> constexpr Matrix<3, T> inverse(const Matrix<3, T>& mat);
    
    ///////////////////////////////////////
    /// @brief 4-dimensional matrix inverse
    template<typename T> constexpr Matrix<4, T> inverse(const Matrix<4, T>& mat);

    template<typename T> constexpr Matrix<2, T> transpose(const Matrix<2, T>& mat);
    template<typename T> constexpr Matrix<3, T> transpose(const Matrix<3, T>& mat);
    template<typename T> constexpr Matrix<4, T> transpose(const Matrix<4, T>& mat);
}

#include "functions.tpp"
