
#include "transforms.h"

#include "Sirius/Math/Matrix/Matrix.h"

namespace Sirius
{
    template<unsigned dim, typename T>
    constexpr T dot(const Vector<dim, T>& v1, const Vector<dim, T>& v2)
    {
        T result = static_cast<T>(0);

        for (int i = 0; i < dim; ++i)
        {
            result += v1[i] * v2[i];
        }

        return result;
    }

    template<typename T>
    constexpr T dot(const Vector<2, T>& v1, const Vector<2, T>& v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

    template<typename T>
    constexpr T dot(const Vector<3, T>& v1, const Vector<3, T>& v2)
    {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    template<typename T>
    constexpr T dot(const Vector<4, T>& v1, const Vector<4, T>& v2)
    {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
    }

    template<typename T> 
    constexpr Vector<3, T> cross(const Vector<3, T>& v1, const Vector<3, T>& v2)
    {
        return Vector<3, T>(
                v1.y * v2.z - v2.y * v1.z,
                v1.z * v2.x - v2.z * v1.x,
                v1.x * v2.y - v2.x * v1.y);
    }

    template<unsigned dim, typename T> requires std::is_floating_point_v<T>
    constexpr Vector<dim, T> normalize(const Vector<dim, T>& vec)
    {
        return vec / std::sqrt(dot(vec, vec));
    }

    template<typename T>
    constexpr Vector<2, T> normalize(const Vector<2, T>& vec)
    {
        return normalize<2, T>(vec);
    }

    template<typename T>
    constexpr Vector<3, T> normalize(const Vector<3, T>& vec)
    {
        auto result = normalize<3, T>(vec);
        return {result[0], result[1], result[2]};
    }

    template<typename T>
    constexpr Vector<4, T> normalize(const Vector<4, T>& vec)
    {
        auto result = normalize<4, T>(vec);
        return {result[0], result[1], result[2], result[3]};
    }

    template<typename T>
    constexpr Vector<2, T> rotate(const Vector<2, T>& vec, T angle)
    {
        return { vec.x * std::cos(angle) - vec.y * std::sin(angle),
                 vec.x  * std::sin(angle) + vec.y * std::cos(angle) };
    }

    template<typename T>
    constexpr Vector<3, T> rotate(const Vector<3, T>& vec, const Vector<3, T>& axis, T angle)
    {
        return { Matrix<3, T>(rotate(axis, angle)) * vec };
    }

    template<typename T>
    constexpr Vector<4, T> rotate(const Vector<4, T>& vec, const Vector<3, T>& axis, T angle)
    {
        return { rotate(axis, angle) * vec };
    }
}
