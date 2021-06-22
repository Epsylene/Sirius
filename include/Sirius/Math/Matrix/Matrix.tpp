
#include "Matrix.h"

namespace Sirius
{
    template<unsigned int dim, typename T>
    template<typename T1, typename... Ts> requires std::is_convertible_v<T1, Vector<dim, T>>
    constexpr Matrix<dim, T>::Matrix(const T1& c1, const Ts&... cs)
    {
        columns = { c1, cs... };
    }

    template<unsigned int dim, typename T>
    template<typename T1, typename... Ts> requires std::is_convertible_v<T1, T>
    constexpr Matrix<dim, T>::Matrix(T1 val, Ts... vals)
    {
        std::array<T, dim> scalars = { val, vals...};
        Vector <dim, T> column = {};

        for (int i = 0; i < dim; ++i)
        {
            for (int j = 0; j < dim; ++j)
            {
                column[j] = scalars[j];
            }

            columns[i] = column;
        }
    }

    template<unsigned dim, typename T>
    template<typename U>
    constexpr Matrix<dim, T>& Matrix<dim, T>::operator=(const Matrix<dim, U>& mat)
    {
        for (int i = 0; i < dim; ++i)
        {
            columns[i] = static_cast<T>(mat.columns[i]);
        }
    }

    template<unsigned dim, typename T>
    Vector<dim, T>& Matrix<dim, T>::operator[](unsigned int column)
    {
        return columns[column];
    }

    template<unsigned dim, typename T>
    const Vector<dim, T>& Matrix<dim, T>::operator[](unsigned int column) const
    {
        return columns[column];
    }

    template<unsigned dim, typename T>
    constexpr Matrix<dim, T>& Matrix<dim, T>::operator+=(const Matrix<dim, T>& mat)
    {
        for (int i = 0; i < dim; ++i)
        {
            columns[i] += mat.columns[i];
        }

        return *this;
    }

    template<unsigned dim, typename T>
    constexpr Matrix<dim, T>& Matrix<dim, T>::operator-=(const Matrix<dim, T>& mat)
    {
        for (int i = 0; i < dim; ++i)
        {
            columns[i] -= mat.columns[i];
        }

        return *this;
    }

    template<unsigned dim, typename T>
    constexpr Matrix<dim, T>& Matrix<dim, T>::operator*=(T scalar)
    {
        for (int i = 0; i < dim; ++i)
        {
            columns[i] *= scalar;
        }

        return *this;
    }

    template<unsigned dim, typename T>
    constexpr Matrix<dim, T>& Matrix<dim, T>::operator*=(const Matrix<dim, T>& mat)
    {
        return (*this = *this * mat);
    }

    template<unsigned dim, typename T>
    constexpr Matrix<dim, T>& Matrix<dim, T>::operator/=(T scalar)
    {
        for (int i = 0; i < dim; ++i)
        {
            columns[i] /= scalar;
        }

        return *this;
    }

    template<unsigned int dim, typename T>
    bool Matrix<dim, T>::operator==(const Matrix <dim, T>& rhs) const
    {
        for (int i = 0; i < dim; ++i)
        {
            if(columns[i] != rhs.columns[i])
                return false;
        }

        return true;
    }

    template<unsigned int dim, typename T>
    bool Matrix<dim, T>::operator!=(const Matrix <dim, T>& rhs) const
    {
        return !(*this == rhs);
    }
}

template <unsigned dim, typename T>
struct fmt::formatter<Sirius::Matrix<dim, T>>
{
    constexpr auto parse(format_parse_context& ctx)
    {
        return ctx.end();
    }

    template <typename Context>
    auto format(const Sirius::Matrix<dim, T>& mat, Context& ctx)
    {
        std::string formatStr = "\n[" + std::to_string(mat[0][0]);

        for (int j = 1; j < dim; ++j)
        {
            formatStr += " " + std::to_string(mat[j][0]);
        }

        formatStr += "]";

        for (int i = 1; i < dim; ++i)
        {
            formatStr += "\n[" + std::to_string(mat[0][i]);

            for (int j = 1; j < dim; ++j)
            {
                formatStr += " " + std::to_string(mat[j][i]);
            }

            formatStr += "]";
        }

        return format_to(ctx.out(), formatStr);
    }
};

template<unsigned dim, typename T>
std::ostream& operator<<(std::ostream& out, const Sirius::Matrix<dim, T>& mat)
{

}
