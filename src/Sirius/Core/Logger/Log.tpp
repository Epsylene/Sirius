
#include "Log.hpp"

#include <fmt/os.h>
#include <fmt/chrono.h>

namespace fs = std::filesystem;

#define macro_str(a) #a
#define xmacro_str(a) macro_str(a)

namespace Sirius
{
    File Log::logFile {{}, fmt::format("log_{:%d.%m.%Y-%H.%M.%S}.txt", std::chrono::system_clock::now())};
    bool Log::verbose = false;

    void Log::init(bool verbose = false)
    {
        Log::verbose = verbose;

        std::string logsPath = std::string(xmacro_str(SRS_APP_DIR)) + "/logs/";
        fs::create_directories(logsPath);

        auto name = fmt::format("log_{:%d.%m.%Y-%H.%M.%S}.txt", std::chrono::system_clock::now());
        logFile.stream.open(logsPath + name);
    }

    template<typename... Ts>
    void Log::log(LogLevel level, LogChannel channel, std::string_view message,
                  Ts&&... args)
    {
        using namespace std::chrono;

        std::string logMsg;
        if(verbose)
        {
            auto now = system_clock::now();
            auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

            logMsg = fmt::format("[{:%d-%m-%Y %H:%M:%S}.{}] [{}] ", now, ms.count(), magic_enum::enum_name(channel)) + std::string(message);
        }
        else
        {
            logMsg = fmt::format("[{}] ", magic_enum::enum_name(channel)) + std::string(message);
        }

        switch (level)
        {
            case LogLevel::TRACE:
                fmt::vprint(logMsg + "\n", fmt::make_format_args(std::forward<Ts>(args)...));
                break;

            case LogLevel::INFO:
                fmt::vprint("\033[32m" + logMsg + "\033[0m\n", fmt::make_format_args(std::forward<Ts>(args)...));
                break;

            case LogLevel::WARN:
                fmt::vprint("\033[33m" + logMsg + "\033[0m\n", fmt::make_format_args(std::forward<Ts>(args)...));
                break;

            case LogLevel::ERR:
                fmt::vprint("\033[31m" + logMsg + "\033[0m\n", fmt::make_format_args(std::forward<Ts>(args)...));
                break;
        }

        if(level != LogLevel::TRACE || verbose)
        {
            logFile.stream.open(std::string(xmacro_str(SRS_APP_DIR)) + "/logs/" + logFile.name, std::ios::out | std::ios::app);
            logFile.stream << "(" << magic_enum::enum_name(level) << ") " << fmt::vformat(logMsg, fmt::make_format_args(std::forward<Ts>(args)...)) << "\n";
            logFile.stream.close();
        }
    }

    void Log::trace(LogChannel channel, std::string_view message)
    {
        trace(channel, message, "");
    }

    void Log::info(LogChannel channel, std::string_view message)
    {
        info(channel, message, "");
    }

    void Log::warn(LogChannel channel, std::string_view message)
    {
        warn(channel, message, "");
    }

    void Log::error(LogChannel channel, std::string_view message)
    {
        error(channel, message, "");
    }

    template<typename... Ts>
    void Log::trace(LogChannel channel, std::string_view message, Ts&&... args)
    {
        log(LogLevel::TRACE, channel, message, std::forward<Ts>(args)...);
    }

    template<typename... Ts>
    void Log::info(LogChannel channel, std::string_view message, Ts&&... args)
    {
        log(LogLevel::INFO, channel, message, std::forward<Ts>(args)...);
    }

    template<typename... Ts>
    void Log::warn(LogChannel channel, std::string_view message, Ts&&... args)
    {
        log(LogLevel::WARN, channel, message, std::forward<Ts>(args)...);
    }

    template<typename... Ts>
    void Log::error(LogChannel channel, std::string_view message, Ts&&... args)
    {
        log(LogLevel::ERR, channel, message, std::forward<Ts>(args)...);
    }
}