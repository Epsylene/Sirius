
#pragma once

#include "srspch.hpp"

namespace Sirius
{
    /////////////////////////////////////////////////
    /// @brief The logging channel to print to
    ///
    /// CORE should be used for library messages only.
    enum class LogChannel
    {
        CORE, CLIENT, SCENE, GUI
    };

    /////////////////////////////////////////
    /// @brief Logger message level
    ///
    /// Use TRACE for debug purposes and INFO, WARN,
    /// ERR as suited.
    enum class LogLevel
    {
        TRACE, INFO, WARN, ERR
    };

    //////////////////////////////////////////////
    /// @brief Logger "class"
    ///
    /// Provides an interface to log messages from
    /// the engine and the client.
    namespace Logger
    {
        bool verbose;

        void init(bool verbose = false);

        //////////////////////////////////////////////
        /// @brief Generic log function
        ///
        /// Provided, but using Logger::trace() and co is
        /// preferable.
        template<typename... Ts>
        void log(LogLevel level, LogChannel channel, fmt::format_string<Ts...> message, Ts&&... args);

        ///////////////////////////////////////////
        /// @brief Log a debug message with no args
        void trace(LogChannel channel, std::string_view message);

        ///////////////////////////////////////////
        /// @brief Log an info message with no args
        void info(LogChannel channel, std::string_view message);

        //////////////////////////////////////////
        /// @brief Log a warn message with no args
        void warn(LogChannel channel, std::string_view message);

        ////////////////////////////////////////////
        /// @brief Log an error message with no args
        void error(LogChannel channel, std::string_view message);

        ////////////////////////////////////////
        /// @brief Log a debug message with args
        template<typename... Ts>
        void trace(LogChannel channel, fmt::format_string<Ts...> message, Ts&&... args);

        ///////////////////////////////////////
        /// @brief Log a info message with args
        template<typename... Ts>
        void info(LogChannel channel, fmt::format_string<Ts...> message, Ts&&... args);

        ///////////////////////////////////////
        /// @brief Log a warn message with args
        template<typename... Ts>
        void warn(LogChannel channel, fmt::format_string<Ts...> message, Ts&&... args);

        /////////////////////////////////////////
        /// @brief Log an error message with args
        template<typename... Ts>
        void error(LogChannel channel, fmt::format_string<Ts...> message, Ts&&... args);
    }
}

#include "Logger.tpp"
