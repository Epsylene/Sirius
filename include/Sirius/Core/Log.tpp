
#include "Sirius/Core/Log.hpp"

#include <fmt/color.h>

namespace Sirius
{
    static Scope<fmt::ostream> logFile;

    void Log::init(const fs::path& path)
    {
        auto dirPath = path.has_extension() ? path.parent_path() : path;
        fs::create_directories(dirPath.parent_path()/"logs");

        using namespace std::chrono;

        auto now = system_clock::now();
        auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
        auto timer = system_clock::to_time_t(now);
        auto bt = std::localtime(&timer);

        std::ostringstream oss;
        oss << std::put_time(bt, "log_%d.%m.%Y-%H.%M.%S.txt");
        logFile = std::make_unique<fmt::ostream>(fmt::output_file((dirPath/"logs"/oss.str()).string()));
    }

    template<typename... Ts>
    void Log::log(LogLevel level, LogChannel channel, std::string_view message,
                  Ts&&... args)
    {
        using namespace std::chrono;

        auto now = system_clock::now();
        auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
        auto timer = system_clock::to_time_t(now);
        auto bt = std::localtime(&timer);

        std::ostringstream oss;
        oss << std::put_time(bt, "[%d-%m-%Y %H:%M:%S");
        oss << "." << std::setfill('0') << std::setw(3) << ms.count() << "] ";
        oss << "[" << magic_enum::enum_name(channel) << "] ";

        auto logMsg = oss.str() + std::string(message);

        // @todo: fix printing to files and multiple log levels outputs

        switch (level)
        {
            case LogLevel::TRACE:
                fmt::vprint(logMsg + "\n", fmt::make_format_args(std::forward<Ts>(args)...));
//                fmt::vprint(logFile, logMsg + "\n", fmt::make_format_args(std::forward<Ts>(args)...));

            case LogLevel::INFO:
                fmt::vprint("\033[32m" + logMsg + "\033[0m\n", fmt::make_format_args(std::forward<Ts>(args)...));
//                fmt::vprint(logFile, fmt::fg(fmt::color::green), logMsg + "\n", fmt::make_format_args(std::forward<Ts>(args)...));

            case LogLevel::WARN:
                fmt::vprint("\033[33m" + logMsg + "\033[0m\n", fmt::make_format_args(std::forward<Ts>(args)...));
//                fmt::vprint(logFile, fmt::fg(fmt::color::green), logMsg + "\n", fmt::make_format_args(std::forward<Ts>(args)...));

            case LogLevel::ERR:
                fmt::vprint("\033[31m" + logMsg + "\033[0m\n", fmt::make_format_args(std::forward<Ts>(args)...));
//                fmt::vprint(logFile, fmt::fg(fmt::color::green), logMsg + "\n", fmt::make_format_args(std::forward<Ts>(args)...));
        }

//        logFile->close();
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
