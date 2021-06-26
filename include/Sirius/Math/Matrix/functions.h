
#pragma once

#include "Matrix.h"

namespace Sirius
{
    template<typename T> constexpr Matrix<2, T> inverse(const Matrix<2, T>& mat);
    template<typename T> constexpr Matrix<3, T> inverse(const Matrix<3, T>& mat);
    template<typename T> constexpr Matrix<4, T> inverse(const Matrix<4, T>& mat);
}

#include "functions.tpp"
