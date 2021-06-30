
#pragma once

namespace Sirius
{
    /////////////////////////////////////////////////
    /// @brief 4-dimensional vector class
    /// 
    /// @tparam T The type of the vector coefficients
    template<typename T> requires std::is_scalar_v<T>
    struct Vector4
    {
        T x, y, z, w;

        constexpr Vector4() = default;

        //////////////////////////////////////////
        /// @brief Construct a vector with all its 
        ///     coefficients set to `scalar`
        constexpr explicit Vector4(T scalar);

        /////////////////////////////////////////
        /// @brief Construct a vector from the 
        ///     provided scalar coefficients
        constexpr Vector4(T x, T y, T z, T w);

        constexpr Vector4(const Vector4& vec) = default;
        constexpr Vector4(Vector4&& vec) noexcept = default;

        constexpr Vector4<T>& operator=(const Vector4<T>& vec) = default;

        /////////////////////////////////////////////////////////
        /// @brief Assignment operator for different-type vectors
        ///
        /// The coefficients of the right-hand side vector are 
        /// statically casted to the type of the left-hand side 
        /// vector.
        template<typename U> constexpr Vector4<T>& operator=(const Vector4<U>& vec);

        ///////////////////////////////////////////////
        /// @brief Get the coefficient at index `index`
        T operator[](unsigned index);

        ///////////////////////////////////////////////
        /// @brief Get the coefficient at index `index`
        const T operator[](unsigned index) const;


        ///////////////////////////
        /// @brief Unary vector sum
        constexpr Vector4<T>& operator+=(const Vector4<T>& vec);

        //////////////////////////////////
        /// @brief Unary vector difference
        constexpr Vector4<T>& operator-=(const Vector4<T>& vec);

        //////////////////////////////////////
        /// @brief Unary vector scalar product
        constexpr Vector4<T>& operator*=(T scalar);

        ///////////////////////////////////////
        /// @brief Unary vector scalar division
        constexpr Vector4<T>& operator/=(T scalar);

        /////////////////////////////////////////////////////
        /// @brief Unary vector coefficient-wise product
        ///
        /// This is only provided for the sake of convenience,
        /// in dot product functions and the like.
        constexpr Vector4<T>& operator*=(const Vector4<T>& vec);

        //////////////////////////
        /// @brief Opposite vector
        constexpr Vector4<T> operator-();


        ///////////////////////////////////
        /// @brief Vector equality operator
        bool operator==(const Vector4<T>& rhs) const;

        /////////////////////////////////////
        /// @brief Vector difference operator
        bool operator!=(const Vector4<T>& rhs) const;

        constexpr operator Vector<4, T>() const;
    };


    /////////////////////////////
    /// @brief Binary vectors sum
    template<typename T> constexpr Vector4<T> operator+(const Vector4<T>& v1, const Vector4<T>& v2);
    
    ////////////////////////////////////
    /// @brief Binary vectors difference
    template<typename T> constexpr Vector4<T> operator-(const Vector4<T>& v1, const Vector4<T>& v2);
    
    ///////////////////////////////////////
    /// @brief Binary vector scalar product
    template<typename T> constexpr Vector4<T> operator*(const Vector4<T>& vec, T scalar);
    
    ////////////////////////////////////////
    /// @brief Binary vector scalar division
    template<typename T> constexpr Vector4<T> operator/(const Vector4<T>& vec, T scalar);

    /////////////////////////////////////////////////
    /// @brief Binary vector coefficient-wise product
    ///
    /// This is only provided for the sake of convenience,
    /// in dot product functions and the like.
    template<typename T> constexpr Vector4<T> operator*(const Vector4<T>& v1, const Vector4<T>& v2);
    template<typename T> constexpr Vector4<T> operator*(const Vector<4, T>& v1, const Vector4<T>& v2);

    using Vector4i = Vector4<int>;
    using Vector4f = Vector4<float>;
    using Vector4d = Vector4<double>;

    using Vec4 = Vector4f;
}

#include "Vector4.tpp"
