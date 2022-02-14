
#pragma once

#include <fmt/os.h>
#include <fmt/chrono.h>

#include "srspch.hpp"

#include "../Core.hpp"
#include "../Application.hpp"

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

    struct File
    {
        std::ofstream stream;
        const std::string name;
    };

    //////////////////////////////////////////////
    /// @brief Log utility class
    ///
    /// Provides an interface to log messages from
    /// the library and the client.
    class Log
    {
        private:

            static File logFile;

        public:

            static void init();

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
