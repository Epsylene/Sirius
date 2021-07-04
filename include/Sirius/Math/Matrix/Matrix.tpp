
#include "Matrix.hpp"

namespace Sirius
{
    template<unsigned int dim, typename T> requires std::is_scalar_v<T>
    constexpr Matrix<dim, T>::Matrix(T val)
    {
        for (int i = 0; i < dim; ++i)
        {
            for (int j = 0; j < dim; ++j)
            {
                columns[i][j] = val;
            }
        }
    }

    template<unsigned int dim, typename T> requires std::is_scalar_v<T>
    template<typename... Cs> constexpr Matrix<dim, T>::Matrix(const Vector<dim, Cs>&... cs)
    {
        columns = { cs... };
    }

    template<unsigned int dim, typename T> requires std::is_scalar_v<T>
    template<typename... Ts> requires (std::is_convertible_v<Ts, T> && ...)
    constexpr Matrix<dim, T>::Matrix(Ts... vals)
    {
        std::array<T, dim * dim> scalars = { vals...};
        Vector <dim, T> column = {};

        for (int i = 0; i < dim; ++i)
        {
            for (int j = 0; j < dim; ++j)
            {
                column[j] = scalars[i + j * dim];
            }

            columns[i] = column;
        }
    }

    template<unsigned dim, typename T> requires std::is_scalar_v<T>
    template<unsigned dim2> requires (dim2 < dim)
    constexpr Matrix<dim, T>::Matrix(const Matrix<dim2, T>& mat)
    {
        for (int i = 0; i < dim2; ++i)
        {
            for (int j = 0; j < dim2; ++j)
            {
                columns[i][j] = mat[i][j];
            }
        }
    }

    template<unsigned dim, typename T> requires std::is_scalar_v<T>
    template<unsigned dim2> requires (dim2 > dim)
    constexpr Matrix<dim, T>::Matrix(const Matrix<dim2, T>& mat)
    {
        for (int i = 0; i < dim; ++i)
        {
            for (int j = 0; j < dim; ++j)
            {
                columns[i][j] = mat[i][j];
            }
        }
    }

    template<unsigned dim, typename T> requires std::is_scalar_v<T>
    template<typename U> requires std::is_convertible_v<U, T>
    constexpr Matrix<dim, T>& Matrix<dim, T>::operator=(const Matrix<dim, U>& mat)
    {
        for (int i = 0; i < dim; ++i)
        {
            columns[i] = static_cast<T>(mat.columns[i]);
        }
    }

    template<unsigned dim, typename T> requires std::is_scalar_v<T>
    Vector<dim, T>& Matrix<dim, T>::operator[](unsigned int column)
    {
        return columns[column];
    }

    template<unsigned dim, typename T> requires std::is_scalar_v<T>
    const Vector<dim, T>& Matrix<dim, T>::operator[](unsigned int column) const
    {
        return columns[column];
    }

    template<unsigned dim, typename T> requires std::is_scalar_v<T>
    constexpr Matrix<dim, T>& Matrix<dim, T>::operator+=(const Matrix<dim, T>& mat)
    {
        for (int i = 0; i < dim; ++i)
        {
            columns[i] += mat.columns[i];
        }

        return *this;
    }

    template<unsigned dim, typename T> requires std::is_scalar_v<T>
    constexpr Matrix<dim, T>& Matrix<dim, T>::operator-=(const Matrix<dim, T>& mat)
    {
        for (int i = 0; i < dim; ++i)
        {
            columns[i] -= mat.columns[i];
        }

        return *this;
    }

    template<unsigned dim, typename T> requires std::is_scalar_v<T>
    constexpr Matrix<dim, T>& Matrix<dim, T>::operator*=(T scalar)
    {
        for (int i = 0; i < dim; ++i)
        {
            columns[i] *= scalar;
        }

        return *this;
    }

    template<unsigned dim, typename T> requires std::is_scalar_v<T>
    constexpr Matrix<dim, T>& Matrix<dim, T>::operator*=(const Matrix<dim, T>& mat)
    {
        return (*this = *this * mat);
    }

    template<unsigned dim, typename T> requires std::is_scalar_v<T>
    constexpr Matrix<dim, T>& Matrix<dim, T>::operator/=(T scalar)
    {
        for (int i = 0; i < dim; ++i)
        {
            columns[i] /= scalar;
        }

        return *this;
    }

    template<unsigned int dim, typename T> requires std::is_scalar_v<T>
    bool Matrix<dim, T>::operator==(const Matrix <dim, T>& rhs) const
    {
        for (int i = 0; i < dim; ++i)
        {
            if(columns[i] != rhs.columns[i])
                return false;
        }

        return true;
    }

    template<unsigned int dim, typename T> requires std::is_scalar_v<T>
    bool Matrix<dim, T>::operator!=(const Matrix <dim, T>& rhs) const
    {
        return !(*this == rhs);
    }

    template<unsigned int dim, typename T> requires std::is_scalar_v<T>
    constexpr Matrix <dim, T> Matrix<dim, T>::operator-()
    {
        Matrix<dim, T> result {};

        for (int i = 0; i < dim; ++i)
        {
            for (int j = 0; j < dim; ++j)
            {
                result[i][j] = -columns[i][j];
            }
        }

        return result;
    }

    template<unsigned int dim, typename T> requires std::is_scalar_v<T>
    auto Matrix<dim, T>::begin()
    {
        return columns.begin();
    }

    template<unsigned int dim, typename T> requires std::is_scalar_v<T>
    const auto Matrix<dim, T>::begin() const
    {
        return columns.begin();
    }

    template<unsigned int dim, typename T> requires std::is_scalar_v<T>
    auto Matrix<dim, T>::end()
    {
        return columns.end();
    }

    template<unsigned int dim, typename T> requires std::is_scalar_v<T>
    const auto Matrix<dim, T>::end() const
    {
        return columns.end();
    }

    template<unsigned dim, typename T>
    constexpr Vector<dim, T> operator*(const Matrix<dim, T>& mat, const Vector<dim, T>& vec)
    {
        Vector<dim, T> result {};

        for (int i = 0; i < dim; ++i)
        {
            for (int j = 0; j < dim; ++j)
            {
                result[i] += mat[j][i] * result[j];
            }
        }

        return result;
    }

    template<unsigned dim, typename T>
    const T* value_ptr(const Matrix<dim, T>& mat)
    {
        return &(mat[0][0]);
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
        std::string formatStr = "\n\t[" + std::to_string(mat[0][0]);

        for (int j = 1; j < dim; ++j)
        {
            formatStr += " " + std::to_string(mat[j][0]);
        }

        formatStr += "]";

        for (int i = 1; i < dim; ++i)
        {
            formatStr += "\n\t[" + std::to_string(mat[0][i]);

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
    out << "\n\t[" << mat[0][0];

    for (int j = 1; j < dim; ++j)
    {
        out << " " << mat[j][0];
    }

    out << "]";

    for (int i = 1; i < dim; ++i)
    {
        out << "\n\t[" << mat[0][i];

        for (int j = 1; j < dim; ++j)
        {
            out << " " << mat[j][i];
        }

        out << "]";
    }

    return out;
}
