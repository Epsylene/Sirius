
#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>

#include "Core.h"

namespace Sirius
{
    //////////////////////////////////////////////
    /// @brief Log utility class
    ///
    /// Provides an interface to log messages from
    /// the library and the client.
    class Log
    {
        private:

            static Ref<spdlog::logger> coreLogger;
            static Ref<spdlog::logger> clientLogger;

        public:

            ///////////////////////////////////
            /// @brief Initializes the loggers.
            static void init();

            ////////////////////////////
            /// @brief Sirius trace log.
            template<typename... T>
            static void coreTrace(T... args) { coreLogger->trace(args...); }

            ////////////////////////////
            /// @brief Client trace log.
            template<typename... T>
            static void trace(T... args) { clientLogger->trace(args...); }

            ///////////////////////////
            /// @brief Sirius info log.
            template<typename... T>
            static void coreInfo(T... args) { coreLogger->info(args...); }

            ///////////////////////////
            /// @brief Client info log.
            template<typename... T>
            static void info(T... args) { clientLogger->info(args...); }

            ///////////////////////////
            /// @brief Sirius warn log.
            template<typename... T>
            static void coreWarn(T... args) { coreLogger->warn(args...); }

            ///////////////////////////
            /// @brief Client warn log.
            template<typename... T>
            static void warn(T... args) { clientLogger->warn(args...); }

            ////////////////////////////
            /// @brief Sirius error log.
            template<typename... T>
            static void coreError(T... args) { coreLogger->error(args...); }

            ////////////////////////////
            /// @brief Client error log.
            template<typename... T>
            static void error(T... args) { clientLogger->error(args...); }

            ////////////////////////////
            /// @brief Sirius fatal log.
            template<typename... T>
            static void coreFatal(T... args) { coreLogger->critical(args...); }

            ////////////////////////////
            /// @brief Client fatal log.
            template<typename... T>
            static void fatal(T... args) { clientLogger->critical(args...); }

            //////////////////////////////////
            /// @brief Get the library logger.
            inline static Ref<spdlog::logger>& getCoreLogger() { return coreLogger; }

            /////////////////////////////////
            /// @brief Get the client logger.
            inline static Ref<spdlog::logger>& getClientLogger() { return clientLogger; }
    };
}

//Core log
#define SRS_CORE_TRACE(...) ::Sirius::Log::getCoreLogger()->trace(__VA_ARGS__)
#define SRS_CORE_INFO(...) ::Sirius::Log::getCoreLogger()->info(__VA_ARGS__)
#define SRS_CORE_WARN(...) ::Sirius::Log::getCoreLogger()->warn(__VA_ARGS__)
#define SRS_CORE_ERROR(...) ::Sirius::Log::getCoreLogger()->error(__VA_ARGS__)
#define SRS_CORE_FATAL(...) ::Sirius::Log::getCoreLogger()->critical(__VA_ARGS__)

//Client log
#define SRS_TRACE(...) ::Sirius::Log::getClientLogger()->trace(__VA_ARGS__)
#define SRS_INFO(...) ::Sirius::Log::getClientLogger()->info(__VA_ARGS__)
#define SRS_WARN(...) ::Sirius::Log::getClientLogger()->warn(__VA_ARGS__)
#define SRS_ERROR(...) ::Sirius::Log::getClientLogger()->error(__VA_ARGS__)
#define SRS_FATAL(...) ::Sirius::Log::getClientLogger()->critical(__VA_ARGS__)
