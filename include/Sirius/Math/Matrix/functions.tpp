
#include "functions.h"

namespace Sirius
{
    template<typename T>
    constexpr Matrix<2, T> inverse(const Matrix<2, T>& mat)
    {
        T oneOverDet = static_cast<T>(1) / (mat[0][0] * mat[1][1] 
                                            - mat[1][0] * mat[0][1]);

        return { mat[1][1] * oneOverDet,
               - mat[0][1] * oneOverDet,
               - mat[1][0] * oneOverDet,
                 mat[0][0] * oneOverDet };
    }

    template<typename T>
    constexpr Matrix<3, T> inverse(const Matrix<3, T>& mat)
    {
        T oneOverDet = static_cast<T>(1) / (
                  mat[0][0] * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2])
                - mat[1][0] * (mat[0][1] * mat[2][2] - mat[2][1] * mat[0][2])
                + mat[2][0] * (mat[0][1] * mat[1][2] - mat[1][1] * mat[0][2]));

        Matrix<3, T> inverse;
        inverse[0][0] =  (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2]) * oneOverDet;
        inverse[1][0] = -(mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2]) * oneOverDet;
        inverse[2][0] =  (mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1]) * oneOverDet;
        inverse[0][1] = -(mat[0][1] * mat[2][2] - mat[2][1] * mat[0][2]) * oneOverDet;
        inverse[1][1] =  (mat[0][0] * mat[2][2] - mat[2][0] * mat[0][2]) * oneOverDet;
        inverse[2][1] = -(mat[0][0] * mat[2][1] - mat[2][0] * mat[0][1]) * oneOverDet;
        inverse[0][2] =  (mat[0][1] * mat[1][2] - mat[1][1] * mat[0][2]) * oneOverDet;
        inverse[1][2] = -(mat[0][0] * mat[1][2] - mat[1][0] * mat[0][2]) * oneOverDet;
        inverse[2][2] =  (mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1]) * oneOverDet;

        return inverse;
    }

    template<typename T>
    constexpr Matrix<4, T> inverse(const Matrix<4, T>& mat)
    {
        T coef00 = mat[2][2] * mat[3][3] - mat[3][2] * mat[2][3];
        T coef02 = mat[1][2] * mat[3][3] - mat[3][2] * mat[1][3];
        T coef03 = mat[1][2] * mat[2][3] - mat[2][2] * mat[1][3];

        T coef04 = mat[2][1] * mat[3][3] - mat[3][1] * mat[2][3];
        T coef06 = mat[1][1] * mat[3][3] - mat[3][1] * mat[1][3];
        T coef07 = mat[1][1] * mat[2][3] - mat[2][1] * mat[1][3];

        T coef08 = mat[2][1] * mat[3][2] - mat[3][1] * mat[2][2];
        T coef10 = mat[1][1] * mat[3][2] - mat[3][1] * mat[1][2];
        T coef11 = mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2];

        T coef12 = mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3];
        T coef14 = mat[1][0] * mat[3][3] - mat[3][0] * mat[1][3];
        T coef15 = mat[1][0] * mat[2][3] - mat[2][0] * mat[1][3];

        T coef16 = mat[2][0] * mat[3][2] - mat[3][0] * mat[2][2];
        T coef18 = mat[1][0] * mat[3][2] - mat[3][0] * mat[1][2];
        T coef19 = mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2];

        T coef20 = mat[2][0] * mat[3][1] - mat[3][0] * mat[2][1];
        T coef22 = mat[1][0] * mat[3][1] - mat[3][0] * mat[1][1];
        T coef23 = mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1];

        Vector4<T> fac0(coef00, coef00, coef02, coef03);
        Vector4<T> fac1(coef04, coef04, coef06, coef07);
        Vector4<T> fac2(coef08, coef08, coef10, coef11);
        Vector4<T> fac3(coef12, coef12, coef14, coef15);
        Vector4<T> fac4(coef16, coef16, coef18, coef19);
        Vector4<T> fac5(coef20, coef20, coef22, coef23);

        Vector4<T> vec0(mat[1][0], mat[0][0], mat[0][0], mat[0][0]);
        Vector4<T> vec1(mat[1][1], mat[0][1], mat[0][1], mat[0][1]);
        Vector4<T> vec2(mat[1][2], mat[0][2], mat[0][2], mat[0][2]);
        Vector4<T> vec3(mat[1][3], mat[0][3], mat[0][3], mat[0][3]);

        Vector4<T> inv0(vec1 * fac0 - vec2 * fac1 + vec3 * fac2);
        Vector4<T> inv1(vec0 * fac0 - vec2 * fac3 + vec3 * fac4);
        Vector4<T> inv2(vec0 * fac1 - vec1 * fac3 + vec3 * fac5);
        Vector4<T> inv3(vec0 * fac2 - vec1 * fac4 + vec2 * fac5);

        Vector4<T> signA(1, -1, 1, -1);
        Vector4<T> signB(-1, 1, -1, 1);
        Matrix<4, T> inverse(inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB);

        Vector4<T> row0(inverse[0][0], inverse[1][0], inverse[2][0], inverse[3][0]);

        Vector4<T> dot0(mat[0] * row0);
        T dot1 = (dot0.x + dot0.y) + (dot0.z + dot0.w);

        T oneOverDet = static_cast<T>(1) / dot1;

        return inverse * oneOverDet;
    }
}