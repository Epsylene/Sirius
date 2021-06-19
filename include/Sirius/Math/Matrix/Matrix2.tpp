
#include "Matrix2.h"

namespace Sirius
{
    template<typename T>
    constexpr Matrix<2, T>::Matrix(const Vector<2, T>& c1, const Vector<2, T>& c2)
    {
        columns[0] = c1;
        columns[1] = c2;
    }

    template<typename T>
    constexpr Matrix<2, T>::Matrix(T a00, T a01, T a10, T a11)
    {
        columns[0] = {a00, a10};
        columns[1] = {a01, a11};
    }

    template<typename T>
    constexpr Matrix<2, T>& Matrix<2, T>::operator+=(const Matrix<2, T>& mat)
    {
        columns[0] += mat[0];
        columns[1] += mat[1];

        return *this;
    }

    template<typename T>
    constexpr Matrix<2, T>& Matrix<2, T>::operator-=(const Matrix<2, T>& mat)
    {
        columns[0] -= mat[0];
        columns[1] -= mat[1];

        return *this;
    }

    template<typename T>
    Vector<2, T>& Matrix<2, T>::operator[](unsigned int column)
    {
        return columns[column];
    }

    template<typename T>
    const Vector<2, T>& Matrix<2, T>::operator[](unsigned int column) const
    {
        return columns[column];
    }

    template<typename T>
    constexpr Matrix<2, T>& Matrix<2, T>::operator*=(T scalar)
    {
        columns[0] *= scalar;
        columns[1] *= scalar;

        return *this;
    }

    template<typename T>
    constexpr Matrix<2, T>& Matrix<2, T>::operator*=(const Matrix<2, T>& mat)
    {
        return (*this = *this * mat);
    }

    template<typename T>
    constexpr Matrix<2, T>& Matrix<2, T>::operator/=(T scalar)
    {
        columns[0] /= scalar;
        columns[1] /= scalar;

        return *this;
    }

    template<typename T>
    constexpr Matrix<2, T> operator+(const Matrix<2, T>& mat1, const Matrix<2, T>& mat2)
    {
        return Matrix<2, T>(mat1[0] + mat2[0], mat1[1] + mat2[1]);
    }

    template<typename T>
    constexpr Matrix<2, T> operator-(const Matrix<2, T>& mat1, const Matrix<2, T>& mat2)
    {
        return Matrix<2, T>(mat1[0] - mat2[0], mat1[1] - mat2[1]);
    }

    template<typename T>
    constexpr Matrix<2, T> operator*(const Matrix<2, T>& mat, T scalar)
    {
        return Matrix<2, T>(mat[0] * scalar, mat[1] * scalar);
    }

    template<typename T>
    constexpr Vector<2, T> operator*(const Matrix<2, T>& mat, const Vector<2, T>& vec)
    {
        return Vector<2, T>(mat[0][0] * vec.x + mat[1][0] * vec.y,
                            mat[0][1] * vec.x + mat[1][1] * vec.y);
    }

    template<typename T>
    constexpr Matrix<2, T> operator*(const Matrix<2, T>& mat1, const Matrix<2, T>& mat2)
    {
        return Matrix<2, T>(
                mat1[0][0] * mat2[0][0] + mat1[1][0] * mat2[0][1],
                mat1[0][1] * mat2[0][0] + mat1[1][1] * mat2[0][1],
                mat1[0][0] * mat2[1][0] + mat1[1][0] * mat2[1][1],
                mat1[0][1] * mat2[1][0] + mat1[1][1] * mat2[1][1]);
    }
}

template <typename T>
struct fmt::formatter<Sirius::Matrix<2, T>>
{
    constexpr auto parse(format_parse_context& ctx)
    {
        return ctx.end();
    }

    template <typename Context>
    auto format(const Sirius::Matrix<2, T>& mat, Context& ctx)
    {
        return format_to(ctx.out(), "\n\t[{} {}]\n\t[{} {}]", mat[0][0], mat[1][0], mat[0][1], mat[1][1]);
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const Sirius::Matrix<2, T>& mat)
{
    return out << "[" << mat[0][0] << " " << mat[1][0]
        << "]\n[" << mat[0][1] << " " << mat[1][1] << "]";
}
