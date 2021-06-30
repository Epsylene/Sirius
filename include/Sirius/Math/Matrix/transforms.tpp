
#include "transforms.h"

#include "Sirius/Math/Vector/transforms.h"

namespace Sirius
{
    template<unsigned dim, typename T>
    constexpr Matrix<dim, T> identity()
    {
        Matrix<dim, T> result;

        for (int i = 0; i < dim; ++i)
        {
            result[i][i] = static_cast<T>(1);
        }

        return result;
    }

    template<typename T>
    constexpr Matrix<4, T> translate(const Vector<3, T>& direction)
    {
        Matrix<4, T> result = identity<4, T>();
        result[3][0] = direction.x;
        result[3][1] = direction.y;
        result[3][2] = direction.z;

        return result;
    }

    template<typename T>
    constexpr Matrix<4, T> rotate(const Vector<3, T>& axis, T angle)
    {
        T const c = std::cos(angle);
        T const s = std::sin(angle);

        Vector<3, T> n_axis { normalize(axis) };
        Vector<3, T> temp {  n_axis * (static_cast<T>(1) - c) };

        Matrix<4, T> rotate;
        rotate[0][0] = c + temp[0] * n_axis[0];
        rotate[0][1] = temp[0] * n_axis[1] + s * n_axis[2];
        rotate[0][2] = temp[0] * n_axis[2] - s * n_axis[1];

        rotate[1][0] = temp[1] * n_axis[0] - s * n_axis[2];
        rotate[1][1] = c + temp[1] * n_axis[1];
        rotate[1][2] = temp[1] * n_axis[2] + s * n_axis[0];

        rotate[2][0] = temp[2] * n_axis[0] + s * n_axis[1];
        rotate[2][1] = temp[2] * n_axis[1] - s * n_axis[0];
        rotate[2][2] = c + temp[2] * n_axis[2];

        Matrix<4, T> result;
        result[0] = Vector<4, T>(rotate[0][0], rotate[0][1], rotate[0][2], static_cast<T>(0));
        result[1] = Vector<4, T>(rotate[1][0], rotate[1][1], rotate[1][2], static_cast<T>(0));
        result[2] = Vector<4, T>(rotate[2][0], rotate[2][1], rotate[2][2], static_cast<T>(0));
        result[3][3] = static_cast<T>(1);

        return result;
    }

    template<typename T>
    constexpr Matrix<4, T> scale(const Vector<3, T>& direction)
    {
        Matrix<4, T> result;
        result[0][0] = direction[0];
        result[1][1] = direction[1];
        result[2][2] = direction[2];
        result[3][3] = static_cast<T>(1);

        return result;
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Matrix<4, T> scale(T factor)
    {
        return scale(Vector<3, T>(factor));
    }

    template<typename T>
    constexpr Matrix<4, T> lookAt(const Vector<3, T>& eye, const Vector<3, T>& center, const Vector<3, T>& up)
    {
        Vector<3, T> forward { normalize(center - eye) };
        Vector<3, T> right { normalize(cross(forward, up)) };
        Vector<3, T> n_up { cross(right, forward) };

        Matrix<4, T> result { identity<4>() };
        result[0][0] = right.x;
        result[1][0] = right.y;
        result[2][0] = right.z;
        result[0][1] = n_up.x;
        result[1][1] = n_up.y;
        result[2][1] = n_up.z;
        result[0][2] = -forward.x;
        result[1][2] = -forward.y;
        result[2][2] = -forward.z;
        result[3][0] = -dot(right, eye);
        result[3][1] = -dot(n_up, eye);
        result[3][2] = dot(forward, eye);

        return result;
    }
}