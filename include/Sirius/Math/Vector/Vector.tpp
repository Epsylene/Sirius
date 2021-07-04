
#include "Vector.hpp"

#include <spdlog/fmt/bundled/format.h>

namespace Sirius
{
    template<unsigned dim, typename T> requires std::is_scalar_v<T>
    constexpr Vector<dim, T>::Vector(T scalar)
    {
        for (auto& val: vals)
        {
            val = scalar;
        }
    }

    template<unsigned int dim, typename T> requires std::is_scalar_v<T>
    template<typename... Ts> requires (std::is_convertible_v<Ts, T> && ...)
    constexpr Vector<dim, T>::Vector(Ts... xs)
    {
        vals = { xs... };
    }

    template<unsigned int dim, typename T> requires std::is_scalar_v<T>
    template<unsigned dim2> requires (dim2 > dim)
    constexpr Vector<dim, T>::Vector(const Vector<dim2, T>& vec)
    {
        for (int i = 0; i < dim; ++i)
        {
            vals[i] = vec[i];
        }
    }

    template<unsigned int dim, typename T> requires std::is_scalar_v<T>
    template<unsigned dim2> requires (dim2 < dim)
    constexpr Vector<dim, T>::Vector(const Vector<dim2, T>& vec)
    {
        for (int i = 0; i < dim2; ++i)
        {
            vals[i] = vec[i];
        }
    }

    template<unsigned dim, typename T> requires std::is_scalar_v<T>
    template<typename U> requires std::is_convertible_v<U, T>
    constexpr Vector<dim, T>& Vector<dim, T>::operator=(const Vector<dim, U>& vec)
    {
        for (int i = 0; i < dim; ++i)
        {
            vals[i] = static_cast<T>(vec.vals[i]);
        }
    }

    template<unsigned dim, typename T> requires std::is_scalar_v<T>
    constexpr T& Vector<dim, T>::operator[](unsigned index)
    {
        return vals[index];
    }

    template<unsigned dim, typename T> requires std::is_scalar_v<T>
    constexpr const T& Vector<dim, T>::operator[](unsigned index) const
    {
        return vals[index];
    }

    template<unsigned dim, typename T> requires std::is_scalar_v<T>
    constexpr Vector<dim, T>& Vector<dim, T>::operator+=(const Vector<dim, T>& vec)
    {
        for (int i = 0; i < dim; ++i)
        {
            vals[i] += vec.vals[i];
        }

        return *this;
    }

    template<unsigned dim, typename T> requires std::is_scalar_v<T>
    constexpr Vector<dim, T>& Vector<dim, T>::operator-=(const Vector<dim, T>& vec)
    {
        for (int i = 0; i < dim; ++i)
        {
            vals[i] -= vec.vals[i];
        }

        return *this;
    }

    template<unsigned dim, typename T> requires std::is_scalar_v<T>
    constexpr Vector<dim, T>& Vector<dim, T>::operator*=(T scalar)
    {
        for (auto& val: vals)
        {
            val *= scalar;
        }

        return *this;
    }

    template<unsigned dim, typename T> requires std::is_scalar_v<T>
    constexpr Vector<dim, T>& Vector<dim, T>::operator/=(T scalar)
    {
        for (auto& val: vals)
        {
            val /= scalar;
        }

        return *this;
    }

    template<unsigned dim, typename T> requires std::is_scalar_v<T>
    constexpr Vector<dim, T>& Vector<dim, T>::operator*=(const Vector<dim, T>& vec)
    {
        for (int i = 0; i < dim; i++)
        {
            vals[i] *= vec[i];
        }

        return *this;
    }

    template<unsigned dim, typename T> requires std::is_scalar_v<T>
    bool Vector<dim, T>::operator==(const Vector<dim, T>& rhs) const
    {
        for (int i = 0; i < dim; ++i)
        {
            if(vals[i] != rhs[i])
                return false;
        }

        return true;
    }

    template<unsigned dim, typename T> requires std::is_scalar_v<T>
    bool Vector<dim, T>::operator!=(const Vector<dim, T>& rhs) const
    {
        return !(*this == rhs);
    }

    template<unsigned int dim, typename T> requires std::is_scalar_v<T>
    constexpr Vector<dim, T>& Vector<dim, T>::operator-()
    {
        for (int i = 0; i < dim; ++i)
        {
            vals[i] = vals[i] ? -vals[i] : 0;
        }

        return *this;
    }

    template<unsigned dim, typename T>
    constexpr Vector<dim, T> operator+(const Vector<dim, T>& v1, const Vector<dim, T>& v2)
    {
        Vector<dim, T> result {};

        for (int i = 0; i < dim; ++i)
        {
            result[i] = v1[i] + v2[i];
        }

        return result;
    }

    template<unsigned dim, typename T>
    constexpr Vector<dim, T> operator-(const Vector<dim, T>& v1, const Vector<dim, T>& v2)
    {
        Vector<dim, T> result {};

        for (int i = 0; i < dim; ++i)
        {
            result[i] = v1[i] - v2[i];
        }

        return result;
    }

    template<unsigned dim, typename T>
    constexpr Vector<dim, T> operator*(const Vector<dim, T>& vec, T scalar)
    {
        Vector<dim, T> result {};

        for (int i = 0; i < dim; ++i)
        {
            result[i] = vec[i] * scalar;
        }

        return result;
    }

    template<unsigned dim, typename T>
    constexpr Vector<dim, T> operator/(const Vector<dim, T>& vec, T scalar)
    {
        Vector<dim, T> result {};

        for (int i = 0; i < dim; ++i)
        {
            result[i] = vec[i] / scalar;
        }

        return result;
    }

    template<unsigned dim, typename T>
    constexpr Vector<dim, T> operator*(const Vector<dim, T>& v1, const Vector<dim, T>& v2)
    {
        Vector<dim, T> result {};

        for (int i = 0; i < dim; ++i)
        {
            result[i] = v1[i] * v2[i];
        }

        return result;
    }

    template<unsigned dim, typename T>
    const T* value_ptr(const Vector<dim, T>& vec)
    {
        return &(vec[0]);
    }
}

template <unsigned dim, typename T>
struct fmt::formatter<Sirius::Vector<dim, T>>
{
    constexpr auto parse(format_parse_context& ctx)
    {
        return ctx.end();
    }

    template <typename Context>
    auto format(const Sirius::Vector<dim, T>& vec, Context& ctx)
    {
        std::string formatStr = "(" + std::to_string(vec[0]);

        for (int i = 1; i < dim; ++i)
        {
            formatStr += ", " + std::to_string(vec[i]);
        }

        return format_to(ctx.out(), formatStr + ")");
    }
};

template<unsigned dim, typename T>
std::ostream& operator<<(std::ostream& out, const Sirius::Vector<dim, T>& vec)
{
    out << "(" << vec[0];

    for (int i = 1; i < dim; ++i)
    {
        out << ", " << vec[i];
    }

    return out << ")";
}