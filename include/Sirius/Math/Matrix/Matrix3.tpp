
#include "Matrix3.h"

namespace Sirius
{
    template<typename T>
    constexpr Matrix<3, T>::Matrix(const Vector<3, T>& c1, const Vector<3, T>& c2, const Vector<3, T>& c3)
    {
        columns[0] = c1;
        columns[1] = c2;
        columns[2] = c3;
    }

    template<typename T>
    constexpr Matrix<3, T>::Matrix(T a00, T a01, T a02, T a10, T a11, T a12, T a20, T a21, T a22)
    {
        columns[0] = {a00, a10, a20};
        columns[1] = {a01, a11, a21};
        columns[2] = {a02, a12, a22};
    }

    template<typename T>
    constexpr Matrix<3, T>& Matrix<3, T>::operator+=(const Matrix<3, T>& mat)
    {
        columns[0] += mat[0];
        columns[1] += mat[1];
        columns[2] += mat[2];

        return *this;
    }

    template<typename T>
    constexpr Matrix<3, T>& Matrix<3, T>::operator-=(const Matrix<3, T>& mat)
    {
        columns[0] -= mat[0];
        columns[1] -= mat[1];
        columns[2] -= mat[2];

        return *this;
    }

    template<typename T>
    Vector<3, T>& Matrix<3, T>::operator[](unsigned int column)
    {
        return columns[column];
    }

    template<typename T>
    const Vector<3, T>& Matrix<3, T>::operator[](unsigned int column) const
    {
        return columns[column];
    }

    template<typename T>
    constexpr Matrix<3, T>& Matrix<3, T>::operator*=(T scalar)
    {
        columns[0] *= scalar;
        columns[1] *= scalar;
        columns[2] *= scalar;

        return *this;
    }

    template<typename T>
    constexpr Matrix<3, T>& Matrix<3, T>::operator*=(const Matrix<3, T>& mat)
    {
        return (*this = *this * mat);
    }

    template<typename T>
    constexpr Matrix<3, T>& Matrix<3, T>::operator/=(T scalar)
    {
        columns[0] /= scalar;
        columns[1] /= scalar;
        columns[2] /= scalar;

        return *this;
    }

    template<typename T>
    constexpr Matrix<3, T> operator+(const Matrix<3, T>& mat1, const Matrix<3, T>& mat2)
    {
        return Matrix<3, T>(mat1[0] + mat2[0], mat1[1] + mat2[1], mat1[2] + mat2[2]);
    }

    template<typename T>
    constexpr Matrix<3, T> operator-(const Matrix<3, T>& mat1, const Matrix<3, T>& mat2)
    {
        return Matrix<3, T>(mat1[0] - mat2[0], mat1[1] - mat2[1], mat1[2] - mat2[2]);
    }

    template<typename T>
    constexpr Matrix<3, T> operator*(const Matrix<3, T>& mat, T scalar)
    {
        return Matrix<3, T>(mat[0] * scalar, mat[1] * scalar, mat[2] * scalar);
    }

    template<typename T>
    constexpr Vector<3, T> operator*(const Matrix<3, T>& mat, const Vector<3, T>& vec)
    {
        return Vector<3, T>(mat[0][0] * vec.x + mat[1][0] * vec.y + mat[2][0] * vec.z,
                            mat[0][1] * vec.x + mat[1][1] * vec.y + mat[2][1] * vec.z,
                            mat[0][2] * vec.x + mat[1][2] * vec.y + mat[2][2] * vec.z);
    }

    template<typename T>
    constexpr Matrix<3, T> operator*(const Matrix<3, T>& mat1, const Matrix<3, T>& mat2)
    {
        const T a00 = mat1[0][0], a01 = mat1[0][1], a02 = mat1[0][2];
        const T a10 = mat1[1][0], a11 = mat1[1][1], a12 = mat1[1][2];
        const T a20 = mat1[2][0], a21 = mat1[2][1], a22 = mat1[2][2];

        const T b00 = mat2[0][0], b01 = mat2[0][1], b02 = mat2[0][2];
        const T b10 = mat2[1][0], b11 = mat2[1][1], b12 = mat2[1][2];
        const T b20 = mat2[2][0], b21 = mat2[2][1], b22 = mat2[2][2];
        
        Matrix<3, T> result;
        result[0][0] = a00 * b00 + a10 * b01 + a20 * b02;
        result[0][1] = a01 * b00 + a11 * b01 + a21 * b02;
        result[0][2] = a02 * b00 + a12 * b01 + a22 * b02;
        result[1][0] = a00 * b10 + a10 * b11 + a20 * b12;
        result[1][1] = a01 * b10 + a11 * b11 + a21 * b12;
        result[1][2] = a02 * b10 + a12 * b11 + a22 * b12;
        result[2][0] = a00 * b20 + a10 * b21 + a20 * b22;
        result[2][1] = a01 * b20 + a11 * b21 + a21 * b22;
        result[2][2] = a02 * b20 + a12 * b21 + a22 * b22;

        return result;
    }
}

template <typename T>
struct fmt::formatter<Sirius::Matrix<3, T>>
{
    constexpr auto parse(format_parse_context& ctx)
    {
        return ctx.end();
    }

    template <typename Context>
    auto format(const Sirius::Matrix<3, T>& mat, Context& ctx)
    {
        return format_to(ctx.out(), "\n\t[{} {} {}]\n\t[{} {} {}]\n\t[{} {} {}]",
                         mat[0][0], mat[1][0], mat[2][0],
                         mat[0][1], mat[1][1], mat[2][1],
                         mat[0][2], mat[1][2], mat[2][2]);
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const Sirius::Matrix<3, T>& mat)
{
    return out << "[" << mat[0][0] << " " << mat[1][0] << " " << mat[2][0]
            << "]\n[" << mat[0][1] << " " << mat[1][1] << " " << mat[2][1]
            << "]\n[" << mat[0][2] << " " << mat[1][2] << " " << mat[2][2] << "]";
}
