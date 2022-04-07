
#include "Vector3.hpp"

namespace Sirius
{
    template<typename T> requires std::is_scalar_v<T>
    template<std::convertible_to<T> Ts>
    constexpr Vector<3, T>::Vector(Ts scalar): x(scalar), y(scalar), z(scalar)
    {}

    template<typename T> requires std::is_scalar_v<T>
    template<std::convertible_to<T> Ts>
    constexpr Vector<3, T>::Vector(Ts x, Ts y, Ts z): x(x), y(y), z(z)
    {}

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector<3, T>::Vector(const Vector<2, T>& vec):
        x(vec.x), y(vec.y), z(0)
    {}

    template<typename T> requires std::is_scalar_v<T>
    template<std::convertible_to<T> U>
    constexpr Vector<3, T>& Vector<3, T>::operator=(const Vector<3, U>& vec)
    {
        this->x = static_cast<T>(vec.x);
        this->y = static_cast<T>(vec.y);
        this->z = static_cast<T>(vec.z);

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr T& Vector<3, T>::operator[](unsigned int index)
    {
        return m[index];
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr const T& Vector<3, T>::operator[](unsigned int index) const
    {
        return m[index];
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector<3, T>& Vector<3, T>::operator+=(const Vector<3, T>& vec)
    {
        x += vec.x;
        y += vec.y;
        z += vec.z;

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector<3, T>& Vector<3, T>::operator-=(const Vector<3, T>& vec)
    {
        x -= vec.x;
        y -= vec.y;
        z -= vec.z;

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    template<std::convertible_to<T> Ts>
    constexpr Vector<3, T>& Vector<3, T>::operator*=(Ts scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    template<std::convertible_to<T> Ts>
    constexpr Vector<3, T>& Vector<3, T>::operator/=(Ts scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector<3, T>& Vector<3, T>::operator*=(const Vector<3, T>& vec)
    {
        x *= vec.x;
        y *= vec.y;
        z *= vec.z;

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    bool Vector<3, T>::operator==(const Vector<3, T>& rhs) const
    {
        return x == rhs.x &&
               y == rhs.y &&
               z == rhs.z;
    }

    template<typename T> requires std::is_scalar_v<T>
    bool Vector<3, T>::operator!=(const Vector<3, T>& rhs) const
    {
        return !(rhs == *this);
    }

    template<typename T> requires std::is_scalar_v<T>
    template<std::convertible_to<T> Ts>
    constexpr Vector<3, T>::Vector(const Vector<2, T>& vec, Ts z):
            Vector(vec.x, vec.y, z)
    {}
}

template <typename T>
struct fmt::formatter<Sirius::Vector<3, T>>
{
    constexpr auto parse(format_parse_context& ctx)
    {
        return ctx.end();
    }

    template <typename Context>
    auto format(const Sirius::Vector<3, T>& vec, Context& ctx)
    {
        return format_to(ctx.out(), "({}, {}, {})", vec.x, vec.y, vec.z);
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const Sirius::Vector<3, T>& vec)
{
    return out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
}