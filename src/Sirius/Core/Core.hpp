
#pragma once

#include "srspch.hpp"
#include <magic_enum.hpp>

#include "Sirius/Core/Logger/Log.hpp"

namespace fs = std::filesystem;

#define SRS_CORE_ASSERT(x, ...) { if(!(x)) { Log::error(LogChannel::CORE, "Assertion failed: {0}", __VA_ARGS__); } }

#define macro_str(a) #a
#define xmacro_str(a) macro_str(a)

namespace Sirius
{
    template<typename T> using Scope = std::unique_ptr<T>;
    template<typename T> using Ref = std::shared_ptr<T>;

    fs::path appPath { xmacro_str(SRS_APP_DIR) };
    fs::path libPath { xmacro_str(SRS_LIB_DIR) };
}
