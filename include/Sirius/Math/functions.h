
#pragma once

#include "srspch.h"

namespace Sirius
{
    ///////////////////////////////////////////////////
    /// @brief Convert an angle from degrees to radians
    template<typename T> requires std::is_floating_point_v<T> T radians(T degrees);
}

#include "functions.tpp"
