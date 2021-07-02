
#include "Vector2.hpp"

namespace Sirius
{
    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector<2, T>::Vector(T scalar): x(scalar), y(scalar)
    {}

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector<2, T>::Vector(T x, T y): x(x), y(y)
    {}

    template<typename T> requires std::is_scalar_v<T>
    template<typename U> requires std::is_convertible_v<U, T>
    constexpr Vector<2, T>& Vector<2, T>::operator=(const Vector<2, U>& vec)
    {
        this->x = static_cast<T>(vec.x);
        this->y = static_cast<T>(vec.y);

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr T& Vector<2, T>::operator[](unsigned int index)
    {
        switch (index)
        {
            default:
            case 0: return x;
            case 1: return y;
        }
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr const T& Vector<2, T>::operator[](unsigned int index) const
    {
        switch (index)
        {
            default:
            case 0: return x;
            case 1: return y;
        }
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector<2, T>& Vector<2, T>::operator+=(const Vector<2, T>& vec)
    {
        x += vec.x;
        y += vec.y;

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector<2, T>& Vector<2, T>::operator-=(const Vector<2, T>& vec)
    {
        x -= vec.x;
        y -= vec.y;

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector<2, T>& Vector<2, T>::operator*=(T scalar)
    {
        x *= scalar;
        y *= scalar;

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector<2, T>& Vector<2, T>::operator/=(T scalar)
    {
        x /= scalar;
        y /= scalar;

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector<2, T>& Vector<2, T>::operator*=(const Vector<2, T>& vec)
    {
        x *= vec.x;
        y *= vec.y;

        return *this;
    }

    template<typename T> requires std::is_scalar_v<T>
    bool Vector<2, T>::operator==(const Vector<2, T>& rhs) const
    {
        return x == rhs.x &&
               y == rhs.y;
    }

    template<typename T> requires std::is_scalar_v<T>
    bool Vector<2, T>::operator!=(const Vector<2, T>& rhs) const
    {
        return !(rhs == *this);
    }

    template<typename T> requires std::is_scalar_v<T>
    constexpr Vector<2, T> Vector<2, T>::operator-()
    {
        return { x ? -x : 0, y ? -y : 0 };
    }

    template<typename T>
    constexpr Vector<2, T> operator+(const Vector<2, T>& v1, const Vector<2, T>& v2)
    {
        return { v1.x + v2.x, v1.y + v2.y };
    }

    template<typename T>
    constexpr Vector<2, T> operator-(const Vector<2, T>& v1, const Vector<2, T>& v2)
    {
        return { v1.x - v2.x, v1.y - v2.y };
    }

    template<typename T>
    constexpr Vector<2, T> operator*(const Vector<2, T>& vec, T scalar)
    {
        return { vec.x * scalar, vec.y * scalar };
    }

    template<typename T>
    constexpr Vector<2, T> operator*(const Vector<2, T>& v1, const Vector<2, T>& v2)
    {
        return { v1.x * v2.x, v1.y * v2.y };
    }

    template<typename T>
    constexpr Vector<2, T> operator/(const Vector<2, T>& vec, T scalar)
    {
        return Vector<2, T>(vec.x / scalar, vec.y / scalar);
    }

    template<typename T> const T* value_ptr(const Vector<2, T>& vec)
    {
        return &(vec.x);
    }
}

template <typename T>
struct fmt::formatter<Sirius::Vector<2, T>>
{
    constexpr auto parse(format_parse_context& ctx)
    {
        return ctx.end();
    }

    template <typename Context>
    auto format(const Sirius::Vector<2, T>& vec, Context& ctx)
    {
        return format_to(ctx.out(), "({}, {})", vec.x, vec.y);
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const Sirius::Vector<2, T>& vec)
{
    return out << "(" << vec.x << ", " << vec.y << ")";
}