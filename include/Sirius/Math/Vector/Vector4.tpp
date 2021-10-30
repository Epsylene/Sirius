
#include "Vector4.hpp"

namespace Sirius
{
    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector<4, T>::Vector(T scalar): x(scalar), y(scalar), z(scalar), w(scalar)
    {}

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector<4, T>::Vector(T x, T y, T z, T w): x(x), y(y), z(z), w(w)
    {}

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector<4, T>::Vector(const Vector<2, T>& vec):
            x(vec.x), y(vec.y), z(0), w(0)
    {}

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector<4, T>::Vector(const Vector<3, T>& vec):
            x(vec.x), y(vec.y), z(vec.z), w(0)
    {}

    template<typename T> requires std::is_scalar_v<T>
    template<typename U> requires std::is_convertible_v<U, T>
    constexpr Vector<4, T>& Vector<4, T>::operator=(const Vector<4, U>& vec)
    {
        this->x = static_cast<T>(vec.x);
        this->y = static_cast<T>(vec.y);
        this->z = static_cast<T>(vec.z);
        this->w = static_cast<T>(vec.w);

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr T& Vector<4, T>::operator[](unsigned int index)
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
    constexpr const T& Vector<4, T>::operator[](unsigned int index) const
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
    constexpr Vector<4, T>& Vector<4, T>::operator+=(const Vector<4, T>& vec)
    {
        x += vec.x;
        y += vec.y;
        z += vec.z;
        w += vec.w;

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector<4, T>& Vector<4, T>::operator-=(const Vector<4, T>& vec)
    {
        x -= vec.x;
        y -= vec.y;
        z -= vec.z;
        w -= vec.w;

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector<4, T>& Vector<4, T>::operator*=(T scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector<4, T>& Vector<4, T>::operator/=(T scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector<4, T>& Vector<4, T>::operator*=(const Vector<4, T>& vec)
    {
        x *= vec.x;
        y *= vec.y;
        z *= vec.z;
        w *= vec.w;

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    bool Vector<4, T>::operator==(const Vector<4, T>& rhs) const
    {
        return x == rhs.x &&
               y == rhs.y &&
               z == rhs.z &&
               w == rhs.w;
    }

    template<typename T> requires std::is_scalar_v<T>
    bool Vector<4, T>::operator!=(const Vector<4, T>& rhs) const
    {
        return !(rhs == *this);
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector<4, T> Vector<4, T>::operator-()
    {
        return {x ? -x : 0, y ? -y : 0, z ? -z : 0, w ? -w : 0};
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector<4, T>::Vector(const Vector<2, T>& vec, T z, T w):
        Vector(vec.x, vec.y, z, w)
    {}

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector<4, T>::Vector(const Vector<3, T>& vec, T w):
        Vector(vec.x, vec.y, vec.z, w)
    {}

    template<typename T>
    constexpr Vector<4, T> operator+(const Vector<4, T>& v1, const Vector<4, T>& v2)
    {
        return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w };
    }

    template<typename T>
    constexpr Vector<4, T> operator-(const Vector<4, T>& v1, const Vector<4, T>& v2)
    {
        return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w };
    }

    template<typename T>
    constexpr Vector<4, T> operator*(const Vector<4, T>& vec, T scalar)
    {
        return { vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar };
    }

    template<typename T>
    constexpr Vector<4, T> operator*(const Vector<4, T>& v1, const Vector<4, T>& v2)
    {
        return { v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w };
    }

    template<typename T>
    constexpr Vector<4, T> operator/(const Vector<4, T>& vec, T scalar)
    {
        return Vector<4, T>(vec.x / scalar, vec.y / scalar, vec.z / scalar, vec.w / scalar);
    }
}

template <typename T>
struct fmt::formatter<Sirius::Vector<4, T>>
{
    constexpr auto parse(format_parse_context& ctx)
    {
        return ctx.end();
    }

    template <typename Context>
    auto format(const Sirius::Vector<4, T>& vec, Context& ctx)
    {
        return format_to(ctx.out(), "({}, {}, {}, {})", vec.x, vec.y, vec.z, vec.w);
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const Sirius::Vector<4, T>& vec)
{
    return out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
}