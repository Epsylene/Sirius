
#pragma once

#include <fmt/os.h>

#include "srspch.hpp"
#include "Core.hpp"

namespace Sirius
{
    enum class LogChannel
    {
        CORE, SCENE, GUI
    };

    enum class LogLevel
    {
        TRACE, INFO, WARN, ERR
    };

    //////////////////////////////////////////////
    /// @brief Log utility class
    ///
    /// Provides an interface to log messages from
    /// the library and the client.
    class Log
    {
        public:

            static void init(const fs::path& path);

            template<typename... Ts>
            static void log(LogLevel level, LogChannel channel, std::string_view message, Ts&&... args);

            template<typename... Ts>
            static void trace(LogChannel channel, std::string_view message, Ts&&... args);
            template<typename... Ts>
            static void info(LogChannel channel, std::string_view message, Ts&&... args);
            template<typename... Ts>
            static void warn(LogChannel channel, std::string_view message, Ts&&... args);
            template<typename... Ts>
            static void error(LogChannel channel, std::string_view message, Ts&&... args);
    };
}

#include "Log.tpp"
