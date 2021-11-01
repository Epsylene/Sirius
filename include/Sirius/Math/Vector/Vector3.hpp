
#pragma once

#include "Vector.hpp"

namespace Sirius
{
    /////////////////////////////////////////////////
    /// @brief 3-dimensional vector class
    /// 
    /// @tparam T The type of the vector coefficients
    template<typename T> requires std::is_scalar_v<T>
    struct Vector<3, T>
    {
        T x, y, z;

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
        constexpr Vector(Ts x, Ts y, Ts z);

        //////////////////////////////////////////
        /// @brief Construct a 3d vector from a 2d
        ///     vector and a scalar
        template<std::convertible_to<T> Ts>
        constexpr Vector(const Vector<2, T>& vec, Ts z);

        constexpr Vector(const Vector& vec) = default;

        ///////////////////////////////////////////////////////
        /// @brief Fill a 3d vector with the values of a 2d one
        constexpr Vector(const Vector<2, T>& vec);

        constexpr Vector(Vector&& vec) noexcept = default;

        constexpr Vector<3, T>& operator=(const Vector<3, T>& vec) = default;

        /////////////////////////////////////////////////////////
        /// @brief Assignment operator for different-type vectors
        ///
        /// The coefficients of the right-hand side vector are 
        /// statically casted to the type of the left-hand side 
        /// vector.
        template<std::convertible_to<T> U>
        constexpr Vector<3, T>& operator=(const Vector<3, U>& vec);

        ///////////////////////////////////////////////
        /// @brief Get the coefficient at index `index`
        constexpr T& operator[](unsigned index);

        ///////////////////////////////////////////////
        /// @brief Get the coefficient at index `index`
        constexpr const T& operator[](unsigned index) const;

        ///////////////////////////
        /// @brief Unary vector sum
        constexpr Vector<3, T>& operator+=(const Vector<3, T>& vec);

        //////////////////////////////////
        /// @brief Unary vector difference
        constexpr Vector<3, T>& operator-=(const Vector<3, T>& vec);

        //////////////////////////////////////
        /// @brief Unary vector scalar product
        template<std::convertible_to<T> Ts>
        constexpr Vector<3, T>& operator*=(Ts scalar);

        ///////////////////////////////////////
        /// @brief Unary vector scalar division
        template<std::convertible_to<T> Ts>
        constexpr Vector<3, T>& operator/=(Ts scalar);

        /////////////////////////////////////////////////////
        /// @brief Unary vector coefficient-wise product
        ///
        /// This is only provided for the sake of convenience,
        /// in dot product functions and the like.
        constexpr Vector<3, T>& operator*=(const Vector<3, T>& vec);

        //////////////////////////
        /// @brief Opposite vector
        constexpr Vector<3, T> operator-();

        ///////////////////////////////////
        /// @brief Vector equality operator
        bool operator==(const Vector<3, T>& rhs) const;

        /////////////////////////////////////
        /// @brief Vector difference operator
        bool operator!=(const Vector<3, T>& rhs) const;
    };

    /////////////////////////////
    /// @brief Binary vectors sum
    template<typename T> constexpr Vector<3, T> operator+(const Vector<3, T>& v1, const Vector<3, T>& v2);

    ////////////////////////////////////
    /// @brief Binary vectors difference
    template<typename T> constexpr Vector<3, T> operator-(const Vector<3, T>& v1, const Vector<3, T>& v2);

    ///////////////////////////////////////
    /// @brief Binary vector scalar product
    template<typename T, std::convertible_to<T> Ts>
    constexpr Vector<3, T> operator*(const Vector<3, T>& vec, Ts scalar);

    ////////////////////////////////////////
    /// @brief Binary vector scalar division
    template<typename T, std::convertible_to<T> Ts>
    constexpr Vector<3, T> operator/(const Vector<3, T>& vec, Ts scalar);

    //////////////////////////////////////////////////////
    /// @brief Binary vector coefficient-wise product
    ///
    /// This is only provided for the sake of convenience,
    /// in dot product functions and the like.
    template<typename T> constexpr Vector<3, T> operator*(const Vector<3, T>& v1, const Vector<3, T>& v2);

    using Vector3i = Vector<3, int>;
    using Vector3f = Vector<3, float>;
    using Vector3d = Vector<3, double>;

    using Vec3 = Vector3f;
}

#include "Vector3.tpp"
