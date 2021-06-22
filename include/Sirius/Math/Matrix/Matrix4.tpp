
#include "Matrix3.h"

namespace Sirius
{
    template<typename T>
    constexpr Matrix<4, T> operator+(const Matrix<4, T>& mat1, const Matrix<4, T>& mat2)
    {
        return Matrix<4, T>(mat1[0] + mat2[0], mat1[1] + mat2[1], mat1[2] + mat2[2], mat1[3] + mat2[3]);
    }

    template<typename T>
    constexpr Matrix<4, T> operator-(const Matrix<4, T>& mat1, const Matrix<4, T>& mat2)
    {
        return Matrix<4, T>(mat1[0] - mat2[0], mat1[1] - mat2[1], mat1[2] - mat2[2], mat1[3] - mat2[3]);
    }

    template<typename T>
    constexpr Matrix<4, T> operator*(const Matrix<4, T>& mat, T scalar)
    {
        return Matrix<4, T>(mat[0] * scalar, mat[1] * scalar, mat[2] * scalar, mat[3] * scalar);
    }

    template<typename T>
    constexpr Vector<4, T> operator*(const Matrix<4, T>& mat, const Vector<4, T>& vec)
    {
        return Vector<4, T>(mat[0][0] * vec.x + mat[1][0] * vec.y + mat[2][0] * vec.z, + mat[3][0] * vec.z,
                            mat[0][1] * vec.x + mat[1][1] * vec.y + mat[2][1] * vec.z, + mat[3][1] * vec.z,
                            mat[0][2] * vec.x + mat[1][2] * vec.y + mat[2][2] * vec.z, + mat[3][2] * vec.z,
                            mat[0][3] * vec.x + mat[1][3] * vec.y + mat[2][3] * vec.z, + mat[3][3] * vec.z);
    }

    template<typename T>
    constexpr Matrix<4, T> operator*(const Matrix<4, T>& mat1, const Matrix<4, T>& mat2)
    {
        const Vector<4, T> a0 = mat1[0], a1 = mat1[1], a2 = mat1[2], a3 = mat1[3];
        const Vector<4, T> b0 = mat2[0], b1 = mat2[1], b2 = mat2[2], b3 = mat2[3];

        return Matrix<4, T> {
            a0 * b0[0] + a1 * b0[1] + a2 * b0[2] + a3 * b0[3],
            a0 * b1[0] + a1 * b1[1] + a2 * b1[2] + a3 * b1[3],
            a0 * b2[0] + a1 * b2[1] + a2 * b2[2] + a3 * b2[3],
            a0 * b3[0] + a1 * b3[1] + a2 * b3[2] + a3 * b3[3] };
    }
}

template <typename T>
struct fmt::formatter<Sirius::Matrix<4, T>>
{
    constexpr auto parse(format_parse_context& ctx)
    {
        return ctx.end();
    }

    template <typename Context>
    auto format(const Sirius::Matrix<4, T>& mat, Context& ctx)
    {
        return format_to(ctx.out(), "\n\t[{} {} {} {}]\n\t[{} {} {} {}]\n\t[{} {} {} {}]\n\t[{} {} {} {}]",
                         mat[0][0], mat[1][0], mat[2][0], mat[3][0],
                         mat[0][1], mat[1][1], mat[2][1], mat[3][1],
                         mat[0][2], mat[1][2], mat[2][2], mat[3][2],
                         mat[0][3], mat[1][3], mat[2][3], mat[3][3]);
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const Sirius::Matrix<4, T>& mat)
{
    return out << "[" << mat[0][0] << " " << mat[1][0] << " " << mat[2][0] << " " << mat[3][0]
               << "]\n[" << mat[0][1] << " " << mat[1][1] << " " << mat[2][1] << " " << mat[3][1]
               << "]\n[" << mat[0][2] << " " << mat[1][2] << " " << mat[2][2] << " " << mat[3][2]
               << "]\n[" << mat[0][3] << " " << mat[1][3] << " " << mat[2][3] << " " << mat[3][3] << "]";
}
