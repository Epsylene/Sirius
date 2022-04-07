
#pragma once

#include "Vector.hpp"

namespace Sirius
{
    /////////////////////////////////////////////////
    /// @brief 4-dimensional vector class
    /// 
    /// @tparam T The type of the vector coefficients
    template<typename T> requires std::is_scalar_v<T>
    struct Vector<4, T>
    {
        union
        {
            std::array<T, 4> m;
            struct { T x, y, z, w; };
        };

        constexpr Vector() = default;

        //////////////////////////////////////////
        /// @brief Construct a vector with all its 
        ///     coefficients set to `scalar`
        template<std::convertible_to<T> Ts>
        constexpr explicit Vector(Ts scalar);

        /////////////////////////////////////////
        /// @brief Construct a vector from the 
        ///     provided scalar coefficients
        template<std::convertible_to<T> Ts>
        constexpr Vector(Ts x, Ts y, Ts z, Ts w);

        //////////////////////////////////////////
        /// @brief Construct a 4d vector from a 2d
        ///     vector and two scalars
        template<std::convertible_to<T> Ts>
        constexpr Vector(const Vector<2, T>& vec, Ts z = 0, Ts w = 0);

        //////////////////////////////////////////
        /// @brief Construct a 4d vector from a 3d
        ///     vector and a scalar
        template<std::convertible_to<T> Ts>
        constexpr Vector(const Vector<3, T>& vec, Ts w = 0);

        constexpr Vector(const Vector& vec) = default;

        ///////////////////////////////////////////////////////
        /// @brief Fill a 4d vector with the values of a 2d one
        constexpr Vector(const Vector<2, T>& vec);

        ///////////////////////////////////////////////////////
        /// @brief Fill a 4d vector with the values of a 3d one
        constexpr Vector(const Vector<3, T>& vec);

        constexpr Vector(Vector&& vec) noexcept = default;

        constexpr Vector<4, T>& operator=(const Vector<4, T>& vec) = default;

        /////////////////////////////////////////////////////////
        /// @brief Assignment operator for different-type vectors
        ///
        /// The coefficients of the right-hand side vector are 
        /// statically casted to the type of the left-hand side 
        /// vector.
        template<std::convertible_to<T> U>
        constexpr Vector<4, T>& operator=(const Vector<4, U>& vec);

        ///////////////////////////////////////////////
        /// @brief Get the coefficient at index `index`
        constexpr T& operator[](unsigned index);

        ///////////////////////////////////////////////
        /// @brief Get the coefficient at index `index`
        constexpr const T& operator[](unsigned index) const;

        ///////////////////////////
        /// @brief Unary vector sum
        constexpr Vector<4, T>& operator+=(const Vector<4, T>& vec);

        //////////////////////////////////
        /// @brief Unary vector difference
        constexpr Vector<4, T>& operator-=(const Vector<4, T>& vec);

        //////////////////////////////////////
        /// @brief Unary vector scalar product
        template<std::convertible_to<T> Ts>
        constexpr Vector<4, T>& operator*=(Ts scalar);

        ///////////////////////////////////////
        /// @brief Unary vector scalar division
        template<std::convertible_to<T> Ts>
        constexpr Vector<4, T>& operator/=(Ts scalar);

        /////////////////////////////////////////////////////
        /// @brief Unary vector coefficient-wise product
        ///
        /// This is only provided for the sake of convenience,
        /// in dot product functions and the like.
        constexpr Vector<4, T>& operator*=(const Vector<4, T>& vec);

        //////////////////////////
        /// @brief Opposite vector
        constexpr Vector<4, T> operator-();

        ///////////////////////////////////
        /// @brief Vector equality operator
        bool operator==(const Vector<4, T>& rhs) const;

        /////////////////////////////////////
        /// @brief Vector difference operator
        bool operator!=(const Vector<4, T>& rhs) const;
    };

    using Vector4i = Vector<4, int>;
    using Vector4f = Vector<4, float>;
    using Vector4d = Vector<4, double>;

    using Vec4 = Vector4f;
}

#include "Vector4.tpp"
