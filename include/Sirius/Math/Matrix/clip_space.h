
#pragma once

#include "Matrix.h"

namespace Sirius
{
    template<typename T> constexpr Matrix<4, T> ortho(T left, T right, T bottom, T top);
    template<typename T> constexpr Matrix<4, T> ortho(T left, T right, T bottom, T top, T near, T far);

    template<typename T> constexpr Matrix<4, T> perspective(T fov, T aspect, T near, T far);
    template<typename T> constexpr Matrix<4, T> perspective_planes(T left, T right, T bottom, T top);
    template<typename T> constexpr Matrix<4, T> perspective_planes(T left, T right, T bottom, T top, T near, T far);
}

#include "clip_space.tpp"
