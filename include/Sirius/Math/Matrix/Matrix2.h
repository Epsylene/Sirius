
#pragma once

#include "Sirius/Math/Vector/Vector2.h"

namespace Sirius
{
    template<unsigned dim, typename T> struct Matrix;

    template<typename T>
    class Matrix<2, T>
    {
        private:

            std::array<Vector<2, T>, 2> columns;

        public:

            constexpr Matrix() = default;
            constexpr Matrix(const Vector<2, T>& c1, const Vector<2, T>& c2);
            constexpr Matrix(T a00, T a01, T a10, T a11);
            constexpr Matrix(const Matrix& mat) = default;
            constexpr Matrix(Matrix&& mat) noexcept = default;

            constexpr Matrix<2, T>& operator=(const Matrix<2, T>& mat) = default;
            template<typename U> constexpr Matrix<2, T>& operator=(const Matrix<2, U>& mat);

            Vector<2, T>& operator[](unsigned column);
            const Vector<2, T>& operator[](unsigned column) const;

            constexpr Matrix<2, T>& operator+=(const Matrix<2, T>& mat);
            constexpr Matrix<2, T>& operator-=(const Matrix<2, T>& mat);
            constexpr Matrix<2, T>& operator*=(T scalar);
            constexpr Matrix<2, T>& operator*=(const Matrix<2, T>& mat);
            constexpr Matrix<2, T>& operator/=(T scalar);
    };

    template<typename T> constexpr Matrix<2, T> operator+(const Matrix<2, T>& mat1, const Matrix<2, T>& mat2);
    template<typename T> constexpr Matrix<2, T> operator-(const Matrix<2, T>& mat1, const Matrix<2, T>& mat2);
    template<typename T> constexpr Matrix<2, T> operator*(const Matrix<2, T>& mat, T scalar);
    template<typename T> constexpr Vector<2, T> operator*(const Matrix<2, T>& mat, const Vector<2, T>& vec);
    template<typename T> constexpr Matrix<2, T> operator*(const Matrix<2, T>& mat1, const Matrix<2, T>& mat2);

    using Matrix2i = Matrix<2, int>;
    using Matrix2f = Matrix<2, float>;
    using Matrix2d = Matrix<2, double>;
}

#include "Matrix2.tpp"
