
#include "Vector.h"

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
    template<typename... Ts> requires std::is_scalar_v<T>
    constexpr Vector<dim, T>::Vector(Ts... xs)
    {
        vals = { xs... };
    }

    template<unsigned dim, typename T> requires std::is_scalar_v<T>
    template<typename U>
    constexpr Vector<dim, T>& Vector<dim, T>::operator=(const Vector<dim, U>& vec)
    {
        for (int i = 0; i < dim; ++i)
        {
            vals[i] = static_cast<T>(vec.vals[i]);
        }
    }

    template<unsigned dim, typename T> requires std::is_scalar_v<T>
    constexpr T Vector<dim, T>::operator[](unsigned index)
    {
        return vals[index];
    }

    template<unsigned dim, typename T> requires std::is_scalar_v<T>
    constexpr T Vector<dim, T>::operator[](unsigned index) const
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
    }

    template<unsigned dim, typename T> requires std::is_scalar_v<T>
    constexpr Vector<dim, T>& Vector<dim, T>::operator/=(T scalar)
    {
        for (auto& val: vals)
        {
            val /= scalar;
        }
    }

    template<unsigned dim, typename T> requires std::is_scalar_v<T>
    bool Vector<dim, T>::operator==(const Vector<dim, T>& rhs) const
    {
        for (int i = 0; i < dim; ++i)
        {
            if(vals[i] != rhs.vals[i])
                return false;
        }

        return true;
    }

    template<unsigned dim, typename T> requires std::is_scalar_v<T>
    bool Vector<dim, T>::operator!=(const Vector<dim, T>& rhs) const
    {
        return !(*this == rhs);
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
    requires std::integral<T>
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