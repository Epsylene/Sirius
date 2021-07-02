
#pragma once

#include "Matrix.hpp"

namespace Sirius
{
    //////////////////////////////////////////
    /// @brief Any-dimensional identity matrix
    template<unsigned dim, typename T = float> constexpr Matrix<dim, T> identity();

    ///////////////////////////////////////////////////////////////
    /// @brief Get the translation matrix of the vector `direction`
    template<typename T = float> constexpr Matrix<4, T> translate(const Vector<3, T>& direction);
    
    ///////////////////////////////////////////////////////////
    /// @brief Get the rotation matrix of `angle` around `axis`
    template<typename T = float> constexpr Matrix<4, T> rotate(const Vector<3, T>& axis, T angle);
    
    ////////////////////////////////////////////////
    /// @brief Get the scaling matrix of `direction`
    template<typename T = float> constexpr Matrix<4, T> scale(const Vector<3, T>& direction);
    
    /////////////////////////////////////////////
    /// @brief Get the scaling matrix by a factor
    ///
    /// The matrix returned is the scaling matrix
    /// of the vector `(factor, factor, factor)`.
    template<typename T> requires std::is_scalar_v<T> constexpr Matrix<4, T> scale(T factor);

    ///////////////////////////////////////////
    /// @brief Get a *lookAt()* matrix
    /// 
    /// @param eye The camera's center
    /// @param center The "looked at" position
    /// @param up The camera's up vector
    template<typename T = float> constexpr Matrix<4, T> lookAt(const Vector<3, T>& eye, const Vector<3, T>& center, const Vector<3, T>& up);
}

#include "transforms.tpp"
