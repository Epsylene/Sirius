
#pragma once

#include "Matrix.hpp"

namespace Sirius
{
    //////////////////////////////////////////////////////////
    /// @brief Orthographic projection matrix
    /// 
    /// The near and far planes distances are set to -1 and 1.
    ///
    /// @param left, right Left and right planes distance 
    /// @param bottom, top Bottom and top planes distance
    template<typename T> constexpr Matrix<4, T> ortho(T left, T right, T bottom, T top);
    
    /////////////////////////////////////////////////////
    /// @brief Orthographic projection matrix
    /// 
    /// @param left, right Left and right planes distance 
    /// @param bottom, top Bottom and top planes distance
    /// @param near, far Near and far planes distance
    template<typename T> constexpr Matrix<4, T> ortho(T left, T right, T bottom, T top, T near, T far);

    /////////////////////////////////////////
    /// @brief Perspective projection matrix
    /// 
    /// @param fov Field of view, that is, the angle between the 
    ///     leftmost and righmost visible part of the view 
    /// @param aspect Aspect ratio of the view
    /// @param near, far Near and far planes distances
    template<typename T> constexpr Matrix<4, T> perspective(T fov, T aspect, T near, T far);
    
    //////////////////////////////////////////////////////////////////
    /// @brief All-planes perspective projection matrix
    ///
    /// This is only provided in case of being found useful; it
    /// should not behave any differently from the classic perspective
    /// projection matrix function. Near and far planes distances are 
    /// set to -1 and 1.
    ///
    /// @param left, right Left and right planes distances
    /// @param bottom, top Bottom and top planes distances
    template<typename T> constexpr Matrix<4, T> perspective_planes(T left, T right, T bottom, T top);
    
    //////////////////////////////////////////////////////////////////
    /// @brief All-planes perspective projection matrix
    ///
    /// This is only provided in case of being found useful; it
    /// should not behave any differently from the classic perspective
    /// projection matrix function.
    ///
    /// @param left, right Left and right planes distances
    /// @param bottom, top Bottom and top planes distances
    /// @param near, far Near and far planes distances
    template<typename T> constexpr Matrix<4, T> perspective_planes(T left, T right, T bottom, T top, T near, T far);
}

#include "clip_space.tpp"
