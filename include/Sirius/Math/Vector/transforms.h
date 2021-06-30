
#pragma once

#include "Vector.h"

namespace Sirius
{
    //////////////////////////////////////
    /// @brief Any-dimensional dot product
    template<unsigned dim, typename T> constexpr T dot(const Vector<dim, T>& v1, const Vector<dim, T>& v2);
    
    //////////////////////////////////////
    /// @brief 2-dimensional dot product
    template<typename T> constexpr T dot(const Vector<2, T>& v1, const Vector<2, T>& v2);
    
    //////////////////////////////////////
    /// @brief 3-dimensional dot product
    template<typename T> constexpr T dot(const Vector<3, T>& v1, const Vector<3, T>& v2);
    
    //////////////////////////////////////
    /// @brief 4-dimensional dot product
    template<typename T> constexpr T dot(const Vector<4, T>& v1, const Vector<4, T>& v2);

    /////////////////////////////////////////////////////
    /// @brief Cross product of two 3-dimensional vectors
    template<typename T> constexpr Vector<3, T> cross(const Vector<3, T>& v1, const Vector<3, T>& v2);

    //////////////////////////////////////////////
    /// @brief Normalize an any-dimensional vector
    template<unsigned dim, typename T> requires std::is_floating_point_v<T>
    constexpr Vector<dim, T> normalize(const Vector<dim, T>& vec);
    
    ///////////////////////////////////////////
    /// @brief Normalize a 2-dimensional vector
    template<typename T> constexpr Vector<2, T> normalize(const Vector<2, T>& vec);
    
    ///////////////////////////////////////////
    /// @brief Normalize a 3-dimensional vector
    template<typename T> constexpr Vector<3, T> normalize(const Vector<3, T>& vec);
    
    ///////////////////////////////////////////
    /// @brief Normalize a 4-dimensional vector
    template<typename T> constexpr Vector<4, T> normalize(const Vector<4, T>& vec);

    ////////////////////////////////////////
    /// @brief Rotate a 2-dimensional vector
    template<typename T> constexpr Vector<2, T> rotate(const Vector<2, T>& vec, T angle);
    
    ////////////////////////////////////////
    /// @brief Rotate a 3-dimensional vector
    template<typename T> constexpr Vector<3, T> rotate(const Vector<3, T>& vec, const Vector<3, T>& axis, T angle);
    
    ////////////////////////////////////////
    /// @brief Rotate a 4-dimensional vector
    template<typename T> constexpr Vector<4, T> rotate(const Vector<4, T>& vec, const Vector<3, T>& axis, T angle);
}

#include "transforms.tpp"
