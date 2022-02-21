
#include "Log.hpp"

#include <fmt/os.h>
#include <fmt/chrono.h>

namespace fs = std::filesystem;

#define macro_str(a) #a
#define xmacro_str(a) macro_str(a)

namespace Sirius
{
    File Log::logFile {{}, fmt::format("log_{:%d.%m.%Y-%H.%M.%S}.txt", std::chrono::system_clock::now())};

    void Log::init()
    {
//        fs::create_directories("logs");
//
//        auto name = fmt::format("log_{:%d.%m.%Y-%H.%M.%S}.txt", std::chrono::system_clock::now());
//        logFile.stream.open(fs::path("logs")/name);
    }

    template<typename... Ts>
    void Log::log(LogLevel level, LogChannel channel, std::string_view message,
                  Ts&&... args)
    {
        using namespace std::chrono;

        auto now = system_clock::now();
        auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

        auto logMsg = fmt::format("[{:%d-%m-%Y %H:%M:%S}.{}] [{}] ", now, ms.count(), magic_enum::enum_name(channel)) + std::string(message);

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

        if(level != LogLevel::TRACE)
        {
            logFile.stream.open(fs::path("logs")/logFile.name, std::ios::out | std::ios::app);
            logFile.stream << "(" << magic_enum::enum_name(level) << ") " << logMsg << "\n";
            logFile.stream.close();
        }
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