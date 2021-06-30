
#include "Matrix2.h"

namespace Sirius
{
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
        return { mat[0] * scalar, mat[1] * scalar };
    }

    template<typename T>
    constexpr Matrix<2, T> operator*(const Matrix<2, T>& mat1, const Matrix<2, T>& mat2)
    {
        return { mat1[0][0] * mat2[0][0] + mat1[1][0] * mat2[0][1],
                 mat1[0][1] * mat2[0][0] + mat1[1][1] * mat2[0][1],
                 mat1[0][0] * mat2[1][0] + mat1[1][0] * mat2[1][1],
                 mat1[0][1] * mat2[1][0] + mat1[1][1] * mat2[1][1] };
    }

    template<typename T>
    constexpr Vector<2, T> operator*(const Matrix<2, T>& mat, const Vector<2, T>& vec)
    {
        return { mat[0][0] * vec.x + mat[1][0] * vec.y,
                          mat[0][1] * vec.x + mat[1][1] * vec.y };
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
