
#pragma once

#include "srspch.hpp"

#include <fmt/os.h>

namespace Sirius
{
    /////////////////////////////////////////////////
    /// @brief The logging channel to print tp
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

    //////////////////////////////////////////////////
    /// @brief Basic "file" representation as a stream
    ///     and a filename 
    struct File
    {
        std::ofstream stream;
        const std::string name;
    };

    //////////////////////////////////////////////
    /// @brief Logger utility class
    ///
    /// Provides an interface to log messages from
    /// the engine and the client.
    class Logger
    {
        private:

            static File logFile;
            static bool verbose;

        public:

            /////////////////////////////////////////
            /// @brief Initialize the logger
            /// 
            /// @param verbose (false by default) Print the
            ///     date and time of each message, as well
            ///     as printing the TRACE level messages in
            ///     the log files.
            static void init(bool verbose);

            //////////////////////////////////////////////
            /// @brief Generic log function
            ///
            /// Provided, but using Logger::trace() and co is
            /// preferable.
            template<typename... Ts>
            static void log(LogLevel level, LogChannel channel, std::string_view message, Ts&&... args);

            ///////////////////////////////////////////
            /// @brief Log a debug message with no args
            static void trace(LogChannel channel, std::string_view message);
            
            ///////////////////////////////////////////
            /// @brief Log an info message with no args
            static void info(LogChannel channel, std::string_view message);
            
            //////////////////////////////////////////
            /// @brief Log a warn message with no args
            static void warn(LogChannel channel, std::string_view message);
            
            ////////////////////////////////////////////
            /// @brief Log an error message with no args
            static void error(LogChannel channel, std::string_view message);

            ////////////////////////////////////////
            /// @brief Log a debug message with args
            template<typename... Ts>
            static void trace(LogChannel channel, std::string_view message, Ts&&... args);
            
            ///////////////////////////////////////
            /// @brief Log a info message with args
            template<typename... Ts>
            static void info(LogChannel channel, std::string_view message, Ts&&... args);
            
            ///////////////////////////////////////
            /// @brief Log a warn message with args
            template<typename... Ts>
            static void warn(LogChannel channel, std::string_view message, Ts&&... args);
            
            /////////////////////////////////////////
            /// @brief Log an error message with args
            template<typename... Ts>
            static void error(LogChannel channel, std::string_view message, Ts&&... args);
    };
}

#include "Log.tpp"
