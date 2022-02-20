
#pragma once

#include "../Vector/Vector.hpp"

#undef far
#undef near

namespace Sirius
{
    /////////////////////////////////////////////
    /// @brief Any-dimensional matrix class
    /// 
    /// @tparam dim Dimension of the matrix
    /// @tparam T Type of the matrix coefficients
    template<unsigned dim, typename T = float>
    requires std::is_scalar_v<T>
    class Matrix
    {
        private:

            std::array<Vector<dim, T>, dim> columns {};

        public:

            Matrix() = default;

            //////////////////////////////////////////
            /// @brief Construct a matrix with all its
            ///     coefficients set to `val`
            template<std::convertible_to<T> Ts>
            explicit constexpr Matrix(Ts val);

            //////////////////////////////////////
            /// @brief Construct a matrix with the
            ///     provided column vectors 
            template<typename... Cs>
            explicit constexpr Matrix(const Vector<dim, Cs>&... cs);

            ///////////////////////////////////////////////
            /// @brief Construct a matrix with the provided
            ///     scalars as its coefficients
            template<std::convertible_to<T>... Ts>
            constexpr explicit Matrix(Ts... vals);

            constexpr Matrix(const Matrix& mat) = default;

            /////////////////////////////////////////////////////////////
            /// @brief Construct a matrix from a smaller matrix
            ///
            /// The coefficients of the result matrix between 0 and dim2 
            /// are set to the corresponding ones of the argument matrix; 
            /// those between dim2 and dim are set to 0.
            template<unsigned dim2> requires (dim2 < dim)
            constexpr Matrix(const Matrix<dim2, T>& mat);
            
            ///////////////////////////////////////////////////
            /// @brief Construct a matrix from a smaller matrix
            ///
            /// The result matrix takes the coefficients from 0
            /// to dim of the argument matrix, and the rest are 
            /// ignored.
            template<unsigned dim2> requires (dim2 > dim)
            constexpr Matrix(const Matrix<dim2, T>& mat);

            constexpr Matrix(Matrix&& mat) noexcept = default;
            constexpr Matrix<dim, T>& operator=(const Matrix<dim, T>& mat) = default;

            //////////////////////////////////////////////////////////
            /// @brief Assignment operator for different-type matrices
            ///
            /// The coefficients of the right-hand side matrix are
            /// statically casted to the type of the left-hand side
            /// matrix.
            template<std::convertible_to<T> U>
            constexpr Matrix<dim, T>& operator=(const Matrix<dim, U>& mat);

            //////////////////////////////////////////////////
            /// @brief Get the column vector at index `column`
            Vector<dim, T>& operator[](unsigned int column);

            //////////////////////////////////////////////////
            /// @brief Get the column vector at index `column`
            const Vector<dim, T>& operator[](unsigned int column) const;

            ///////////////////////////
            /// @brief Unary matrix sum
            constexpr Matrix<dim, T>& operator+=(const Matrix<dim, T>& mat);

            //////////////////////////////////
            /// @brief Unary matrix difference
            constexpr Matrix<dim, T>& operator-=(const Matrix<dim, T>& mat);

            //////////////////////////////////////
            /// @brief Unary matrix scalar product
            template<std::convertible_to<T> Ts>
            constexpr Matrix<dim, T>& operator*=(Ts scalar);

            ///////////////////////////////////////
            /// @brief Unary matrix scalar division
            template<std::convertible_to<T> Ts>
            constexpr Matrix<dim, T>& operator/=(Ts scalar);

            ///////////////////////////////
            /// @brief Unary matrix product 
            constexpr Matrix<dim, T>& operator*=(const Matrix<dim, T>& mat);

            //////////////////////////
            /// @brief Matrix opposite
            constexpr Matrix<dim, T> operator-();

            ///////////////////////////////////
            /// @brief Matrix equality operator
            bool operator==(const Matrix<dim, T>& rhs) const;

            /////////////////////////////////////
            /// @brief Matrix difference operator
            bool operator!=(const Matrix<dim, T>& rhs) const;

            auto begin();
            const auto begin() const;
            auto end();
            const auto end() const;
    };

    ///////////////////////////////////////
    /// @brief Matrix-vector multiplication
    template<unsigned dim, typename T> constexpr Vector<dim, T> operator*(const Matrix<dim, T>& mat, const Vector<dim, T>& vec);
}

#include "Matrix.tpp"

#include "Matrix2.hpp"
#include "Matrix3.hpp"
#include "Matrix4.hpp"
