
#pragma once

#include "srspch.hpp"
#include "magic_enum.hpp"

#include "Sirius/Core/Logger/Log.hpp"

//#define SRS_CORE_ASSERT(x, ...) { if(!(x)) { Log::error(LogChannel::CORE, "Assertion failed: {0}", __VA_ARGS__); } }
#define SRS_CORE_ASSERT(x, ...) if(!(x)) {}

namespace fs = std::filesystem;

namespace Sirius
{
    template<typename T> using Scope = std::unique_ptr<T>;
    template<typename T> using Ref = std::shared_ptr<T>;
}
