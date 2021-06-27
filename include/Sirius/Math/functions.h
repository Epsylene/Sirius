
#pragma once

#include "srspch.h"

namespace Sirius
{
    template<typename T> requires std::is_floating_point_v<T> T radians(T degrees);
}

#include "functions.tpp"
