
#pragma once

namespace Sirius
{
    /////////////////////////////////////
    /// @brief 2-dimensional vector class
    /// 
    /// @tparam T The type of the vector coefficients
    template<typename T> requires std::is_scalar_v<T>
    struct Vector2
    {
        T x, y;

        constexpr Vector2() = default;

        //////////////////////////////////////////
        /// @brief Construct a vector with all its 
        ///     coefficients set to `scalar`
        constexpr explicit Vector2(T scalar);

        //////////////////////////////////////
        /// @brief Construct a vector from the 
        ///     provided scalar coefficients
        constexpr Vector2(T x, T y);

        constexpr Vector2(const Vector2& vec) = default;
        constexpr Vector2(Vector2&& vec) noexcept = default;

        constexpr Vector2<T>& operator=(const Vector2<T>& vec) = default;

        /////////////////////////////////////////////////////////
        /// @brief Assignment operator for different-type vectors
        ///
        /// The coefficients of the right-hand side vector are 
        /// statically casted to the type of the left-hand side 
        /// vector.
        template<typename U> constexpr Vector2<T>& operator=(const Vector2<U>& vec);

        ///////////////////////////////////////////////
        /// @brief Get the coefficient at index `index`
        constexpr T operator[](unsigned index);

        ///////////////////////////////////////////////
        /// @brief Get the coefficient at index `index`
        constexpr T operator[](unsigned index) const;

        ///////////////////////////
        /// @brief Unary vector sum
        constexpr Vector2<T>& operator+=(const Vector2<T>& vec);
        
        //////////////////////////////////
        /// @brief Unary vector difference
        constexpr Vector2<T>& operator-=(const Vector2<T>& vec);
        
        //////////////////////////////////////
        /// @brief Unary vector scalar product
        constexpr Vector2<T>& operator*=(T scalar);
        
        ///////////////////////////////////////
        /// @brief Unary vector scalar division
        constexpr Vector2<T>& operator/=(T scalar);

        /////////////////////////////////////////////////////
        /// @brief Unary vector coefficient-wise product
        ///
        /// This is only provided for the sake of convenience,
        /// in dot product functions and the like.
        constexpr Vector2<T>& operator*=(const Vector2<T>& vec);

        //////////////////////////
        /// @brief Opposite vector
        constexpr Vector2<T> operator-();

        ///////////////////////////////////
        /// @brief Vector equality operator
        bool operator==(const Vector2<T>& rhs) const;
        
        /////////////////////////////////////
        /// @brief Vector difference operator
        bool operator!=(const Vector2<T>& rhs) const;

        constexpr operator Vector<2, T>() const;
    };

    /////////////////////////////
    /// @brief Binary vectors sum
    template<typename T> constexpr Vector2<T> operator+(const Vector2<T>& v1, const Vector2<T>& v2);
    
    ////////////////////////////////////
    /// @brief Binary vectors difference
    template<typename T> constexpr Vector2<T> operator-(const Vector2<T>& v1, const Vector2<T>& v2);
    
    ///////////////////////////////////////
    /// @brief Binary vector scalar product
    template<typename T> constexpr Vector2<T> operator*(const Vector2<T>& vec, T scalar);
    
    ////////////////////////////////////////
    /// @brief Binary vector scalar division
    template<typename T> constexpr Vector2<T> operator/(const Vector2<T>& vec, T scalar);
    
    /////////////////////////////////////////////////
    /// @brief Binary vector coefficient-wise product
    ///
    /// This is only provided for the sake of convenience,
    /// in dot product functions and the like.
    template<typename T> constexpr Vector2<T> operator*(const Vector2<T>& v1, const Vector2<T>& v2);

    using Vector2i = Vector2<int>;
    using Vector2f = Vector2<float>;
    using Vector2d = Vector2<double>;

    using Vec2 = Vector2f;
}

#include "Vector2.tpp"
