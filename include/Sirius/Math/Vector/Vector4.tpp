
#include "Vector4.h"

namespace Sirius
{
    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector4<T>::Vector4(T scalar): x(scalar), y(scalar), z(scalar), w(scalar)
    {}

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector4<T>::Vector4(T x, T y, T z, T w): x(x), y(y), z(z), w(w)
    {}

    template<typename T> requires std::is_scalar_v<T>
    template<typename U>
    constexpr Vector4<T>& Vector4<T>::operator=(const Vector4<U>& vec)
    {
        this->x = static_cast<T>(vec.x);
        this->y = static_cast<T>(vec.y);
        this->z = static_cast<T>(vec.z);
        this->w = static_cast<T>(vec.w);

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    T Vector4<T>::operator[](unsigned int index)
    {
        switch (index)
        {
            default: return;
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
        }
    }

    template<typename T> requires std::is_scalar_v<T>
    const T Vector4<T>::operator[](unsigned int index) const
    {
        switch (index)
        {
            default:
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
        }
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector4<T>& Vector4<T>::operator+=(const Vector4<T>& vec)
    {
        x += vec.x;
        y += vec.y;
        z += vec.z;
        w += vec.w;

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector4<T>& Vector4<T>::operator-=(const Vector4<T>& vec)
    {
        x -= vec.x;
        y -= vec.y;
        z -= vec.z;
        w -= vec.w;

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector4<T>& Vector4<T>::operator*=(T scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector4<T>& Vector4<T>::operator/=(T scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    bool Vector4<T>::operator==(const Vector4<T>& rhs) const
    {
        return x == rhs.x &&
               y == rhs.y &&
               z == rhs.z &&
               w == rhs.w;
    }

    template<typename T> requires std::is_scalar_v<T>
    bool Vector4<T>::operator!=(const Vector4<T>& rhs) const
    {
        return !(rhs == *this);
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector4<T>::operator Vector<4, T>() const
    {
        return Vector<4, T>(x, y, z, w);
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector4<T> Vector4<T>::operator-()
    {
        return {x ? -x : 0, y ? -y : 0, z ? -z : 0, w ? -w : 0};
    }

    template<typename T>
    constexpr Vector4<T> operator+(const Vector4<T>& v1, const Vector4<T>& v2)
    {
        return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w };
    }

    template<typename T>
    constexpr Vector4<T> operator-(const Vector4<T>& v1, const Vector4<T>& v2)
    {
        return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w };
    }

    template<typename T>
    constexpr Vector4<T> operator*(const Vector4<T>& vec, T scalar)
    {
        return { vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar };
    }

    template<typename T>
    constexpr Vector4<T> operator*(const Vector4<T>& v1, const Vector4<T>& v2)
    {
        return { v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w };
    }

    template<typename T> constexpr Vector4<T> operator*(const Vector<4, T>& v1, const Vector4<T>& v2)
    {
        return { v1[0] * v2.x, v1[1] * v2.y, v1[2] * v2.z, v1[3] * v2.w };
    }

    template<typename T>
    constexpr Vector4<T> operator/(const Vector4<T>& vec, T scalar)
    {
        return Vector4<T>(vec.x / scalar, vec.y / scalar, vec.z / scalar, vec.w / scalar);
    }
}

template <typename T>
struct fmt::formatter<Sirius::Vector4<T>>
{
    constexpr auto parse(format_parse_context& ctx)
    {
        return ctx.end();
    }

    template <typename Context>
    auto format(const Sirius::Vector4<T>& vec, Context& ctx)
    {
        return format_to(ctx.out(), "({}, {}, {}, {})", vec.x, vec.y, vec.z, vec.w);
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const Sirius::Vector4<T>& vec)
{
    return out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
}