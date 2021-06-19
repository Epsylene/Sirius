
#pragma once

#include "Sirius/Math/Vector/Vector3.h"

namespace Sirius
{
    template<unsigned dim, typename T> struct Matrix;

    template<typename T>
    class Matrix<4, T>
    {
        private:

            std::array<Vector<4, T>, 4> columns {};

        public:

            constexpr Matrix() = default;
            constexpr Matrix(const Vector<4, T>& c1, const Vector<4, T>& c2, const Vector<4, T>& c3, const Vector<4, T>& c4);
            constexpr Matrix(T a00, T a01, T a02, T a03, T a10, T a11, T a12, T a13, T a20, T a21, T a22, T a23, T a30, T a31, T a32, T a33);
            constexpr Matrix(const Matrix& mat) = default;
            constexpr Matrix(Matrix&& mat) noexcept = default;

            constexpr Matrix<4, T>& operator=(const Matrix<4, T>& mat) = default;
            template<typename U> constexpr Matrix<4, T>& operator=(const Matrix<4, U>& mat);

            Vector<4, T>& operator[](unsigned column);
            const Vector<4, T>& operator[](unsigned column) const;

            constexpr Matrix<4, T>& operator+=(const Matrix<4, T>& mat);
            constexpr Matrix<4, T>& operator-=(const Matrix<4, T>& mat);
            constexpr Matrix<4, T>& operator*=(T scalar);
            constexpr Matrix<4, T>& operator*=(const Matrix<4, T>& mat);
            constexpr Matrix<4, T>& operator/=(T scalar);
    };

    template<typename T> constexpr Matrix<4, T> operator+(const Matrix<4, T>& mat1, const Matrix<4, T>& mat2);
    template<typename T> constexpr Matrix<4, T> operator-(const Matrix<4, T>& mat1, const Matrix<4, T>& mat2);
    template<typename T> constexpr Matrix<4, T> operator*(const Matrix<4, T>& mat, T scalar);
    template<typename T> constexpr Vector<4, T> operator*(const Matrix<4, T>& mat, const Vector<4, T>& vec);
    template<typename T> constexpr Matrix<4, T> operator*(const Matrix<4, T>& mat1, const Matrix<4, T>& mat2);

    using Matrix4i = Matrix<4, int>;
    using Matrix4f = Matrix<4, float>;
    using Matrix4d = Matrix<4, double>;
}

#include "Matrix4.tpp"
