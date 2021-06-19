
#pragma once

#include "Sirius/Math/Vector/Vector3.h"

namespace Sirius
{
    template<unsigned dim, typename T> struct Matrix;

    template<typename T>
    class Matrix<3, T>
    {
        private:

            std::array<Vector<3, T>, 3> columns {};

        public:

            constexpr Matrix() = default;
            constexpr Matrix(const Vector<3, T>& c1, const Vector<3, T>& c2, const Vector<3, T>& c3);
            constexpr Matrix(T a00, T a01, T a02, T a10, T a11, T a12, T a20, T a21, T a22);
            constexpr Matrix(const Matrix& mat) = default;
            constexpr Matrix(Matrix&& mat) noexcept = default;

            constexpr Matrix<3, T>& operator=(const Matrix<3, T>& mat) = default;
            template<typename U> constexpr Matrix<3, T>& operator=(const Matrix<3, U>& mat);

            Vector<3, T>& operator[](unsigned column);
            const Vector<3, T>& operator[](unsigned column) const;

            constexpr Matrix<3, T>& operator+=(const Matrix<3, T>& mat);
            constexpr Matrix<3, T>& operator-=(const Matrix<3, T>& mat);
            constexpr Matrix<3, T>& operator*=(T scalar);
            constexpr Matrix<3, T>& operator*=(const Matrix<3, T>& mat);
            constexpr Matrix<3, T>& operator/=(T scalar);
    };

    template<typename T> constexpr Matrix<3, T> operator+(const Matrix<3, T>& mat1, const Matrix<3, T>& mat2);
    template<typename T> constexpr Matrix<3, T> operator-(const Matrix<3, T>& mat1, const Matrix<3, T>& mat2);
    template<typename T> constexpr Matrix<3, T> operator*(const Matrix<3, T>& mat, T scalar);
    template<typename T> constexpr Vector<3, T> operator*(const Matrix<3, T>& mat, const Vector<3, T>& vec);
    template<typename T> constexpr Matrix<3, T> operator*(const Matrix<3, T>& mat1, const Matrix<3, T>& mat2);

    using Matrix3i = Matrix<3, int>;
    using Matrix3f = Matrix<3, float>;
    using Matrix3d = Matrix<3, double>;
}

#include "Matrix3.tpp"
