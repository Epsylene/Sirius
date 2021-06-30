
#pragma once

namespace Sirius
{
    /////////////////////////////////////////////////
    /// @brief 3-dimensional vector class
    /// 
    /// @tparam T The type of the vector coefficients
    template<typename T> requires std::is_scalar_v<T>
    struct Vector3
    {
        T x, y, z;

        constexpr Vector3() = default;

        //////////////////////////////////////////
        /// @brief Construct a vector with all its 
        ///     coefficients set to `scalar`
        constexpr explicit Vector3(T scalar);

        /////////////////////////////////////////
        /// @brief Construct a vector from the 
        ///     provided scalar coefficients
        constexpr Vector3(T x, T y, T z);

        constexpr Vector3(const Vector3& vec) = default;
        constexpr Vector3(Vector3&& vec) noexcept = default;

        constexpr Vector3<T>& operator=(const Vector3<T>& vec) = default;

        /////////////////////////////////////////////////////////
        /// @brief Assignment operator for different-type vectors
        ///
        /// The coefficients of the right-hand side vector are 
        /// statically casted to the type of the left-hand side 
        /// vector.
        template<typename U> constexpr Vector3<T>& operator=(const Vector3<U>& vec);

        ///////////////////////////////////////////////
        /// @brief Get the coefficient at index `index`
        T operator[](unsigned index);

        ///////////////////////////////////////////////
        /// @brief Get the coefficient at index `index`
        const T operator[](unsigned index) const;

        ///////////////////////////
        /// @brief Unary vector sum
        constexpr Vector3<T>& operator+=(const Vector3<T>& vec);

        //////////////////////////////////
        /// @brief Unary vector difference
        constexpr Vector3<T>& operator-=(const Vector3<T>& vec);

        //////////////////////////////////////
        /// @brief Unary vector scalar product
        constexpr Vector3<T>& operator*=(T scalar);

        ///////////////////////////////////////
        /// @brief Unary vector scalar division
        constexpr Vector3<T>& operator/=(T scalar);

        /////////////////////////////////////////////////////
        /// @brief Unary vector coefficient-wise product
        ///
        /// This is only provided for the sake of convenience,
        /// in dot product functions and the like.
        constexpr Vector3<T>& operator*=(const Vector3<T>& vec);

        //////////////////////////
        /// @brief Opposite vector
        constexpr Vector3<T> operator-();

        ///////////////////////////////////
        /// @brief Vector equality operator
        bool operator==(const Vector3<T>& rhs) const;

        /////////////////////////////////////
        /// @brief Vector difference operator
        bool operator!=(const Vector3<T>& rhs) const;

        constexpr operator Vector<3, T>() const;
    };

    template<typename T> constexpr Vector3<T> operator+(const Vector3<T>& v1, const Vector3<T>& v2);
    template<typename T> constexpr Vector3<T> operator-(const Vector3<T>& v1, const Vector3<T>& v2);
    template<typename T> constexpr Vector3<T> operator*(const Vector3<T>& vec, T scalar);
    template<typename T> constexpr Vector3<T> operator*(const Vector3<T>& v1, const Vector3<T>& v2);
    template<typename T> constexpr Vector3<T> operator/(const Vector3<T>& vec, T scalar);

    using Vector3i = Vector3<int>;
    using Vector3f = Vector3<float>;
    using Vector3d = Vector3<double>;

    using Vec3 = Vector3f;
}

#include "Vector3.tpp"
