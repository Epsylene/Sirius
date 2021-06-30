
#include "clip_space.h"

namespace Sirius
{
    template<typename T> 
    constexpr Matrix<4, T> ortho(T left, T right, T bottom, T top)
    {
        return ortho(left, right, bottom, top, -static_cast<T>(1), static_cast<T>(1));
    }

    template<typename T> 
    constexpr Matrix<4, T> ortho(T left, T right, T bottom, T top, T near, T far)
    {
        Matrix<4, T> result { identity<4>() };

        result[0][0] = static_cast<T>(2) / (right - left);
        result[3][0] = - (right + left) / (right - left);
        result[1][1] = static_cast<T>(2) / (top - bottom);
        result[3][1] = - (top + bottom) / (top - bottom);
        result[2][2] = - static_cast<T>(2) / (far - near);
        result[3][2] = -(far + near) / (far - near);

        return result;
    }

    template<typename T>
    constexpr Matrix<4, T> perspective(T fov, T aspect, T near, T far)
    {
        T const tanHalfFov = std::tan(radians(fov) / static_cast<T>(2));

        Matrix<4, T> result { identity<4>() };
        result[0][0] = static_cast<T>(1) / (aspect * tanHalfFov);
        result[1][1] = static_cast<T>(1) / (tanHalfFov);
        result[2][2] = - (far + near) / (far - near);
        result[3][2] = - (static_cast<T>(2) * far * near) / (far - near);
        result[2][3] = - static_cast<T>(1);

        return result;
    }

    template<typename T>
    constexpr Matrix<4, T> perspective_planes(T left, T right, T bottom, T top)
    {
        return perspective_planes(left, right, bottom, top, -static_cast<T>(1), static_cast<T>(1));
    }

    template<typename T>
    constexpr Matrix<4, T> perspective_planes(T left, T right, T bottom, T top, T near, T far)
    {
        Matrix<4, T> result {};
        result[0][0] = static_cast<T>(2) * near / (right - left);
        result[3][0] = (right + left) / (right - left);
        result[1][1] = static_cast<T>(2) * near / (top - bottom);
        result[2][1] = (top + bottom) / (top - bottom);
        result[2][2] = - (far + near) / (far - near);
        result[3][2] = - static_cast<T>(2) * far * near / (far - near);
        result[2][3] = - static_cast<T>(1);

        return result;
    }
}