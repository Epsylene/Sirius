
#pragma once

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
        constexpr explicit Vector(T scalar);

        /////////////////////////////////////////
        /// @brief Construct a vector from the 
        ///     provided scalar coefficients
        constexpr Vector(T x, T y, T z);

        constexpr Vector(const Vector& vec) = default;
        constexpr Vector(Vector&& vec) noexcept = default;

        constexpr Vector<3, T>& operator=(const Vector<3, T>& vec) = default;

        /////////////////////////////////////////////////////////
        /// @brief Assignment operator for different-type vectors
        ///
        /// The coefficients of the right-hand side vector are 
        /// statically casted to the type of the left-hand side 
        /// vector.
        template<typename U> requires std::is_convertible_v<U, T>
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
        constexpr Vector<3, T>& operator*=(T scalar);

        ///////////////////////////////////////
        /// @brief Unary vector scalar division
        constexpr Vector<3, T>& operator/=(T scalar);

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
    template<typename T> constexpr Vector<3, T> operator*(const Vector<3, T>& vec, T scalar);

    ////////////////////////////////////////
    /// @brief Binary vector scalar division
    template<typename T> constexpr Vector<3, T> operator/(const Vector<3, T>& vec, T scalar);

    //////////////////////////////////////////////////////
    /// @brief Binary vector coefficient-wise product
    ///
    /// This is only provided for the sake of convenience,
    /// in dot product functions and the like.
    template<typename T> constexpr Vector<3, T> operator*(const Vector<3, T>& v1, const Vector<3, T>& v2);

    /////////////////////////////////////////////
    /// @brief Vector coefficients values pointer
    template<typename T> const T* value_ptr(const Vector<3, T>& vec);

    using Vector3i = Vector<3, int>;
    using Vector3f = Vector<3, float>;
    using Vector3d = Vector<3, double>;

    using Vec3 = Vector3f;
}

#include "Vector3.tpp"
