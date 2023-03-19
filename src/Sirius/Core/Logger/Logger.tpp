
#include "Logger.hpp"

#include <fmt/os.h>
#include <fmt/chrono.h>
#include <fmt/color.h>

namespace fs = std::filesystem;

#define macro_str(a) #a
#define xmacro_str(a) macro_str(a)

namespace Sirius
{
    auto name = fmt::format("log_{:%d.%m.%Y-%H.%M.%S}.txt", std::chrono::system_clock::now());
    auto logs = std::string(xmacro_str(SRS_APP_DIR)) + "/logs/";
    static auto file = fmt::output_file(logs + name);

    void Logger::init(bool verbose)
    {
        Logger::verbose = verbose;

        fs::create_directories(logs);
    }

    template<typename... Ts>
    void Logger::log(LogLevel level, LogChannel channel, fmt::format_string<Ts...> message,
                     Ts&&... args)
    {
        std::string logMsg {};
        auto chnl_name = magic_enum::enum_name(channel);

        if(verbose)
        {
            using namespace std::chrono;

            auto now = system_clock::now();
            auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

            logMsg = fmt::format("[{:%d-%m-%Y %H:%M:%S}.{}] [{}] {}\n", now, ms.count(), chnl_name, message);
        }
        else
        {
            logMsg = fmt::format("[{}] {}\n", chnl_name, message);
        }

        switch (level)
        {
            case LogLevel::TRACE:
                fmt::print(fmt::runtime(logMsg), std::forward<Ts>(args)...);
                break;

            case LogLevel::INFO:
                fmt::print(fmt::fg(fmt::color::green), logMsg, std::forward<Ts>(args)...);
                break;

            case LogLevel::WARN:
                fmt::print(fmt::fg(fmt::color::yellow), logMsg, std::forward<Ts>(args)...);
                break;

            case LogLevel::ERR:
                fmt::print(fmt::fg(fmt::color::red), logMsg, std::forward<Ts>(args)...);
                break;
        }

        if(level > LogLevel::TRACE || verbose)
        {
            file.print(fmt::runtime(logMsg), std::forward<Ts>(args)...);
        }
    }

    void Logger::trace(LogChannel channel, std::string_view message)
    {
        trace(channel, fmt::runtime(message), "");
    }

    void Logger::info(LogChannel channel, std::string_view message)
    {
        info(channel, fmt::runtime(message), "");
    }

    void Logger::warn(LogChannel channel, std::string_view message)
    {
        warn(channel, fmt::runtime(message), "");
    }

    void Logger::error(LogChannel channel, std::string_view message)
    {
        error(channel, fmt::runtime(message), "");
    }

    template<typename... Ts>
    void Logger::trace(LogChannel channel, fmt::format_string<Ts...> message, Ts&&... args)
    {
        log(LogLevel::TRACE, channel, message, std::forward<Ts>(args)...);
    }

    template<typename... Ts>
    void Logger::info(LogChannel channel, fmt::format_string<Ts...> message, Ts&&... args)
    {
        log(LogLevel::INFO, channel, message, std::forward<Ts>(args)...);
    }

    template<typename... Ts>
    void Logger::warn(LogChannel channel, fmt::format_string<Ts...> message, Ts&&... args)
    {
        log(LogLevel::WARN, channel, message, std::forward<Ts>(args)...);
    }

    template<typename... Ts>
    void Logger::error(LogChannel channel, fmt::format_string<Ts...> message, Ts&&... args)
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