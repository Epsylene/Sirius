
#pragma once

namespace Sirius
{
    /////////////////////////////////////////////////
    /// @brief Any-dimensional vector class
    /// 
    /// @tparam dim The vector dimension
    /// @tparam T The type of the vector coefficients
    template<unsigned dim, typename T = float>
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
            template<std::convertible_to<T> Ts>
            constexpr explicit Vector(Ts scalar);

            /////////////////////////////////////////
            /// @brief Construct a vector from the 
            ///     provided scalar coefficients
            template<std::convertible_to<T>... Ts>
            explicit constexpr Vector(Ts... xs);

            template<unsigned dim2, std::convertible_to<T>... Ts> requires (dim2 < dim)
            constexpr Vector(const Vector<dim2, T>& vec, Ts... scalars);

            template<unsigned dim2> requires (dim2 > dim)
            constexpr Vector(const Vector<dim2, T>& vec);

            template<unsigned dim2> requires (dim2 < dim)
            constexpr Vector(const Vector<dim2, T>& vec);

            constexpr Vector(const Vector& vec) = default;
            constexpr Vector(Vector&& vec) noexcept = default;

            constexpr Vector<dim, T>& operator=(const Vector<dim, T>& vec) = default;
            
            /////////////////////////////////////////////////////////
            /// @brief Assignment operator for different-type vectors
            ///
            /// The coefficients of the right-hand side vector are 
            /// statically casted to the type of the left-hand side 
            /// vector.
            template<std::convertible_to<T> U>
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
            template<std::convertible_to<T> Ts>
            constexpr Vector<dim, T>& operator*=(Ts scalar);

            ///////////////////////////////////////
            /// @brief Unary vector scalar division
            template<std::convertible_to<T> Ts>
            constexpr Vector<dim, T>& operator/=(Ts scalar);

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
    template<unsigned dim, typename T, std::convertible_to<T> Ts>
    constexpr Vector<dim, T> operator*(const Vector<dim, T>& vec, Ts scalar);
    
    ////////////////////////////////////////
    /// @brief Binary vector scalar division
    template<unsigned dim, typename T, std::convertible_to<T> Ts>
    constexpr Vector<dim, T> operator/(const Vector<dim, T>& vec, Ts scalar);

    //////////////////////////////////////////////////////
    /// @brief Binary vector coefficient-wise product
    ///
    /// This is only provided for the sake of convenience,
    /// in dot product functions and the like.
    template<unsigned dim, typename T> constexpr Vector<dim, T> operator*(const Vector<dim, T>& v1, const Vector<dim, T>& v2);
}

#include "Vector.tpp"

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
