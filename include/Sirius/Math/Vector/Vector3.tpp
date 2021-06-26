
#include "Vector3.h"

namespace Sirius
{
    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector3<T>::Vector3(T scalar): x(scalar), y(scalar), z(scalar)
    {}

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector3<T>::Vector3(T x, T y, T z): x(x), y(y), z(z)
    {}

    template<typename T> requires std::is_scalar_v<T>
    template<typename U>
    constexpr Vector3<T>& Vector3<T>::operator=(const Vector3<U>& vec)
    {
        this->x = static_cast<T>(vec.x);
        this->y = static_cast<T>(vec.y);
        this->z = static_cast<T>(vec.z);

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    T Vector3<T>::operator[](unsigned int index)
    {
        switch (index)
        {
            default:
            case 0: return x;
            case 1: return y;
            case 2: return z;
        }
    }

    template<typename T> requires std::is_scalar_v<T>
    const T Vector3<T>::operator[](unsigned int index) const
    {
        switch (index)
        {
            default:
            case 0: return x;
            case 1: return y;
            case 2: return z;
        }
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& vec)
    {
        x += vec.x;
        y += vec.y;
        z += vec.z;

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& vec)
    {
        x -= vec.x;
        y -= vec.y;
        z -= vec.z;

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector3<T>& Vector3<T>::operator*=(T scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector3<T>& Vector3<T>::operator/=(T scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    bool Vector3<T>::operator==(const Vector3<T>& rhs) const
    {
        return x == rhs.x &&
               y == rhs.y &&
               z == rhs.z;
    }

    template<typename T> requires std::is_scalar_v<T>
    bool Vector3<T>::operator!=(const Vector3<T>& rhs) const
    {
        return !(rhs == *this);
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector3<T>::operator Vector<3, T>() const
    {
        return Vector<3, T>(x, y, z);
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector3<T> Vector3<T>::operator-()
    {
        return {x ? -x : 0, y ? -y : 0, z ? -z : 0};
    }

    template<typename T>
    constexpr Vector3<T> operator+(const Vector3<T>& v1, const Vector3<T>& v2)
    {
        return Vector3<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
    }

    template<typename T>
    constexpr Vector3<T> operator-(const Vector3<T>& v1, const Vector3<T>& v2)
    {
        return Vector3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
    }

    template<typename T>
    constexpr Vector3<T> operator*(const Vector3<T>& vec, T scalar)
    {
        return Vector3<T>(vec.x * scalar, vec.y * scalar, vec.z * scalar);
    }

    template<typename T>
    constexpr Vector3<T> operator*(const Vector3<T>& v1, const Vector3<T>& v2)
    {
        return { v1.x * v2.x, v1.y * v2.y, v1.z * v2.z };
    }

    template<typename T>
    constexpr Vector3<T> operator/(const Vector3<T>& vec, T scalar)
    {
        return Vector3<T>(vec.x / scalar, vec.y / scalar, vec.z / scalar);
    }
}

template <typename T>
struct fmt::formatter<Sirius::Vector3<T>>
{
    constexpr auto parse(format_parse_context& ctx)
    {
        return ctx.end();
    }

    template <typename Context>
    auto format(const Sirius::Vector3<T>& vec, Context& ctx)
    {
        return format_to(ctx.out(), "({}, {}, {})", vec.x, vec.y, vec.z);
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const Sirius::Vector3<T>& vec)
{
    return out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
}