
#pragma once

#include "Vector.hpp"

#include <variant>

namespace Sirius
{
    /////////////////////////////////////
    /// @brief 2-dimensional vector class
    /// 
    /// @tparam T The type of the vector coefficients
    template<typename T> requires std::is_scalar_v<T>
    struct Vector<2, T>
    {
        public:

        union
        {
            std::array<T, 2> m {};
            struct { float x, y; };
        };

        constexpr Vector() = default;

        //////////////////////////////////////////
        /// @brief Construct a vector with all its 
        ///     coefficients set to `scalar`
        template<std::convertible_to<T> Ts>
        constexpr explicit Vector(Ts scalar);

        //////////////////////////////////////
        /// @brief Construct a vector from the 
        ///     provided scalar coefficients
        template<std::convertible_to<T> Ts>
        constexpr Vector(Ts x, Ts y);

        constexpr Vector(const Vector& vec) = default;
        constexpr Vector(Vector&& vec) noexcept = default;

        constexpr Vector<2, T>& operator=(const Vector<2, T>& vec) = default;

        /////////////////////////////////////////////////////////
        /// @brief Assignment operator for different-type vectors
        ///
        /// The coefficients of the right-hand side vector are 
        /// statically casted to the type of the left-hand side 
        /// vector.
        template<std::convertible_to<T> U>
        constexpr Vector<2, T>& operator=(const Vector<2, U>& vec);

        ///////////////////////////////////////////////
        /// @brief Get the coefficient at index `index`
        constexpr T& operator[](unsigned index);

        ///////////////////////////////////////////////
        /// @brief Get the coefficient at index `index`
        constexpr const T& operator[](unsigned index) const;

        ///////////////////////////
        /// @brief Unary vector sum
        constexpr Vector<2, T>& operator+=(const Vector<2, T>& vec);
        
        //////////////////////////////////
        /// @brief Unary vector difference
        constexpr Vector<2, T>& operator-=(const Vector<2, T>& vec);
        
        //////////////////////////////////////
        /// @brief Unary vector scalar product
        template<std::convertible_to<T> Ts>
        constexpr Vector<2, T>& operator*=(Ts scalar);
        
        ///////////////////////////////////////
        /// @brief Unary vector scalar division
        template<std::convertible_to<T> Ts>
        constexpr Vector<2, T>& operator/=(Ts scalar);

        /////////////////////////////////////////////////////
        /// @brief Unary vector coefficient-wise product
        ///
        /// This is only provided for the sake of convenience,
        /// in dot product functions and the like.
        constexpr Vector<2, T>& operator*=(const Vector<2, T>& vec);

        //////////////////////////
        /// @brief Opposite vector
        constexpr Vector<2, T> operator-();

        ///////////////////////////////////
        /// @brief Vector equality operator
        bool operator==(const Vector<2, T>& rhs) const;
        
        /////////////////////////////////////
        /// @brief Vector difference operator
        bool operator!=(const Vector<2, T>& rhs) const;
    };

    using Vector2i = Vector<2, int>;
    using Vector2f = Vector<2, float>;
    using Vector2d = Vector<2, double>;

    using Vec2 = Vector2f;
}

#include "Vector2.tpp"
