
#pragma once

#include "srspch.hpp"

namespace Sirius
{
    /// @brief The logging channel to print to
    ///
    /// CORE should be used for library messages only.
    enum class LogChannel
    {
        CORE, CLIENT, SCENE, GUI
    };

    /// @brief Logger message level
    ///
    /// Use TRACE for debug purposes and INFO, WARN,
    /// ERR as suited.
    enum class LogLevel
    {
        TRACE, INFO, WARN, ERR
    };

    /// @brief Logger class
    ///
    /// Provides an interface to log messages from
    /// the engine and the client.
    class Logger
    {
            static fmt::ostream file;
            static bool verbose;

        public:

            /// @brief Initialiazes the logger
            ///
            /// @param verbose If true, log all info, even on
            /// trace level, and print the date and time of each
            /// message.
            static void init(bool verbose = false);

            /// Generic log function
            ///
            /// @details Provided, but using Logger::trace() and co is
            /// preferable.
            template<typename... Ts>
            static void log(LogLevel level, LogChannel channel, fmt::format_string<Ts...> message, Ts&&... args);

            /// Log a debug message with no args
            static void trace(LogChannel channel, std::string_view message);

            /// Log an info message with no args
            static void info(LogChannel channel, std::string_view message);

            /// Log a warn message with no args
            static void warn(LogChannel channel, std::string_view message);

            /// Log an error message with no args
            static void error(LogChannel channel, std::string_view message);

            /// Log a debug message with args
            template<typename... Ts>
            static void trace(LogChannel channel, fmt::format_string<Ts...> message, Ts&&... args);

            /// Log a info message with args
            template<typename... Ts>
            static void info(LogChannel channel, fmt::format_string<Ts...> message, Ts&&... args);

            /// Log a warn message with args
            template<typename... Ts>
            static void warn(LogChannel channel, fmt::format_string<Ts...> message, Ts&&... args);

            /// Log an error message with args
            template<typename... Ts>
            static void error(LogChannel channel, fmt::format_string<Ts...> message, Ts&&... args);

            /// Log a message at trace level and in the CORE
            /// channel (for debug purposes)
            static void print(std::string_view msg);
    };
}

#include "Logger.tpp"
