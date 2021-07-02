
#pragma once

namespace Sirius
{
    /////////////////////////////////////////////////
    /// @brief Any-dimensional vector class
    /// 
    /// @tparam dim The vector dimension
    /// @tparam T The type of the vector coefficients
    template<unsigned dim, typename T>
    requires std::is_scalar_v<T>
    class Vector
    {
        private:

            std::array<T, dim> vals {};

        public:

            constexpr Vector() = default;

            //////////////////////////////////////////
            /// @brief Construct a vector with all its 
            ///     coefficients set to `scalar`
            constexpr explicit Vector(T scalar);

            /////////////////////////////////////////
            /// @brief Construct a vector from the 
            ///     provided scalar coefficients
            template<typename... Ts> requires std::is_scalar_v<T>
            explicit constexpr Vector(Ts... xs);

            constexpr Vector(const Vector& vec) = default;
            constexpr Vector(Vector&& vec) noexcept = default;

            constexpr Vector<dim, T>& operator=(const Vector<dim, T>& vec) = default;
            
            /////////////////////////////////////////////////////////
            /// @brief Assignment operator for different-type vectors
            ///
            /// The coefficients of the right-hand side vector are 
            /// statically casted to the type of the left-hand side 
            /// vector.
            template<typename U> requires std::is_convertible_v<U, T>
            constexpr Vector<dim, T>& operator=(const Vector<dim, U>& vec);

            ///////////////////////////////////////////////
            /// @brief Get the coefficient at index `index`
            constexpr T& operator[](unsigned index);

            ///////////////////////////////////////////////
            /// @brief Get the coefficient at index `index`
            constexpr const T& operator[](unsigned index) const;

            ///////////////////////////
            /// @brief Unary vector sum
            constexpr Vector<dim, T>& operator+=(const Vector<dim, T>& vec);

            //////////////////////////////////
            /// @brief Unary vector difference
            constexpr Vector<dim, T>& operator-=(const Vector<dim, T>& vec);

            //////////////////////////////////////
            /// @brief Unary vector scalar product
            constexpr Vector<dim, T>& operator*=(T scalar);

            ///////////////////////////////////////
            /// @brief Unary vector scalar division
            constexpr Vector<dim, T>& operator/=(T scalar);

            /////////////////////////////////////////////////////
            /// @brief Unary vector coefficient-wise product
            ///
            /// This is only provided for the sake of convenience,
            /// in dot product functions and the like.
            constexpr Vector<dim, T>& operator*=(const Vector<dim, T>& vec);

            //////////////////////////
            /// @brief Opposite vector
            constexpr Vector<dim, T>& operator-();

            ///////////////////////////////////
            /// @brief Vector equality operator
            bool operator==(const Vector<dim, T>& rhs) const;

            /////////////////////////////////////
            /// @brief Vector difference operator
            bool operator!=(const Vector<dim, T>& rhs) const;
    };

    /////////////////////////////
    /// @brief Binary vectors sum
    template<unsigned dim, typename T> constexpr Vector<dim, T> operator+(const Vector<dim, T>& v1, const Vector<dim, T>& v2);
    
    ////////////////////////////////////
    /// @brief Binary vectors difference
    template<unsigned dim, typename T> constexpr Vector<dim, T> operator-(const Vector<dim, T>& v1, const Vector<dim, T>& v2);
    
    ///////////////////////////////////////
    /// @brief Binary vector scalar product
    template<unsigned dim, typename T> constexpr Vector<dim, T> operator*(const Vector<dim, T>& vec, T scalar);
    
    ////////////////////////////////////////
    /// @brief Binary vector scalar division
    template<unsigned dim, typename T> constexpr Vector<dim, T> operator/(const Vector<dim, T>& vec, T scalar);

    /////////////////////////////////////////////////
    /// @brief Binary vector coefficient-wise product
    ///
    /// This is only provided for the sake of convenience,
    /// in dot product functions and the like.
    template<unsigned dim, typename T> constexpr Vector<dim, T> operator*(const Vector<dim, T>& v1, const Vector<dim, T>& v2);

    /////////////////////////////////////////////
    /// @brief Vector coefficients values pointer
    template<unsigned dim, typename T> const T* value_ptr(const Vector<dim, T>& vec);
}

#include "Vector.tpp"

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
