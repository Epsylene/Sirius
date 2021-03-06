
#include "Vector4.hpp"

namespace Sirius
{
    template<typename T> requires std::is_scalar_v<T>
    template<std::convertible_to<T> Ts>
    constexpr Vector<4, T>::Vector(Ts scalar): x(scalar), y(scalar), z(scalar), w(scalar)
    {}

    template<typename T> requires std::is_scalar_v<T>
    template<std::convertible_to<T> Ts>
    constexpr Vector<4, T>::Vector(Ts x, Ts y, Ts z, Ts w): x(x), y(y), z(z), w(w)
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
    template<std::convertible_to<T> U>
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
        return m[index];
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr const T& Vector<4, T>::operator[](unsigned int index) const
    {
        return m[index];
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
    template<std::convertible_to<T> Ts>
    constexpr Vector<4, T>& Vector<4, T>::operator*=(Ts scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    template<std::convertible_to<T> Ts>
    constexpr Vector<4, T>& Vector<4, T>::operator/=(Ts scalar)
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
    template<std::convertible_to<T> Ts>
    constexpr Vector<4, T>::Vector(const Vector<2, T>& vec, Ts z, Ts w):
        Vector(vec.x, vec.y, z, w)
    {}

    template<typename T> requires std::is_scalar_v<T>
    template<std::convertible_to<T> Ts>
    constexpr Vector<4, T>::Vector(const Vector<3, T>& vec, Ts w):
        Vector(vec.x, vec.y, vec.z, w)
    {}
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