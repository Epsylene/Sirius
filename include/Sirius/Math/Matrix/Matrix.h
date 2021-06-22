
#pragma once

#include "Sirius/Math/Vector/Vector.h"

namespace Sirius
{
    template<unsigned dim, typename T>
    class Matrix
    {
        private:

            std::array<Vector<dim, T>, dim> columns;

        public:

            Matrix() = default;

            template<typename T1, typename... Ts> requires std::is_convertible_v<T1, Vector<dim, T>>
            explicit constexpr Matrix(const T1& c1, const Ts&... cs);

            template<typename T1, typename... Ts> requires std::is_convertible_v<T1, T>
            constexpr explicit Matrix(T1 val, Ts... vals);

            constexpr Matrix(const Matrix& mat) = default;
            constexpr Matrix(Matrix&& mat) noexcept = default;

            constexpr Matrix<dim, T>& operator=(const Matrix<dim, T>& mat) = default;
            template<typename U> constexpr Matrix<dim, T>& operator=(const Matrix<dim, U>& mat);

            Vector<dim, T>& operator[](unsigned int column);
            const Vector<dim, T>& operator[](unsigned int column) const;

            constexpr Matrix<dim, T>& operator+=(const Matrix<dim, T>& mat);
            constexpr Matrix<dim, T>& operator-=(const Matrix<dim, T>& mat);
            constexpr Matrix<dim, T>& operator*=(T scalar);
            constexpr Matrix<dim, T>& operator*=(const Matrix<dim, T>& mat);
            constexpr Matrix<dim, T>& operator/=(T scalar);

            bool operator==(const Matrix<dim, T>& rhs) const;
            bool operator!=(const Matrix<dim, T>& rhs) const;
    };
}

#include "Matrix.tpp"

//#include "Matrix2.h"
//#include "Matrix3.h"
//#include "Matrix4.h"
