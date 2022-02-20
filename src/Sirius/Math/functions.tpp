
#include "functions.hpp"

namespace Sirius
{
    template<typename T> requires std::is_floating_point_v<T>
    T radians(T degrees)
    {
        return degrees * static_cast<T>(0.01745329251994329576923690768489);
    }
}