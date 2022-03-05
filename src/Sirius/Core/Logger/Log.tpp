
#include "Log.hpp"

#include <fmt/os.h>
#include <fmt/chrono.h>
#include <fmt/color.h>

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
        std::string logMsg;
        if(verbose)
        {
            using namespace std::chrono;

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
                fmt::print(fmt::runtime(logMsg + "\n"), std::forward<Ts>(args)...);
                break;

            case LogLevel::INFO:
                fmt::print(fmt::fg(fmt::color::green), logMsg + "\n", std::forward<Ts>(args)...);
                break;

            case LogLevel::WARN:
                fmt::print(fmt::fg(fmt::color::yellow), logMsg + "\n", std::forward<Ts>(args)...);
                break;

            case LogLevel::ERR:
                fmt::print(fmt::fg(fmt::color::red), logMsg + "\n", std::forward<Ts>(args)...);
                break;
        }

        if(level != LogLevel::TRACE || verbose)
        {
            logFile.stream.open(std::string(xmacro_str(SRS_APP_DIR)) + "/logs/" + logFile.name, std::ios::out | std::ios::app);
            logFile.stream << "(" << magic_enum::enum_name(level) << ") " << fmt::format(fmt::runtime(logMsg), std::forward<Ts>(args)...) << "\n";
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

template <>
struct fmt::formatter<std::filesystem::path>
{
    constexpr auto parse(format_parse_context& ctx)
    {
        return ctx.end();
    }

    template <typename Context>
    auto format(const std::filesystem::path& path, Context& ctx)
    {
        return format_to(ctx.out(), fmt::runtime(path.string()));
    }
};