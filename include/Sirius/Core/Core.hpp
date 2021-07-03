
#pragma once

#include "srspch.hpp"

#define SRS_ASSERT(x, ...) { if(!(x)) { SRS_ERROR("Assertion failed: {0}", __VA_ARGS__); } }
#define SRS_CORE_ASSERT(x, ...) { if(!(x)) { SRS_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); } }

namespace Sirius
{
    template<typename T> using Scope = std::unique_ptr<T>;

    template<typename T> using Ref = std::shared_ptr<T>;
}
